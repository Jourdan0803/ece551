#include "sunspots.h"

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"

ss_monthly_t parseLine(char * line) {
  // WRITE ME
  unsigned year;
  unsigned month;
  double num;
  char * ptr = line;
  char remaining[100];
  // check the format of year
  while (ptr < line + 4) {
    if (!isdigit(*ptr)) {
      fprintf(stderr, "Error: Invalid year format.\n");
      exit(EXIT_FAILURE);
    }
    ptr++;
  }
  if (*ptr != '-') {
    fprintf(stderr, "Error: Year should be 4 digit.\n");
    exit(EXIT_FAILURE);
  }
  ptr++;
  // check format of month
  while (ptr < line + 7) {
    if (!isdigit(*ptr)) {
      fprintf(stderr, "Error: Invalid month format.\n");
      exit(EXIT_FAILURE);
    }
    ptr++;
  }
  if (*ptr != ',') {
    fprintf(stderr, "Error: Month should be 2 digit.\n");
    exit(EXIT_FAILURE);
  }
  //check if line follow the right data format YYYY_MM,DOUBLE
  if (sscanf(line, "%4u-%2u,%lf%99s", &year, &month, &num, remaining) != 3) {
    fprintf(stderr, "Error: Invalid input format.\n");
    exit(EXIT_FAILURE);
  }
  //check if month is between 01 and 12
  if (month > 12 || month < 1) {
    fprintf(stderr, "Error: Month should be within 01 through 12(inclusive).\n");
    exit(EXIT_FAILURE);
  }
  //check if number of sunspots is non-negative floating number
  if (num < 0) {
    fprintf(stderr, "Error: Number of sunspots should be non-negative.\n");
    exit(EXIT_FAILURE);
  }
  // add to ss_monthly_t
  ss_monthly_t ans;
  ans.year = year;
  ans.month = month;
  ans.num = num;
  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  //restricts w to be positive odd number,w<=n;
  if (w > n || w < 0 || w % 2 == 0) {
    fprintf(stderr, "Error:w should be an odd positive integer no more than n\n");
    exit(EXIT_FAILURE);
  }

  int center = (w - 1) / 2;
  for (int i = 0; i < n; i++) {
    int number = 0;
    double sum = 0.0;
    int lower = i - center;
    int upper = i + center;
    for (int j = lower; j <= upper; j++) {
      if (j <= n - 1 && j >= 0) {
        number += 1;
        sum += data[j].num;
      }
    }
    //copy month and year to mean
    mean[i].month = data[i].month;
    mean[i].year = data[i].year;
    mean[i].num = sum / number;
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  //restricts array to be non-zero;
  if (n == 0) {
    fprintf(stderr, "Error:0 element in array\n");
    exit(EXIT_FAILURE);
  }
  //calculate the max index
  size_t max_index = 0;
  for (size_t i = 1; i < n; i++) {
    if (data[i].num > data[max_index].num) {
      max_index = i;
    }
  }
  //calculate time stamps
  double time_stamp = data[max_index].year + data[max_index].month / 12.0;
  return time_stamp;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  //restricts n to be at least 2
  if (n < 2) {
    fprintf(stderr, "Error:n should be at least 2\n");
    exit(EXIT_FAILURE);
  }
  double sum_diff = 0;
  for (size_t i = 1; i < n; i++) {
    sum_diff += timeStamps[i] - timeStamps[i - 1];
  }
  double avr = sum_diff / (n - 1);
  return avr;
}
