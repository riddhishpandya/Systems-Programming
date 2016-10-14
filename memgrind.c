#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"



void testA(){
	char* malloc_pointers[3000];
	int pointer_counter = 0;
	int workload_counter = 0;
	long int time_total = 0;

	while(workload_counter < 100) {
		struct timeval start, end;
		gettimeofday(&start, NULL);


  		while(pointer_counter < 3000) {

	  		malloc_pointers[pointer_counter] = malloc(1);
	  		pointer_counter++;

	  	}
	  	pointer_counter = 0;
	  	while(pointer_counter < 3000) {

	  		free(malloc_pointers[pointer_counter]);
	  		pointer_counter++;

	  	}
	  	gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;
	}
	long int average_time = time_total/100;
	printf("Average Time for Test A was %ld microseconds\n", average_time);	
}

void testB(){
	int pointer_counter = 0;
	int workload_counter = 0;
	long int time_total = 0;

	while(workload_counter < 100) {
		struct timeval start, end;
		gettimeofday(&start, NULL);


  		while(pointer_counter < 3000) {

	  		char* test_pointer = (char*)malloc(1);
	  		free(test_pointer);
	  		pointer_counter++;
	  	}

	  	gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;
	}
	long int average_time = time_total/100;
	printf("Average Time for Test B was %ld microseconds\n", average_time);	

}

void testC(){

}

void testD(){

}

void testEF(){

}


int main( int number_of_args, char* arg_list[] ) {
	block_init();
	testA();
	testB();
    
    return 0;
}