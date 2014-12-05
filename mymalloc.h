#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(x) memMalloc(x);
#define calloc(x) memCalloc(x);
#define remalloc(x) memReMalloc(x);
#define free(x) memFree(x);


typedef struct _memBlock MemBlock;

struct _memBlock{
	MemBlock next, prev;
	unsigned int size, address;
	int free;
}

void* memMalloc(unsigned int* s);
void memCalloc(unsigned int* s);
void memReMalloc(void* p);
void memfree(void* p);

#endif