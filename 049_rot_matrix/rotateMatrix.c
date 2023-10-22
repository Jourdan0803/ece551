#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void rotate_matrix(FILE * f) {
  int row = 0;
  int column = 0;
  int c;
  char matrix[10][10] = {"0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000",
                         "0000000000"};
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (column >= 10 || row >= 10) {
        fprintf(stderr, "Invalid matrix\n");
        exit(EXIT_FAILURE);
      }
      else {
        if (c < 0 || c > 255) {
          fprintf(stderr, "Invalid character\n");
          exit(EXIT_FAILURE);
        }
        else {
          matrix[row][column] = c;
          column++;
        }
      }
    }
    else {
      if (column != 10) {
        fprintf(stderr, "Invalid matrix\n");
        exit(EXIT_FAILURE);
      }
      else {
        column = 0;
        row++;
      }
    }
  }
  if (row != 10 || column != 0) {
    fprintf(stderr, "Invalid matrix\n");
    exit(EXIT_FAILURE);
  }
  for (int j = 0; j < 10; j++) {
    for (int i = 9; i >= 0; i--) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage:rotateMatrix input\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file\n");
    return EXIT_FAILURE;
  }
  rotate_matrix(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
