#include <stdio.h>

#define MAXLINE 100
#define ALPHABET 25

int main() {
  char c = getchar();
  int line[MAXLINE];
  int alpha_count[MAXLINE];
  for (int i = 0; i < MAXLINE; i++) {
      line[i] = 0;
  }
  for (int i = 0; i < MAXLINE; i++) {
      alpha_count[i] = 0;
  }
  int nword = 0;
  int length = 0;
  while (c != EOF) {
    char peekAhead = getchar();
    alpha_count[c] += 1;
    length++;
    if ((peekAhead == ' ' || peekAhead == '\n' || peekAhead == '\t') && c > 'a' && c < 'z') {
      nword++;
      line[length] += 1;
      length = 0;
    }
    c = peekAhead;
  }
  for (int i = 0; i < MAXLINE; i++) {
      if (line[i] > 0){
      printf("Length: %d - %d\n", i, line[i]);

      }
  }
  printf("Word count: %d\n", nword);
}
