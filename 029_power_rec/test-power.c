#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned result = power(x, y);
  if (result != expected_ans) {
    printf("Failured to pass the tests");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(1, 1, 1);
  run_check(2, 3, 8);
  run_check(-1, 2, 1);
  run_check(-1, 3, -1);
}
