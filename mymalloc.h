#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#define ERROR_NOT_ALLOCATED printf("ERROR: Attempted to free an unallocated block. Line: %d File: %s\n", __LINE__, __FILE__);


void block_init();
void* malloc(size_t size);
void free(void * mem_location);

#endif