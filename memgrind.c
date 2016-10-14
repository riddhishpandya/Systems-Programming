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

   int malloc_counter = 0;
   int free_counter = 0;
   int total_counter = 0;
   time_t t;
  
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   while(total_counter < 6000) {

   		int random_number = rand() % 2;
   		if(random_number == 0 && malloc_counter < 3000) {
   			malloc_counter++;
   			total_counter++;
   		}else if (random_number == 1 && free_counter < 3000) {
   			free_counter++;
   			total_counter++;
   		}

   }
   printf("total_counter is: %d\nmalloc_counter is: %d\nfree_counter is: %d\n",total_counter,malloc_counter,free_counter);

}
void testD(){

}

void testEF(){

}


int main( int number_of_args, char* arg_list[] ) {
	block_init();
	testA();
	testB();
	testC();
    
    return 0;
}