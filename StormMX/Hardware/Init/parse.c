/* Abstract: Routines for parsing command line arguments. */

/* Copyright 1999-2002 chaos development. */

#include <enviroment.h>
#include "Include/parse.h"

/* Split the command line parameters in words (separated by one or
   more spaces). */

unsigned int arguments_parse (
  char *source, 
  char **array_of_pointers)
{
  unsigned int number_of_arguments = 0;
  unsigned int position;
  char waited_char = ' ';
  int state = 0;

  for(position = 0;source[position] != '\0';position++)
  {
    if (state == 0)
    {
      if (source[position] == waited_char)
      {
        continue;
      }
      else if (source[position] == '\"')
      {
        waited_char = '\"';
        array_of_pointers[number_of_arguments] = source + position + 1;
        number_of_arguments++;
      }
      else if (source[position] == '\'')
      {
        waited_char = '\'';
        array_of_pointers[number_of_arguments] = source + position + 1;
        number_of_arguments++;
      }
      else
      {
        array_of_pointers[number_of_arguments] = source + position;
        number_of_arguments++;
      }
      state = 1;
    }
    else if (state == 1)
    {
      if (source[position] == waited_char)
      {
        state = 0;
	source[position] = 0;
        waited_char = ' ';
      }
    }
  }

  return number_of_arguments;
}
