#include "mymalloc.h"

#include <stdio.h>
#include <string.h>


int main()
{
  /* Mallocing test */	
  char* string = malloc(sizeof(char)*10);
	

  char* saturation = malloc(sizeof(char)*5001);
	
	printf("-\n");
  char* notmalloc = "1";
  free(notmalloc);
	
	printf("-\n");
  free(string);
  free(string);
	
	printf("-\n");
  //free(unkown);

  //calloc test
  char* callocd = calloc(sizeof(char)*5);

  //Offset test
  char* offset = malloc(sizeof(char)*1);
  free(offset + 10);

  free(callocd);

  char* alloc = realloc(offset, sizeof(char)*2);

  free(alloc);	
	printf("-\n");
  printStats();
  return 0;
}
