#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t count = 1;
  size_t max = 0;
  for (int i = 0; i < n; i++) {
    if (array[i + 1] > array[i]) {
      count++;
    }
    else {
      if (count > max) {
        max = count;
      }
      count = 1;
    }
  }
  return max;
}
