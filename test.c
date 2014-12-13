/*#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"mymalloc.h"

#define TA_TEST_BLOCKSIZE 100


//number in range [0,max)
int random_with_max(unsigned int max)
{
  return rand()%max;
}

//true if element found, false otherwise.  Assumes elements are normally >=0
int removefromarr(int n,int*arr,int len){
	printf("removefromarr\n");
	int i = 0;
	while(i < len){
		if(arr[i] == n){
			arr[i] = -1;
			printf("found\n");
			return 1;
		}
		i++;
	}
	printf("not found\n");
	return 0;
}

//Some of these test cases use the library functions calloc and realloc.  Cheating, I know. :P
int main(int argc, char*argv[]){
    
    int casenum;
    
    
    if(argc != 2){
        printf("Usage: ./assignment6_ta_tests <int>casenum\n");
        return 0;
    }
    casenum = atoi(argv[1]);
    
    
    printf("Case num: %d\n",casenum);
    
    if(casenum == 1){
        //    1. free pointer never allocated
        int i;
        int *ip;
        printf("\tTA: Mallocing pointer\n");
        ip = malloc(sizeof(int));
        printf("\tTA: Freeing pointer %p\n",&i);
        free(&i);
        printf("Done\n");
        
    }else if(casenum == 2){
        //    2. free pointer in middle of allocated memory block
        int *ip;
        printf("\tTA: Mallocing pointer\n");
        ip = malloc(10*sizeof(int));
        printf("\tTA: Freeing pointer %p\n",ip+7);
        free(ip+7);
        printf("Done\n");

    }else if(casenum == 3){
        //    3. free pointer between two memory blocks

        char *cp;
        int *ipnext;
        printf("\tTA: Mallocing pointer\n");
        cp = malloc(10*sizeof(char));
        printf("\tTA: Mallocing pointer\n");
        ipnext = malloc(10*sizeof(int));
        printf("\tTA: Freeing pointer %p\n",cp+12);
        free(cp+12);
        printf("Done\n");

    }else if(casenum == 4){
        //    4. freeing pointer a couple bytes before memory block (so into MemEntry struct). Then attempt another malloc.
        char* cp;
        int*ip;
        printf("\tTA: Mallocing pointer\n");
        cp = malloc(15*sizeof(char));
        printf("\tTA: Freeing pointer %p\n",cp-2);
        free(cp-2);
        printf("\tTA: Mallocing pointer\n");
        ip = malloc(16*sizeof(int));
        printf("Done\n");

    }else if(casenum == 5){
        //    5.  redundant freeing of same pointer.
        int *ip1;
        printf("\tTA: Mallocing pointer\n");
        ip1 = malloc(10*sizeof(int));
        printf("\tTA: Freeing pointer %p\n",ip1);
        free(ip1);
        printf("\tTA: Freeing pointer %p\n",ip1);
        free(ip1);
        printf("Done\n");

        
    }else if(casenum == 6){
        //    6.  saturation with a while loop.  Program should not fail.
        int pcount = 0;
        while(malloc(TA_TEST_BLOCKSIZE*sizeof(int))){
			pcount++;
			printf("Allocated %d pointers of size %d\n",pcount,TA_TEST_BLOCKSIZE);
		}
        printf("Done\n");

        
    }else if(casenum == 7){
        //    7.  Saturation, then freeing everything, then saturation with same list of malloc's (should yield same # pointers)
        int *ip;
        int pcount = 0;
        int *doubleip[5000];
        while((ip = malloc(TA_TEST_BLOCKSIZE*sizeof(int)))){
	    doubleip[pcount++] = ip;
            printf("TA: allocated %d blocks of size %d so far\n", pcount, TA_TEST_BLOCKSIZE);
        }

	printf("Saturated. start freeing\n");        

        //free
        int i;
        int cap = pcount;
        for(i = 0; i < cap; i++){
			free(doubleip[i]);
		}
	printf("remalloc\n");        

        //malloc again
        int secondpcount = 0;
        while(malloc(TA_TEST_BLOCKSIZE*sizeof(int))){
            secondpcount++;
        }
        
        if(pcount == secondpcount){
            printf("\tPassed.\n");
        }else{
            printf("\tFailed\n");
        }
        
        printf("Done\n");

    }else if(casenum == 8){
        //    8.  Regular call to malloc (with some modifications of pointer)
        
        int *x;
        int *y;
        printf("\tTA: Mallocing pointer\n");
        x = malloc(sizeof(int));
        printf("\tTA: Mallocing pointer\n");
        y = malloc(sizeof(int));

        *x = 5;
        *y = 7;
        printf("\tBefore swap: x=%d,y=%d\n",*x,*y);
        int temp;
        temp = *x;
        *x = *y;
        *y = temp;
        printf("\tAfter swap: x=%d,y=%d\n",*x,*y);
        printf("Done\n");
    }else if(casenum == 9){
        //    9.  Regular call to free (with some modifications of pointer before free)
        int *x;
        int *y;
        printf("\tTA: Mallocing pointer\n");
        x = malloc(sizeof(int));
        printf("\tTA: Mallocing pointer\n");
        y = malloc(sizeof(int));
        
        *x = 5;
        *y = 7;
        printf("\tBefore swap: x=%d,y=%d\n",*x,*y);
        int temp;
        temp = *x;
        *x = *y;
        *y = temp;
        printf("\tAfter swap: x=%d,y=%d\n",*x,*y);
        printf("\tTA: Freeing pointer %p\n",x);
        free(x);
        printf("\tTA: Freeing pointer %p\n",y);
        free(y);
        printf("Done\n");

    }else if(casenum == 10){
        //   10.  A trickier set of malloc's and free's.
        int **matrix;
        printf("\tAllocating matrix\n");
        matrix = malloc(10*sizeof(int*));
        int i;
        for(i = 0; i < 10; i++){
            matrix[i] = malloc(10*sizeof(int));
        }
        printf("\tFreeing matrix\n");
        for(i = 0; i < 10; i++){
            free(matrix[i]);
        }
        free(matrix);
        printf("Done\n");
    }else if(casenum == 11){
	//  11. Free pointer never allocated (free with no initial malloc's)
	int *ip=(int*)50000;
	
	free(ip);
		
    }else if(casenum == 12){
	//  12.  Random mallocs and frees
	int*ip;
        int pcount = 0;
        int *doubleip[5000];
        while((ip = malloc(TA_TEST_BLOCKSIZE*sizeof(int)))){
            doubleip[pcount++] = ip;
            printf("TA: allocated %d blocks of size %d so far\n", pcount, TA_TEST_BLOCKSIZE);
        }
		printf("Saturated. start freeing\n");        

        //free
        int i;
        int cap = pcount;
        
		int left_to_free[cap];    
        
        for (i=0;i<cap;i++) { 
			left_to_free[i] = i; 
		}
		
	    i = 0;
	    		
	    while(1){
			int done = 1;
			for(i = 0; i < cap; i++){
				if (left_to_free[i] != -1)
					done = 0;
			}
			if(done) break;
			int ind;
			while(!removefromarr((ind = random_with_max(cap)),left_to_free,cap));
			free(doubleip[ind]);
	    }
	    
        printf("remalloc\n");
        
        //malloc again
        int secondpcount = 0;
        while(malloc(TA_TEST_BLOCKSIZE*sizeof(int))){
            secondpcount++;
        }
        
        if(pcount == secondpcount){
            printf("\tPassed.\n");
        }else{
            printf("\tFailed\n");
        }
        
        printf("Done\n");
		
	}
    return 0;
}
*/

#include "mymalloc.h"

#include <stdio.h>
#include <string.h>


int main()
{
  atexit(printStats);
  //Mallocing test 	
  char* string = malloc(sizeof(char)*10);
	

  char* saturation = malloc(sizeof(char)*5001);
	
	printf("-\n");
  char* notmalloc = "1";
  free(notmalloc);
	
  printStats();
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
  return 0;
}

