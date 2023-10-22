#include <stdbool.h>

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}

bool checkBetween(int x, int lower, int upper) {
  if (x >= lower && x < upper) {
    return true;
  }
  else {
    return false;
  }
}
bool checkequal(int x, int y) {
  if (x == y) {
    return true;
  }
  else {
    return false;
  }
}
void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y
  //check if  EITHER
  //    ((x is between x_offset  and x_offset +size2) AND
  //     y is equal to either y_offset OR y_offset + size2 - 1 )
  //  OR
  //    ((y is between y_offset and y_offset + size2) AND
  //     x is equal to either x_offset OR x_offset + size2 -1)
  // if so, print a *
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if ((checkBetween(x, x_offset, x_offset + size2) &&
           (checkequal(y, y_offset) || checkequal(y, y_offset + size2 - 1))) ||
          (checkBetween(y, y_offset, y_offset + size2) &&
           (checkequal(x, x_offset) || checkequal(x, x_offset + size2 - 1)))) {
        printf("*");
      }
      // if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
      else if ((x < size1 && (checkequal(y, 0) || checkequal(y, size1 - 1))) ||
               (y < size1 && (checkequal(x, 0) || checkequal(x, size1 - 1)))) {
        printf("#");
      }
      //else print a space
      else {
        printf(" ");
      }
    }
    //when you finish counting x from 0 to w,
    //print a newline
    printf("\n");
  }
}
//count from 0 to w. Call the number you count with x
//check if  EITHER
//    ((x is between x_offset  and x_offset +size2) AND
//     y is equal to either y_offset OR y_offset + size2 - 1 )
//  OR
//    ((y is between y_offset and y_offset + size2) AND
//     x is equal to either x_offset OR x_offset + size2 -1)
// if so, print a *

//if not,
// check if EITHER
//    x is less than size1 AND (y is either 0 or size1-1)
// OR
//    y is less than size1 AND (x is either 0 or size1-1)
//if so, print a #

//else print a space
//when you finish counting x from 0 to w,
//print a newline

// void squares(int size1, int x_offset, int y_offset, int size2) {
//compute the max of size1 and (x_offset + size2).  Call this w

//compute the max of size1 and (y_offset + size2).  Call this h

//count from 0 to h. Call the number you count with y

//count from 0 to w. Call the number you count with x

//check if  EITHER
//    ((x is between x_offset  and x_offset +size2) AND
//     y is equal to either y_offset OR y_offset + size2 - 1 )
//  OR
//    ((y is between y_offset and y_offset + size2) AND
//     x is equal to either x_offset OR x_offset + size2 -1)
// if so, print a *

//if not,
// check if EITHER
//    x is less than size1 AND (y is either 0 or size1-1)
// OR
//    y is less than size1 AND (x is either 0 or size1-1)
//if so, print a #

//else print a space
//when you finish counting x from 0 to w,
//print a newlne
