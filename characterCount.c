#include <stdio.h>

// Count the number of occurrences of each digit, whitespace, and all other characters
int main() {
  int c, i, whitespace_count, char_count;
  int ndigit[10];

  whitespace_count = char_count = 0;
  for(i = 0; i < 10; ++i)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      whitespace_count += 1;
    } else if (c >= '0' && c <= '9') {
      ndigit[c-'0'] += 1;
	} else {
      ++char_count;
    }
  }
  printf("Whitespace: %d, char_count: %d, ndigits: %d",
	 whitespace_count, char_count, ndigit[0]);
}
