#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_max(int * array, size_t n, size_t correct) {
  if (maxSeq(array, n) == correct) {
    printf("pass");
  }
  else {
    printf("fail");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array2[1] = {1};
  int array3[6] = {0, 0, 1, 3, 5, 1};
  int array4[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array5[7] = {-1, 0, 1, 2, 4, 3, 5};
  int array6[5] = {1, 1, 1, 1, 1};
  int array7[5] = {5, 4, 3, 2, 1};
  int array8[6] = {-1, -2, -3, 0, 3, 8};
  test_max(array2, 1, 1);
  test_max(array3, 6, 4);
  test_max(array4, 10, 4);
  test_max(array5, 7, 5);
  test_max(array6, 5, 1);
  test_max(array7, 5, 1);
  test_max(array8, 6, 4);
  test_max(NULL, 0, 0);
  return EXIT_SUCCESS;
}
