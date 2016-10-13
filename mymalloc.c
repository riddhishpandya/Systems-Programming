/*
 * mymalloc.c
 */
#include <stdio.h>



static char myblock[5000];
char * ptr = myblock;


void * malloc (size_t size) {
	
	if(size == 0)  {
		return NULL;
	}

	/* find the next free block that is greater than requested size */
		
	return;
}

void free (void * mem_location) {
	
	if(mem_location == NULL) {
		return;
	}


	short int * footer = (char *)mem_location + *((short int *)mem_location) + 2; //footer of current block
	
	/* clear allocated bit */
	*((short int *)mem_location) = *((short int *)mem_location) & ~0x01;
	*footer = *((short int *)mem_location) & ~0x01;
	
	/* coalesce if next block is free */
	if(footer + 2 != myblock + 5000) {
		char * next_block = mem_location + *((short int *)mem_location) + 4; //pointer to next block
		int isallocated = *((short int *)next_block) & 0x01; //check allocated bit
		if(!isallocated) {

			short int new_size = *((short int *)mem_location) + *((short int *)next_block) + 4 //new size of free block
			*((short int *)mem_location) = new_size; //adds 4 because footer of current block and header of next block are added to data
			footer = (char *)mem_location + new_size + 2; //new location of footer at end of coalesced block
			*footer = new_size; //new size of free block
			
		}
	}
	/* coalesce if prev block is free */
	if(mem_location != myblock) {
		char * prev_block = mem_location - 2; //accesses footer of prev block
		short int old_size_of_prev_block = *((short int *)prev_block);
		isallocated = *((short int *)prev_block) & 0x01; //check allocated bit
		if(!isallocated) {
			/* new size of prev_block which combines with mem_location */
			short int new_size = *((short int *)prev_block) + *((short int *)mem_location) + 4; //adds 4 because footer of prev block and header of curr block are added to data
			*((short int *)prev_block) = new_size;
			prev_block = prev_block - 2 - old_size_of_prev_block; //header of prev_block
			*((short int *)prev_block) = new_size;
		}
	}	
	return;
}

int main( int number_of_args, char * arg_list[] ) {
 
    unsigned short size_t;
    printf("pointer is of size: %ld\n", sizeof(size_t));
}

>>>>>>> origin/Setup
