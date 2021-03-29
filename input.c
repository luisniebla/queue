#include <stdio.h>

int detab(int);

/** 
    Copy input to uoutput and replace extra blanks with single blank.
    Also count blanks and tabs and newlines
**/
int main() {
  printf("Input");
  detab(4);
  // int count = 0;
  // char c;
  // while(c != EOF) {
  //   char nextC;
  //   nextC = getchar();
  //   if (nextC == ' ' && c == ' ') {
  //     ;
  //   } else {
  //     putchar(nextC);
  //   }
  //   c = nextC;
  //   if (c == ' ' || c == '\t' || c== '\n') {
  //     count++;
  //   }
  // }
  // printf("COUNT: %d", count);
  // return count;
}

// Replace tabs with space 
int detab(int n) {
  char input_program[5000];
  char c = getchar();
  for(int i = 0; i < 5000 || c != EOF; i++) {
    
    if (c == '\t') {
      for(int j = i; j < i + n; j++) {
        input_program[j] = ' ';
      }
    } else {
    input_program[i] = c;
    c = getchar();
    }
  }
  printf("%s", input_program);
}
