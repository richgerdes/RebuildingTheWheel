#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"



int main()
{
	void* ptr = malloc(1);
	printStats();
	
	printList();
	
	free(ptr);
	
	printList();
	
	

	return 0;
}