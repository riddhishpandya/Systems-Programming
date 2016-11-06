 /*
 * mymalloc.h
 */
#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__


#define malloc(size) mymalloc(size, __FILE__, __LINE__) 
#define free(mem_location) myfree(mem_location , __FILE__, __LINE__ )

#define ERROR_NOT_ALLOCATED printf("ERROR: Attempted to free an unallocated block. Line: %d File: %s\n", __LINE__, __FILE__);

void block_init();
void* mymalloc (size_t size, char* file, int line);
void myfree (void * mem_location, char* file, int line);


#endif