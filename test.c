#include "mymalloc.h"

#include <stdio.h>
#include <string.h>


int main()
{
  //int unkown;

  char* string = malloc(sizeof(char)*10);

  char* saturation = malloc(sizeof(char)*5001);

  char* notmalloc = "1";
  free(notmalloc);

  free(string);
  free(string);

  //free(unkown);

  //calloc test
  char* callocd = calloc(sizeof(char)*1);

  //Offset test
  char* offset = malloc(sizeof(char)*1);
  free(offset + 10);

  return 0;
}
