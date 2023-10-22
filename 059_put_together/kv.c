#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  if (answer == NULL) {
    exit(EXIT_FAILURE);
  }
  answer->numPairs = 0;
  answer->kvpair = NULL;
  char * curr = NULL;
  size_t sz;
  while (getline(&curr, &sz, f) >= 0) {
    answer->kvpair =
        realloc(answer->kvpair, (answer->numPairs + 1) * sizeof(*answer->kvpair));
    if (answer->kvpair == NULL) {
      exit(EXIT_FAILURE);
    }
    kvpair_t * kv = malloc(sizeof(*kv));
    kv->key = curr;
    char * p = strchr(kv->key, '=');
    if (p != NULL) {
      *p = '\0';
    }
    kv->value = p + 1;
    char * q = strchr(kv->value, '\n');
    if (q != NULL) {
      *q = '\0';
    }
    answer->kvpair[answer->numPairs] = kv;
    answer->numPairs++;
    curr = NULL;
  }
  if (fclose(f) != 0) {
    exit(EXIT_FAILURE);
  }
  //fclose(f);
  free(curr);
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    free(pairs->kvpair[i]->key);
    free(pairs->kvpair[i]);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < (pairs->numPairs); i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpair[i]->key, pairs->kvpair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    if (strcmp(key, pairs->kvpair[i]->key) == 0) {
      return pairs->kvpair[i]->value;
    }
  }
  return NULL;
}
