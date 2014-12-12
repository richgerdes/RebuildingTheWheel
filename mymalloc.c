#include "mymalloc.h"


#define MEMBLOCK_SIZE (5000)

char memory_block[MEMBLOCK_SIZE];

void* memMalloc(unsigned int s, char * fileName, unsigned int lineNum){
	static int initial = 1;
	static MemBlock *head;
	MemBlock *curr, *new;

	if(initial){
		initial = 0;
		head = (MemBlock*)memory_block;
		head->prev = head->next = head;
		head->free = 1;
		head->size = MEMBLOCK_SIZE - sizeof(MemBlock);
	}

	curr = head->prev;
	unsigned int newSize = s + sizeof(MemBlock);	
	printf("-\n");
	do{
		if(curr->free && curr->size == s){
			curr->free = 0;
			printf("malloced new block of size %d at %p\n",s,((char*)curr + sizeof(MemBlock)));
			return (void *)((char*)curr + sizeof(MemBlock));
		}else if(curr->free && curr->size >= newSize){
			curr->size -= newSize;
			new = (MemBlock*) ((char*)(curr + sizeof(MemBlock)) + curr->size);
			new->next = curr->next;
			new->next->prev = new;
			curr->next = new;
			new->prev = curr;

			new->size = s;
			new->free = 0;
			printf("malloced new block of size %d at %p\n",s,(void *)((char*)new + sizeof(MemBlock)));
			return (void *)((char*)new + sizeof(MemBlock));
		}else
			curr = curr->prev;
	}while (curr != head->prev);
	printf("Saturation\n");
	return NULL;
	
}
void* memCalloc( unsigned int s,char * fileName, unsigned int lineNum){
	void* ptr = malloc(s);
	if(ptr != NULL)
		memset(ptr, 0, s);
	return ptr;
}

void* memRealloc(void* p, int s, char * fileName, unsigned int lineNum){
	void *ptr = malloc(s);
	memcpy(ptr, p, s);
	free(p);
	return ptr;
}

void memFree(void* p, char * fileName, unsigned int lineNum){

	static int initial = 1;
	static MemBlock *head;
	MemBlock *ptr, *prev;

	
	if(initial){
		initial = 0;
		head = (MemBlock*)memory_block;
	}
	if(p < (void*)&memory_block || p > (void*)(&memory_block + MEMBLOCK_SIZE)){
		printf("pointer %p was not in range\n",p);
		return;
	}
	ptr = (MemBlock*) (p - sizeof (MemBlock));

	if(ptr->prev != NULL && ptr->prev->next == ptr && !ptr->free){
		printf("Valid free, freeing block %p\n", p);
		prev = ptr->prev;
		ptr->next = ptr->next;
		ptr->free = 1;
		if(ptr->next != head && ptr->next->free && ptr->next != ptr){
			printf("Merging to the next block\n");
			ptr->size += sizeof(MemBlock) + ptr->next->size;
			ptr->next = ptr->next->next;
			ptr->next->prev = ptr;
		}

		if(ptr != head && prev->free && prev != ptr){
			printf("Merging with previous block\n");
			prev->size += sizeof(MemBlock) + ptr->size;
			prev->next = ptr->next;
			prev->next->prev = prev;
		}
	}else{
		printf("Invalid free or double free\n");
	}


}

