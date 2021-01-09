#include <stdio.h>




/** 
    Copy input to uoutput and replace extra blanks with single blank.
    Also count blanks and tabs and newlines
**/
int main() {
  int count = 0;
  char c;
  while(c != EOF) {
    char nextC;
    nextC = getchar();
    if (nextC == ' ' && c == ' ') {
      ;
    } else {
      putchar(nextC);
    }
    c = nextC;
    if (c == ' ' || c == '\t' || c== '\n') {
      count++;
    }
  }
  printf("COUNT: %d", count);
  return count;
}

