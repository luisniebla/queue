#include <stdio.h>

int main() {
  char c = getchar();
  int nword = 0;
  
  while (c != EOF) {
    char peekAhead = getchar();
    if ((peekAhead == ' ' || peekAhead == '\n' || peekAhead == '\t') && c > 'a' && c < 'z') {
      nword++;
    }
    c = peekAhead;
  }
  printf("Word count: %d", nword);
}
