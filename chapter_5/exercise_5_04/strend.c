#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(void)
{
  char *s = "This si a simple string";
  char *t1 = "string";
  char *t2 = "random string";

  // Test if the string t1 occurs at the end of string s.
  if (strend(s, t1))
    puts("The string t1 orrurs at the end of the string s.");
  else
    puts("The string t1 doesn't orrur at the end of the string s.");

  // Test if the string t2 occurs at the end of string s.
  if (strend(s, t2))
    puts("The string t2 orrurs at the end of the string s.");
  else
    puts("The string t2 doesn't orrur at the end of the string s.");

  return 0;
}

//  Returns 1 if the string t occurs at the end of the string s, and zero otherwise.
int strend(char *s, char *t)
{
  // Determine the lengths of the strings.
  size_t s_length = strlen(s);
  size_t t_length = strlen(t);

  // Move the s & t pointer to the end of the corresponding strings.
  s += s_length - 1;
  t += t_length - 1;

  // Check backwards if each character from string t occurs in the corresonding
  // location from the string s.
  while (*s-- == *t--)
    --t_length;

  return !t_length;
}
