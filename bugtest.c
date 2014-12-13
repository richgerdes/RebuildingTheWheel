#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"



int main()
{

  atexit(printStats);
  //Mallocing test 	
  char* string = malloc(sizeof(char)*10);

  char* saturation = malloc(sizeof(char)*5001);
	
  
  char* notmalloc = "1";
  
  free(notmalloc);
	
  
  free(string);
  
  free(string);
	
  printList();
  //free(unkown);

  //calloc test
  char* callocd = calloc(sizeof(char)*5);

  printList();
  //Offset test
  char* offset = malloc(sizeof(char)*1);
  printList();
  free(offset + 10);

  printList();
  free(callocd);

  printList();
  char* alloc = realloc(offset, sizeof(char)*2);

  printList();
  free(alloc);
  
  printList();
  free(offset);
  printList();
  
  return 0;
}