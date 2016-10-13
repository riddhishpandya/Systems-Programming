<<<<<<< HEAD
/*
 * mymalloc.c
 */
#include <stdio.h>



static char myblock[5000];
char * ptr = myblock;
<<<<<<< HEAD
=======
short int free_space = 4996;
* ((short int *)ptr) = 4996; // sets initial header size to 4996 
* (((short int *)(ptr + 4998))) = 4996; //sets initial footer size to 4996
>>>>>>> 691d6c253f47314f1941f5e09a3f67bf2347e3fa


void * malloc (size_t size) {
	
	if(size == 0)  {
		return NULL;
	}

<<<<<<< HEAD
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
=======
	if (size == 0) {
		return NULL;
	}
	if(size%2 != 0) {
		size = size + 1;
	}

	while(((*((short int *)ptr)) & 1) || (*((short int *)ptr)) <= size+4) {

		if (ptr + 4 + *((short int *)ptr) == myblock+5000) {

			/*return ERROR condition, because reached end of myblock and no 
			free blocks/no free block that fit space */
			return NULL;

		}  
		/* go to next metadata to check if next bloxk is free since current block is not free 
           = current address + size of block + header + footer of current block  */
		ptr = ptr + *((short int *)ptr) + 4;
 	
	}
	/*if code reaches here --> current address points to metadata of free block of >= size */
	short int free_block_size = *((short int *)ptr);

	/*assign header and footer of newly-allocated block*/
	void * return_pointer = ptr + 2;
	*((short int *)ptr) = size | 0x01;
	short int * footer = ptr + 2 + size; 
	*(footer) = size | 0x01;

	/*splitting the free block after completing allocation of new space */
	ptr = ptr + size + 4;
	short int new_free_block_size = free_block_size - size - 4;
	*((short int *)ptr) = new_free_block_size;
	ptr = ptr + 2 + new_free_block_size;
	*((short int *)ptr) = new_free_block_size;





	return return_pointer; 

	
}

void free (void * ptr) {
	return;
}

int main (int number_of_args, char * arg_list[] ) {
>>>>>>> 691d6c253f47314f1941f5e09a3f67bf2347e3fa
 
    unsigned short size_t;
    printf("pointer is of size: %ld\n", sizeof(size_t));
}

<<<<<<< HEAD
=======
#include <stdio.h>
>>>>>>> 4e8ac626801420eb5c3198165a86224d4e90d297
=======
>>>>>>> origin/Setup
>>>>>>> cc8f90cd9712e598a873ee3ba677e3cccd9ad38a
