#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: categories/wordsFilename storyFilename\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * cats = catClassifier(argv[1]);
  parseFile(argv[2], cats, 0);
  return 0;
}
