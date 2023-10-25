#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc == 4) {
    if (strcmp(argv[1], "n")) {
      catarray_t * cats = catClassifier(argv[2]);
      parseFile(argv[3], cats, 1);
    }
  }
  else if (argc == 3) {
    catarray_t * cats = catClassifier(argv[1]);
    parseFile(argv[2], cats, 0);
  }
  else {
    fprintf(stderr, "wrong input format\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
