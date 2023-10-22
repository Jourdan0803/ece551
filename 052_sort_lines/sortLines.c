#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void read(FILE * f) {
  size_t sz;
  size_t i = 0;
  char ** line = NULL;
  char * curr = NULL;
  while (getline(&curr, &sz, f) >= 0) {
    line = realloc(line, (i + 1) * sizeof(*line));
    line[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(line, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", line[j]);
    free(line[j]);
  }
  free(line);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      fprintf(stderr, "No such file exist\n");
      exit(EXIT_FAILURE);
    }
    read(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the input file!\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "No such file exist\n");
        exit(EXIT_FAILURE);
      }
      else {
        read(f);
        if (fclose(f) != 0) {
          fprintf(stderr, "Failed to close the input file!\n");
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
