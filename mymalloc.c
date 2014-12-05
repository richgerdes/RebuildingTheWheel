#include "mymalloc.h"

#define MEMBLOCK_SIZE (5000)

char memory_block[MEMBLOCK_SIZE];

void* memMalloc( unsigned int s){
	static int initial = 1;
	static MemBlock *head;
	MemBlock *curr, *new;

	if(initial){
		initial = 0;
		head = (MemBlock*)memory_block;
		head->prev = head->next = head;
		head->free = 1;
	}

	curr = head;
	unsigned int newSize = s + sizeof(MemBlock);	

	do{
		if(curr->free && curr->size = s){
			curr->free = 0;
			return (void *)(curr + sizeof(MemBlock);
		}else if(curr->free && curr->size >= newSize){
			curr->size -= newSize;
			new = (MemBlock*) (curr + sizeof(MemBlock) + curr->size)

			new->next = curr->next;
			new->next->prev = new;
			curr->next = new;
			new->prev = curr;

			new->size = s;
			new->free = 0;
	
			return (void *)(new + sizeof(MemBlock);
		}else
			curr = curr->next;
	}while (curr != head);

	return NULL;
	
}
void* memCalloc( unsigned int s){
	void* ptr = malloc(s);
	if(ptr != NULL)
		memset(ptr, 0, s);
	return ptr;
}

void* memRealloc(void* p, int s){
	void *ptr = malloc(s);
	memcpy(ptr, p, s);
	free(p);
	return ptr;
}

void memfree(void* p){

	MemBlock* ptr, prev;

	ptr = (MemBlock*) p;

	if(ptr->prev->next == ptr && !ptr->free){
		prev = ptr->prev;
		next = ptr->next;
		ptr->free = 1;
		if(next != head && next->free && next != ptr){
			ptr->size += sizeof(MemBlock) + next->size;
			ptr->next = next->next;
			ptr->next->prev = ptr;
		}

		if(curr != head && prev->free && prev != ptr){
			prev->size += sizeof(MemBlock) + ptr->size;
			prev->next = ptr->next;
			prev->next->prev = prev;
		}

	}


}

