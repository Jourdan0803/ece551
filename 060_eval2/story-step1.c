#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: story input name\n");
    exit(EXIT_FAILURE);
  }
  parseFile(argv[1], NULL, 0);
  return 0;
}
