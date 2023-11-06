#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//function returns reference to previously used words
char * getWordFromBackref(char * ref, category_t * usedWords) {
  int backref = atoi(ref);
  return usedWords->words[usedWords->n_words - backref];
}

//function to delete the used word from cats
void filter(catarray_t * cats, category_t * usedWords) {
  size_t c = 0;
  while (c < cats->n) {
    size_t i = 0;
    while (i < cats->arr[c].n_words) {
      int found = 0;
      for (size_t j = 0; j < usedWords->n_words; j++) {
        if (!strcmp(cats->arr[c].words[i], usedWords->words[j])) {
          found = 1;
          //free the memory of the word being found
          free(cats->arr[c].words[i]);
          //rearrange the array of words
          for (size_t k = i; k < cats->arr[c].n_words - 1; k++) {
            cats->arr[c].words[k] = cats->arr[c].words[k + 1];
          }
          cats->arr[c].n_words--;
          break;
        }
      }
      if (!found) {
        i++;
      }
    }
    c++;
  }
}
// story telling function
void parseFile(const char * file, catarray_t * cats, int noreuse) {
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file");
    exit(EXIT_FAILURE);
  }
  //initialized category_t used to track the backref
  category_t * used = malloc(sizeof(*used));
  used->name = NULL;
  used->words = NULL;
  used->n_words = 0;

  char * line = NULL;
  size_t sz = 0;

  while ((getline(&line, &sz, f)) >= 0) {
    char * start = NULL;
    char * end = NULL;
    //store the start of line for free later
    char * temp = line;
    //check matching underscore on the same line
    while ((start = strchr(line, '_'))) {
      end = strchr(start + 1, '_');
      if (end == NULL) {
        fprintf(stderr, "No end underscore found\n");
        exit(EXIT_FAILURE);
      }
      *start = '\0';
      *end = '\0';
      const char * curr = NULL;
      //for step 3,4: references to previously used words.
      if (atoi((start + 1)) >= 1 && atoi((start + 1)) <= used->n_words) {
        curr = getWordFromBackref(start + 1, used);
      }
      else {
        //for step 4: if '-n' exists, delete words already  used in the cats
        if (noreuse == 1) {
          filter(cats, used);
        }
        curr = chooseWord(start + 1, cats);
      }
      printf("%s%s", line, curr);
      //store words being used
      used->words = realloc(used->words, (used->n_words + 1) * sizeof(*used->words));
      used->words[used->n_words] = strdup(curr);
      used->n_words++;
      line = end + 1;
    }
    printf("%s", line);
    free(temp);
    line = NULL;
  }
  //free used structure
  for (size_t i = 0; i < used->n_words; i++) {
    free(used->words[i]);
  }
  free(used->words);
  free(used);
  free(line);
  if (fclose(f) != 0) {
    exit(EXIT_FAILURE);
  }
}

//function to strip \n
void stripNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
//function to store words in catarray_t
catarray_t * catClassifier(char * file) {
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file");
    exit(EXIT_FAILURE);
  }

  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;

  char * line = NULL;
  size_t sz = 0;
  while ((getline(&line, &sz, f)) >= 0) {
    char * ptr = strchr(line, ':');
    if (ptr == NULL) {
      fprintf(stderr, "Wrong input format\n");
      exit(EXIT_FAILURE);
    }
    *ptr = '\0';
    char * newname = line;
    char * temp = line;  //record the start of the line for free later
    line = ptr + 1;
    int same = 0;

    for (size_t i = 0; i < ans->n; i++) {
      if (strcmp(newname, ans->arr[i].name) == 0) {
        //if find the old category, add the corresponding word to the category
        ans->arr[i].words = realloc(
            ans->arr[i].words, (ans->arr[i].n_words + 1) * sizeof(*ans->arr[i].words));
        ans->arr[i].words[ans->arr[i].n_words] = strdup(line);
        stripNewLine(ans->arr[i].words[ans->arr[i].n_words]);
        ans->arr[i].n_words++;
        same = 1;
        line = NULL;
        break;
      }
    }
    if (!same) {
      /**if the category is new,add a category_t to the array of categories;
      initialize the name, n_words to 1, and the corresponding word to words**/
      ans->arr = realloc(ans->arr, (ans->n + 1) * sizeof(*ans->arr));
      ans->arr[ans->n].name = strdup(newname);
      ans->arr[ans->n].n_words = 1;
      ans->arr[ans->n].words = malloc(sizeof(*ans->arr->words));
      ans->arr[ans->n].words[0] = strdup(line);
      stripNewLine(ans->arr[ans->n].words[0]);
      ans->n++;
      line = NULL;
    }
    free(temp);
  }
  free(line);
  if (fclose(f) != 0) {
    exit(EXIT_FAILURE);
  }
  return ans;
}

//function to free the catarray_t structure
void freeCatArray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}
