#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
int currentAge;
double balance;

void calculation(int startAge, double initial, retire_info type) {
  currentAge = startAge;
  balance = initial;
  for (int i = 0; i < type.months; i++) {
    int ageYears = currentAge / 12;
    int ageMonths = currentAge % 12;
    printf("Age %3d month %2d you have $%.2f\n", ageYears, ageMonths, balance);
    balance += balance * type.rate_of_return;
    balance += type.contribution;
    currentAge++;
  }
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  calculation(startAge, initial, working);
  calculation(currentAge, balance, retired);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return 0;
}
