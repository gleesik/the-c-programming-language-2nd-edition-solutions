#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_TAB_LENGTH 8

int is_str_uint(char *str);
int is_tab_stop_arg_list_valid(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!is_tab_stop_arg_list_valid(argc, argv))
  {
    puts("ERROR: Invalid arguments.\n");
    return EXIT_FAILURE;
  }

  int c;
  unsigned int arg_pos = 1;
  unsigned int line_pos = 0;
  unsigned int tab_stop = DEFAULT_TAB_LENGTH;
  unsigned int nr_of_spaces;
  unsigned int nr_of_custom_tab_stops;
  unsigned int initial_nr_of_custom_tab_stops = argc - 1;

  unsigned int custom_tab_stop = 0;
  unsigned int custom_line_pos_start = 0;

  for (unsigned int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      custom_line_pos_start = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
    else if (argv[i][0] == '+')
    {
      custom_tab_stop = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
  }

  nr_of_custom_tab_stops = initial_nr_of_custom_tab_stops;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      if (nr_of_custom_tab_stops)
      {
        tab_stop = atoi(argv[arg_pos++]);
        --nr_of_custom_tab_stops;
      }
      else if (custom_tab_stop)
      {
        tab_stop = custom_tab_stop;
      }
      else if (initial_nr_of_custom_tab_stops)
      {
        tab_stop = 1;
      }

      if (custom_line_pos_start)
      {
        if (line_pos >= custom_line_pos_start)
        {
          nr_of_spaces = tab_stop;
        }
        else
        {
          nr_of_spaces = 1;
        }
      }
      else
      {
        nr_of_spaces = tab_stop - line_pos % tab_stop;
      }

      while (nr_of_spaces)
      {
        putchar(' ');
        ++line_pos;
        --nr_of_spaces;
      }
    }
    else
    {
      putchar(c);
      ++line_pos;

      if (c == '\n')
      {
        arg_pos = 1;
        line_pos = 0;
        nr_of_custom_tab_stops = initial_nr_of_custom_tab_stops;
      }
    }
  }

  return EXIT_SUCCESS;
}

int is_str_uint(char *str)
{
  for (unsigned int i = 0; i < strlen(str); ++i)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }
  return 1;
}

int is_tab_stop_arg_list_valid(int argc, char *argv[])
{
  for (unsigned int i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-' || argv[i][0] == '+')
    {
      if (argc > 3 || !is_str_uint(argv[i] + 1))
      {
        return 0;
      }
      continue;
    }

    if (!is_str_uint(argv[i]) || (i > 1 && atoi(argv[i - 1]) > atoi(argv[i])))
    {
      return 0;
    }
  }
  return 1;
}

// NOTE: The current program works in a similar fashion as expand.
// run: ./detab 4 8 12 16 < file_tabs.txt > file_spaces.txt
// run: ./detab +8 -2 < file_tabs.txt > file_spaces.txt
