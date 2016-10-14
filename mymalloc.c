/*
 * mymalloc.c
 */
#include <stdio.h>
#include "mymalloc.h"


static char myblock[5000];
char * ptr = &myblock[0];



void block_init() {
	short int * header_ptr = (short int *)&myblock[0];
	*header_ptr = 4996;
	short int * footer_ptr = (short int *)&myblock[4998];
	*footer_ptr = 4996;

}

void* malloc (size_t size) {
	ptr = myblock;
	//printf("ptr is at %p \n",ptr);
	if (size == 0) {
		return NULL;
	}
	if(size%2 != 0) {
		size = size + 1;
	}
	int n = 0;
	while(((*((short int *)ptr)) & 1) || (*((short int *)ptr)) <= size+4) {

		printf("ptr is at %p during %d loop\n",ptr, n);
		if (ptr + 4 + *((short int *)ptr) == myblock+5000) {
			//printf("ptr when NULL is at %p\n",ptr);
			/*return ERROR condition, because reached end of myblock and no 
			free blocks/no free block that fit space */
			printf("returns null\n");
			return NULL;

		}  
		/* go to next metadata to check if next bloxk is free since current block is not free 
           = current address + size of block + header + footer of current block  */
		short int int_actual_size = *((short int *)ptr) & ~0x01;
		ptr = ptr + int_actual_size + 4;
 		n++;
	}
	/*if code reaches here --> current address points to metadata of free block of >= size */
	short int free_block_size = *((short int *)ptr);
	//printf("free_block_size is at %hd\n",free_block_size);
	/*assign header and footer of newly-allocated block*/
	//printf("allocating at %p with size of %d\n",ptr, size);
	void * return_pointer = ptr + 2;
	*((short int *)ptr) = size | 0x01;
	short int * footer = (short int *)(ptr + 2 + size); 
	*(footer) = size | 0x01;

	/*splitting the free block after completing allocation of new space */
	ptr = ptr + size + 4;
	short int new_free_block_size = free_block_size - size - 4;
	//printf("new_free_block_size is at %hd\n",new_free_block_size);
	*((short int *)ptr) = new_free_block_size;
	//printf("ptr of free block %p\n",ptr);
	ptr = ptr + 2 + new_free_block_size;
	*((short int *)ptr) = new_free_block_size;





	return return_pointer; 

	
}

void free (void * mem_location) {
	
	if(mem_location == NULL) {
		return;
	}

	char * header = (char *)mem_location - 2;

	short int * footer = (short int *)(header + (*((short int *)(header)) & ~0x01)); //footer of current block

	printf("footer value: %hu\n", *footer);
	
	/* check to see if it is a pointer in the block (addresses that are not pointers is also checked here) */
	if(header < &myblock[0] || header > &myblock[4999]) { //if ptr is not in the block
		ERROR_NOT_ALLOCATED;
		return;
	}

	/* check to see if pointer was not allocated by malloc */
	if(*((short int *)(header)) != *footer) {
		printf("header value: %hu,  footer value: %hu\n", *((short int *)(header)), *footer);
		ERROR_NOT_ALLOCATED;
		return;
	}

	/* check to see if pointer is already freed */
	if(!(*((short int *)(header)) & 0x01)) { //check if allocated bit is 0
		ERROR_NOT_ALLOCATED;
		return;
	}
	/* clear allocated bit */
	*((short int *)header) = *((short int *)(header)) & ~0x01;
	*footer = *((short int *)(header)) & ~0x01;
	
	/* coalesce if next block is free */
	if((char*)footer + 2 != myblock + 5000) {
		char * next_block = (char *)header + 4 +*((short int *)header); //pointer to next block
		int isallocated = *((short int *)next_block) & 0x01; //check allocated bit
		if(!isallocated) {

			short int new_size = 4 + *((short int *)header) + *((short int *)next_block); //new size of free block
			*((short int *)header) = new_size; //adds 4 because footer of current block and header of next block are added to data
			footer = (short int *)(header + new_size + 2); //new location of footer at end of coalesced block
			*footer = new_size; //new size of free block
			
		}
	}
	/* coalesce if prev block is free */
	if(header != myblock) {
		char * prev_block = header - 2; //accesses footer of prev block
		short int old_size_of_prev_block = *((short int *)prev_block);
		int isallocated = *((short int *)prev_block) & 0x01; //check allocated bit
		if(!isallocated) {
			/* new size of prev_block which combines with header */
			short int new_size = *((short int *)prev_block) + *((short int *)header) + 4; //adds 4 because footer of prev block and header of curr block are added to data
			*((short int *)prev_block) = new_size;
			prev_block = prev_block - 2 - old_size_of_prev_block; //header of prev_block
			*((short int *)prev_block) = new_size;
		}
	}	
	return;
}

int main( int number_of_args, char * arg_list[] ) {

	block_init();

	/*int x;
	free( &x );
	
	char * p = (char *)malloc( 200 );
	free( p + 10 );
	
	int * y;
	free( y );

	char * p2 = (char*)malloc(100);
	free( p2 );
	free( p2 );

	/*this should work */
	printf("this should work\n");
	char * p3 = (char *)malloc( 100 );
	free( p3 );
	printf("this should work\n");
	p3 = (char *)malloc( 100 );
	free( p3 );
	/*
	char* p4 = (char*)malloc(5001);

	char* p5 = (char*)malloc(5000);
	char* p6 = (char*)malloc(1);
	*/
	//int * i = malloc(4);
	return 0;

}
