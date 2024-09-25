#include <stdio.h>

#define THRESHOLD 83

int get_line(char line[], int max_line_len);

int main(void) {
    int len, nextLen;
    char first[THRESHOLD];
    char continuous[THRESHOLD];

    while ((len = get_line(first, THRESHOLD)) > 0) {
        if (len == THRESHOLD-1) {
            // length contains \n (so +1 to actual count)
            printf("%s", first);
            nextLen = THRESHOLD-1;
            
            // check if the string terminated at exactly the 81st place by a newline.
            // If so, no need to look for new segments of same line input.
            if (first[81] != '\n') {
                while (nextLen == THRESHOLD-1) {
                    nextLen = get_line(continuous, THRESHOLD);
                    printf("%s", continuous);
                }
            }
        }
        len = 0;
    }
}

int get_line(char line[], int max_line_len)
{
  int c, i;

  for (i = 0; i < max_line_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';

  return i;
}
