#include <stdio.h>

#define MAXLINE 1000

//prototype functions
int getline(char s[]);

int main() {
  char line[MAXLINE]; // Need to define line here since we don't wanna return it as parameter
  printf("%d", getline(line));
}

int getline(char s[]) {
  char line[MAXLINE];
  char c;
  
  for(int i = 0; i < MAXLINE || c == EOF; i++) {
    c = getchar();
    line[i] = c;
    if (c == '\n') {
      return i;
    }
  }
  return -1
}
