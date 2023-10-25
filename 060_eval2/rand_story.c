#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * getWordFromBackref(char * ref, category_t * usedWords) {
  int backref = atoi(ref);
  return usedWords->words[usedWords->n_words - backref];
}
void filter(catarray_t * cats, category_t * usedWords) {
  size_t c = 0;
  while (c < cats->n) {
    size_t i = 0;
    while (i < cats->arr[c].n_words) {
      int found = 0;
      for (size_t j = 0; j < usedWords->n_words; j++) {
        if (!strcmp(cats->arr[c].words[i], usedWords->words[j])) {
          found = 1;
          for (size_t k = i; k < cats->arr[c].n_words - 1; k++) {
            //free(cats->arr[c].words[k]);
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

void parseFile(const char * file, catarray_t * cats, int noreuse) {
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file");
    exit(EXIT_FAILURE);
  }
  //initialized catarray_t useWords to track the backref
  category_t * used = malloc(sizeof(*used));
  used->name = NULL;
  used->words = NULL;
  used->n_words = 0;

  char * line = NULL;
  size_t sz = 0;

  while ((getline(&line, &sz, f)) >= 0) {
    char * start = NULL;
    char * end = NULL;
    while ((start = strchr(line, '_'))) {
      end = strchr(start + 1, '_');
      if (end == NULL) {
        fprintf(stderr, "No end underscore found\n");
        exit(EXIT_FAILURE);
      }
      *start = '\0';
      *end = '\0';
      const char * curr = NULL;
      if (atoi((start + 1)) >= 1 && atoi((start + 1)) <= used->n_words) {
        curr = getWordFromBackref(start + 1, used);
      }
      else {
        if (noreuse == 1) {
          filter(cats, used);
        }
        curr = chooseWord(start + 1, cats);
      }
      printf("%s%s", line, curr);
      used->words = realloc(used->words, (used->n_words + 1) * sizeof(*used->words));
      used->words[used->n_words] = strdup(curr);
      used->n_words++;
      line = end + 1;
    }
    printf("%s", line);
    line = NULL;
  }

  for (size_t i = 0; i < used->n_words; i++) {
    free(used->words[i]);
  }
  free(used->words);
  free(used);
  free(line);
  fclose(f);
}

void stripNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

catarray_t * catClassifier(char * file) {
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file");
    exit(EXIT_FAILURE);
  }
  //initialize catarray_t ans
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
    line = ptr + 1;
    int same = 0;
    for (size_t i = 0; i < ans->n; i++) {
      if (strcmp(newname, ans->arr[i].name) == 0) {
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
      ans->arr = realloc(ans->arr, (ans->n + 1) * sizeof(*ans->arr));
      category_t * newcat = malloc(sizeof(*newcat));
      newcat->name = strdup(newname);
      newcat->n_words = 1;
      newcat->words = malloc(sizeof(*newcat->words));
      newcat->words[0] = strdup(line);
      stripNewLine(newcat->words[0]);
      ans->arr[ans->n] = *newcat;
      ans->n++;
      line = NULL;
    }
  }
  free(line);
  fclose(f);
  return ans;
}

void freeCatArray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);  // Free name in each category
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);  // Free each word
    }
    free(cats->arr[i].words);  // Free words array
    //printf(cats->arr[i]);
  }
  free(cats->arr);  // Free array of categories
  free(cats);       // Free the structure
}
