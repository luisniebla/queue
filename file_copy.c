#include <stdio.h>

int main() {
  int c;
  printf("Boolean expression: %d\n", getchar() != EOF); // Booleans evaluate to digits
  printf("%d", EOF); // Lets see, the result is -1
  c = getchar();
  while (c != EOF) {
    putchar(c);
    c = getchar();
  }
}
