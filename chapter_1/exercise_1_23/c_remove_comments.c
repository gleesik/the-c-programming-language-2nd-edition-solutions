/* EXERCISE 1-23.
 *
 * Write a program to remove all comments from a C program. Don't
 * forget to handle quoted strings and character constants properly. C comments
 * don't nest. */

#include <stdbool.h>
#include <stdio.h>
#define MAXTEXTLEN 10000

// declarations
// takes text and removes all '/*..*/' comments
void del_star_coms(char text[], char text_no_coms[]);
// takes text and removes all '//' comments
void del_oneline_coms(char text_[], char text_no_coms_[]);

int main(void) {

  int i = 0;
  char c;
  char text[MAXTEXTLEN], text_no_star_coms[MAXTEXTLEN],
      text_no_dash_coms[MAXTEXTLEN];

  while ((c = getchar()) != EOF) {

    text[i++] = c;
  }

  text[i] = '\0';

  del_star_coms(text, text_no_star_coms);
  del_oneline_coms(text_no_star_coms, text_no_dash_coms);

  printf("%s", text_no_dash_coms);
  return 0;
}

// defs
/* text is copied to text_no_coms */
void del_star_coms(char text[], char text_no_coms[]) {
  int j = 0, i = 0;
  bool in_comment = false;
  char c, chc[2];

  while (text[i] != EOF) {

    c = text[i];

    if (i > 0) {

      // placeholder for "/*", "*/" and "//" checker
      chc[0] = chc[1];
      chc[1] = c;

      // determine if in comment
      if ((chc[0] == '/') & (chc[1] == '*')) {
        in_comment = true;
        j--; // remove previous "/"
      }

      if (in_comment) {

        // determine if terminate comment flag
        if ((chc[0] == '*') & (chc[1] == '/')) {
          in_comment = false;
        }

      } else {
        text_no_coms[j++] = c;
      }
    } else {

      chc[1] = c;
      text_no_coms[j++] = c;
    }

    i++;
  }

  text_no_coms[j] = '\0';
}

void del_oneline_coms(char text_[], char text_no_coms_[]) {
  int j = 0, i = 0;
  bool in_comment = false;
  char c, chc[2];

  while (text_[i] != EOF) {

    c = text_[i];

    if (i > 0) {

      // placeholder for "/*", "*/" and "//" checker
      chc[0] = chc[1];
      chc[1] = c;

      // determine if in comment
      if ((chc[0] == '/') & (chc[1] == '/')) {
        in_comment = true;
        j--; // remove previous "/"
      }

      if (in_comment) {

        // determine if terminate comment flag
        if (c == '\n') {
          in_comment = false;
        }

      } else {
        text_no_coms_[j++] = c;
      }
    } else {

      chc[1] = c;
      text_no_coms_[j++] = c;
    }

    i++;
  }
  text_no_coms_[j] = '\0';
}
