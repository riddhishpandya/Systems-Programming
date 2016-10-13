<<<<<<< HEAD
/*
 * mymalloc.c
 */
#include <stdio.h>



static char myblock[5000];
char * ptr = myblock;
short int free_space = 4996;
* ((short int *)ptr) = 4996; // sets initial header size to 4996 
* (((short int *)(ptr + 4998))) = 4996; //sets initial footer size to 4996


void* malloc (size_t size) {

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
 
    unsigned short size_t;
    printf("pointer is of size: %ld\n", sizeof(size_t));
}

=======
#include <stdio.h>
>>>>>>> 4e8ac626801420eb5c3198165a86224d4e90d297
