#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * answer = malloc(sizeof(*answer));
  if (answer == NULL) {
    exit(EXIT_FAILURE);
  }
  answer->array = NULL;
  answer->size = 0;
  answer->unknown = 0;
  return answer;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
    return;
  }
  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->array[i].str, name) == 0) {
      c->array[i].count++;
      return;
    }
  }
  c->size++;
  c->array = realloc(c->array, c->size * sizeof(*c->array));
  one_count_t newCount;
  newCount.count = 1;
  newCount.str = strdup(name);
  c->array[c->size - 1] = newCount;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i].str, c->array[i].count);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->array[i].str);
  }
  free(c->array);
  free(c);
}
