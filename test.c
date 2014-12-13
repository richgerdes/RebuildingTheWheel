#include <stdio.h>
#include <string.h>
#include "mymalloc.h"



int main (int argc, char *argv[]){

  int num;

  if (argc != 2){
      printf ("Please enter executable and the test case number, 1 to 3\n");
      return 0;
  }
  num = atoi (argv[1]);

  printf ("User entered case: %d\n", num);

  if (num == 1){
      
		/*-----Mallocing test-----*/	char *string = malloc (sizeof (char) * 10);

		/*-----Mallocing more then 5000-----*/ 
      	char *sat = malloc (sizeof (char) * 5001);
	if(sat == NULL){	
		printf("Saturation equals NULL\n");
	}
		/*-----Not mallocing properly, then freeing an the non malloced space-----*/ 
      	char *notmalloc = "1";
	free (notmalloc);
      	printStats ();	/*-----Print the fragmentation stats and leak defection stats-----*/

      		/*-----Freeing the malloced string but double freeing it again-----*/ 
	free (string);
     	free (string);
     	printStats ();

		/*-----Calloc test-----*/ 
      	char *calloc = calloc (sizeof (char) * 5);
      
		/*-----Offset set-----*/ 
      	char *offset = malloc (sizeof (char) * 1);
      	free (offset + 10);
	printStats ();

		/*-----Freeing the calloced-----*/
      	free (calloc);
	printStats ();

		/*-----Realloc test-----*/
      	char *alloc = realloc (offset, sizeof (char) * 2);
      	free (alloc);
	printStats ();

    }else if (num == 2){

		/*-----Freeing Pointer that was never allocated-----*/
	int noalloc; 
	int *alloc;
	
	alloc = malloc(10*sizeof(int));
	free(&noalloc);
	printStats();

		/*-----Freeing in the middle of the block-----*/
	free(alloc+1);
	printStats();

		/*-----Valid free-----*/
	free(alloc);
	printStats();

		/*-----Reallocting memory-----*/
	char *test = malloc(sizeof(char)*5);
	char *Realloc = realloc(test, sizeof(char)*1);
      	free(Realloc);
	printStats();
	free(test);
	printStats();
	
		/*-----redundant freeing-----*/

	char *redun = malloc(sizeof(char));
	free(redun);
	free(redun);
	printStats();
	
    }else if(num == 3){
  	
  	char* string = malloc(sizeof(char)*10);

  	char* saturation = malloc(sizeof(char)*5001);
	if(saturation == NULL){	
		printf("Saturation equals NULL\n");
	}
	
  	char* notmalloc = "1";
  	free(notmalloc);
	
  	
  	free(string);
  	free(string);
	printList();
  
  	char* callocd = calloc(sizeof(char)*5);
	printList();
  
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
    }else{
	printf("Error you have entered case: %d that is incorrect 1 to 3 only\n", num);
    }
  
  return 0;

}
  
