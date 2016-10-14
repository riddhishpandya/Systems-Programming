/*
 * mymalloc.c
 */
#include <stdio.h>


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

		//printf("ptr is at %p during %d loop\n",ptr, n);
		if (ptr + 4 + *((short int *)ptr) == myblock+5000) {
			//printf("ptr when NULL is at %p\n",ptr);
			/*return ERROR condition, because reached end of myblock and no 
			free blocks/no free block that fit space */
			//printf("returns null\n");
			return NULL;

		}  
		/* go to next metadata to check if next bloxk is free since current block is not free 
           = current address + size of block + header + footer of current block  */
		short int int_actual_size = *((short int *)ptr) & ~0x01;
		ptr = ptr + int_actual_size + 4;
 		n++;
	}
	//printf("successful malloc\n");
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

	char * mem_location_ptr = (char *)mem_location;

	short int * footer = (short int *)(mem_location_ptr+ 2 + *((short int *)mem_location_ptr)); //footer of current block
	
	/* clear allocated bit */
	*((short int *)mem_location_ptr) = *((short int *)mem_location_ptr) & ~0x01;
	*footer = *((short int *)mem_location_ptr) & ~0x01;
	
	/* coalesce if next block is free */
	if((char*)footer + 2 != myblock + 5000) {
		char * next_block = (char *)mem_location_ptr + 4 +*((short int *)mem_location_ptr); //pointer to next block
		int isallocated = *((short int *)next_block) & 0x01; //check allocated bit
		if(!isallocated) {

			short int new_size = 4 + *((short int *)mem_location_ptr) + *((short int *)next_block); //new size of free block
			*((short int *)mem_location_ptr) = new_size; //adds 4 because footer of current block and header of next block are added to data
			footer = (short int *)(mem_location_ptr + new_size + 2); //new location of footer at end of coalesced block
			*footer = new_size; //new size of free block
			
		}
	}
	/* coalesce if prev block is free */
	if(mem_location_ptr != myblock) {
		char * prev_block = mem_location_ptr - 2; //accesses footer of prev block
		short int old_size_of_prev_block = *((short int *)prev_block);
		int isallocated = *((short int *)prev_block) & 0x01; //check allocated bit
		if(!isallocated) {
			/* new size of prev_block which combines with mem_location_ptr */
			short int new_size = *((short int *)prev_block) + *((short int *)mem_location_ptr) + 4; //adds 4 because footer of prev block and header of curr block are added to data
			*((short int *)prev_block) = new_size;
			prev_block = prev_block - 2 - old_size_of_prev_block; //header of prev_block
			*((short int *)prev_block) = new_size;
		}
	}	
	return;
}

// int main( int number_of_args, char * arg_list[] ) {

// 	block_init();
// 	printf("ptr is at %p\n",ptr);
// 	// int * one = (int*) malloc(1000);
// 	// int * two = (int*) malloc(1000);
// 	// int * three = (int*) malloc(1000);
// 	// int * four = (int*) malloc(1000);
// 	// int * five = (int*) malloc(1000);
// 	//free(c);
// 	//int * i = malloc(4);
// 	return 0;

// }
