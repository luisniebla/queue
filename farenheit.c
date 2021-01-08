#include <stdio.h>

void loop_farenheit() {
  for(float i = 0; i < 300; i += 10) {
    printf("%3f, %6.1f\n", i, 5.0 * (i - 32.0) /9.0);
  }
  for(float i = 300; i > 0; i-=10) {
    printf("%3f, %6.1f\n", i, 5.0 * (i - 32.0) / 9.0);
  }
}
  
int floating_farenheit() {
  float lower, upper;

  lower = 0.0;
  upper = 300.0;

  while (lower < upper) {
    // Remember that declaring flaots is important again
    float celsius = 5.0 * (lower - 32.0) / 9.0;
    // 6.1 indicated at least six characters wide, 1 digit after decimal point
    printf("%3f %3f\n", lower, celsius);
    lower += 10.0;

  }
  return 0;
}

int main() {
  int lower = 0;
  int upper = 300;

  printf("%3s %3s", "Farenheit", "Celsius\n");
  while (lower < upper) {
    int celsius = 5 * (lower - 32) / 9;
    printf("%3d %3d\n", lower, celsius);
    lower += 10;
  }

  printf("--------\n");
  floating_farenheit();

  printf("----loop----\n");
  loop_farenheit();
}
