//#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseFile(char *file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr,"Error opening file");
        exit(EXIT_FAILURE);
    }
    
    char *line = NULL;
    size_t sz = 0;

    while ((getline(&line, &sz, f)) >= 0) {
        char * start = NULL;
        char * end = NULL;
        while ((start = strchr(line, '_'))) {
            char * end = strchr(start + 1, '_');
            if (end ==NULL) {
                fprintf(stderr, "No end underscore found\n");
                exit(EXIT_FAILURE);
            }
            *start = '\0';
            *end = '\0';
            printf("%s%s", line,chooseWord(start+1,NULL));
            line = end + 1;
        }
        printf("%s", line);
    }
}
struct category_tag {
  char * name;
  char ** words;
  size_t n_words;
};
typedef struct category_tag category_t;

struct catarray_tag {
  category_t * arr;
  size_t n;
};
typedef struct catarray_tag catarray_t;

void printWords(catarray_t * cats){
    for(size_t i = 0; i<cats->n;i++){
        printf("%s",cats->arr[i].name);
    }
}

void stripNewLine(char *str){
    char * p = strchr(str,'\n');
    if(p!=NULL){
        *p='\0';
    }
}

void catClassifier(char *file){
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr,"Error opening file");
        exit(EXIT_FAILURE);
    }
    //initialize catarray_t ans
    catarray_t * ans = malloc(sizeof(*ans));
    ans ->arr = NULL;
    ans->n = 0;

    char *line = NULL;
    size_t sz = 0;
    while ((getline(&line, &sz, f)) >= 0) {
        char *ptr = strchr(line, ':');
        if(ptr == NULL){
            fprintf(stderr, "Wrong input format\n");
            exit(EXIT_FAILURE);
        }
        *ptr = '\0';
        char * newname = line;
        line = ptr+1;
        int same = 0;
        for(size_t i = 0;i<ans->n;i++){
            if(strcmp(newname,ans->arr[i].name)==0){
                ans->arr[i].words = realloc(ans->arr[i].words,(ans->arr[i].n_words+1)*sizeof(*ans->arr[i].words));
                ans->arr[i].words[ans->arr[i].n_words]=line;
                stripNewLine(ans->arr[i].words[ans->arr[i].n_words]);
                ans->arr[i].n_words++;
                same = 1;
                line = NULL;
                break;
            }
        }
        if(!same){
            ans->arr = realloc(ans->arr,(ans->n+1)*sizeof(*ans->arr));
            category_t newcat;
            newcat.name=newname;
            newcat.n_words=1;
            newcat.words = malloc(sizeof(*newcat.words));
            newcat.words[0] = line;
            stripNewLine(newcat.words[0]);
            ans->arr[ans->n]=newcat;
            ans->n++;
            line = NULL;
        }
    }  
printWords(ans);


// for(size_t i = 0;i<ans->n;i++){
//     // for(size_t j = 0;i<ans->arr[i].n_words;i++){
//     //     free(ans->arr[i].words[j]);
//     // }
//     free(ans->arr[i].words);
//     //free(ans->arr[i]);
//     }
//     free(ans->arr);
//     free(ans);
}
    
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: story input name\n");
        exit(EXIT_FAILURE);
    }
    catClassifier(argv[1]);
    return 0;
}
