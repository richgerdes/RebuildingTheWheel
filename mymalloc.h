#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <string.h>

#define malloc(x) memMalloc(x,__FILE__, __LINE__)
#define calloc(x) memCalloc(x,__FILE__, __LINE__)
#define realloc(x,y) memRealloc(x,y,__FILE__, __LINE__)
#define free(x) memFree(x,__FILE__, __LINE__)


typedef struct _memBlock MemBlock;

struct _memBlock{
	MemBlock *next, *prev;
	unsigned int size, address;
	int free;
};

void* memMalloc(unsigned int s, char * fileName, unsigned int lineNum);
void* memCalloc(unsigned int s, char * fileName, unsigned int lineNum);
void* memRealloc(void* p, unsigned int s,char * fileName, unsigned int lineNum);
void memFree(void* p, char * fileName, unsigned int lineNum);
void printStats();

#endif
