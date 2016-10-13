#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"



void testA(){

	int counter = 0;
	char* malloc_pointers[3000];

	struct timeval start, end;
  	gettimeofday(&start, NULL);

  	while(counter < 3000) {

  		malloc_pointers[counter] = malloc(1);
  		counter++;

  	}

  	while(counter < 3000) {

  		free(malloc_pointers[counter]);
  		counter++;

  	}
 	

  	gettimeofday(&end, NULL);
  	printf("Time Required = %ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec)
	- (start.tv_sec * 1000000 + start.tv_usec)));	
}

void testB(){

}

void testC(){

}

void testD(){

}

void testEF(){

}


int main( int number_of_args, char* arg_list[] ) {


    
    return 0;
}