#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"

struct testC_node {
   char * ptr; 
   struct node *next;
};

void testA(){
	int null_counter = 0;
	char* malloc_pointers[3000];
	int pointer_counter = 0;
	int workload_counter = 0;
	long int time_total = 0;

	while(workload_counter < 100) {
		block_init();
		pointer_counter = 0;

		struct timeval start, end;
		gettimeofday(&start, NULL);


  		while(pointer_counter < 3000) {

	  		malloc_pointers[pointer_counter] = malloc(1);
	  		//printf("mallocced address is %p\n\n", malloc_pointers[pointer_counter]);
	  		if(malloc_pointers[pointer_counter] == NULL) {
	  			null_counter++;
	  		}
	  		pointer_counter++;

	  	}
	  	pointer_counter = 0;
	  	while(pointer_counter < 3000) {

	   		//printf("freeing address is %p\n", malloc_pointers[pointer_counter]);
	  		free(malloc_pointers[pointer_counter]);
	  		pointer_counter++;

	  	}
	  	gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;
	}
	int average_nulls = null_counter/100;
	long int average_time = time_total/100;
	printf("Average Null Mallocs for Test A was %ld\n", average_nulls);	
	printf("Average Time for Test A was %ld microseconds\n", average_time);	
}

void testB(){
	int null_counter = 0;
	int pointer_counter = 0;
	int workload_counter = 0;
	long int time_total = 0;

	while(workload_counter < 100) {
		block_init();
		pointer_counter = 0;

		struct timeval start, end;
		gettimeofday(&start, NULL);


  		while(pointer_counter < 3000) {

	  		char* test_pointer = (char*)malloc(1);
	  		if(test_pointer == NULL) {
	  			null_counter++;
	  		}
	  		free(test_pointer);
	  		pointer_counter++;
	  	}

	  	gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;
	}
	int average_nulls = null_counter/100;
	long int average_time = time_total/100;
	printf("Average Null Mallocs for Test B was %ld\n", average_nulls);	
	printf("Average Time for Test B was %ld microseconds\n", average_time);	

}

void testC(){

   int null_counter = 0;   
   int workload_counter = 0;
   long int time_total = 0;

   char* malloc_pointers[3000];
   int malloc_counter = 0;
   int free_counter = 0;
   int total_counter = 0;

   time_t t;
  
   /* Intializes random number generator */
   srand((unsigned) time(&t));


   while(workload_counter < 100) {	
   		block_init();
   		malloc_counter = 0;
   		free_counter = 0;
   		total_counter = 0;

   		struct timeval start, end;
		gettimeofday(&start, NULL);

	 	while(total_counter < 6000) {

	   		int random_number = rand() % 2;


	   		if (random_number == 1 && free_counter < 3000) {

	   			if (free_counter < malloc_counter) {

	   				free(malloc_pointers[free_counter]);
					free_counter++;
					total_counter++;
				}
				else {
					random_number = 0;
				}
	   		}

	   		if(random_number == 0 && malloc_counter < 3000) {

	   			malloc_pointers[malloc_counter] = malloc(1);
	   			if(malloc_pointers[malloc_counter] == NULL) {
	  				null_counter++;
	  			}
	   			malloc_counter++;
	   			total_counter++;
	   		}
	    }
		gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;

   }
    int average_nulls = null_counter/100;
	long int average_time = time_total/100;
	printf("Average Null Mallocs for Test C was %ld\n", average_nulls);	
	printf("Average Time for Test C was %ld microseconds\n", average_time);	
    
}
void testD(){
   
   int null_counter = 0;   
   int workload_counter = 0;
   long int time_total = 0;

   void* malloc_pointers[3000];
   int malloc_counter = 0;
   int free_counter = 0;
   int total_counter = 0;

   time_t t;
  
   /* Intializes random number generator */
   srand((unsigned) time(&t));


   while(workload_counter < 100) {	
   		block_init();
   		malloc_counter = 0;
   		free_counter = 0;
   		total_counter = 0;

   		struct timeval start, end;
		gettimeofday(&start, NULL);

	 	while(total_counter < 6000) {
	 		//printf("total counter is %d\n", total_counter);
	   		int random_number = rand() % 2; //free is 1 malloc is 0
	   		//printf("random number is %d\n", random_number);

	   		if (random_number == 1 && free_counter < 3000) {

	   			if (free_counter < malloc_counter) {

	   				//printf("freeing address is %p\n", malloc_pointers[free_counter]);
	   				free(malloc_pointers[free_counter]);
					free_counter++;
					total_counter++;
				}
				else {
					random_number = 0;
				}
	   		}

	   		if(random_number == 0 && malloc_counter < 3000) {

		   		int random_size = rand() % 100;
		   		//printf("random size is %d\n", random_size);
	   			malloc_pointers[malloc_counter] = malloc(random_size);
	   			if(malloc_pointers[malloc_counter] == NULL) {
	  				null_counter++;
	  			}
	   			//printf("mallocced address is %p\n\n", malloc_pointers[malloc_counter]);
		   		malloc_counter++;
		   		total_counter++;
	   		}
	    }
		gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;

   }
    int average_nulls = null_counter/100;
	long int average_time = time_total/100;

	printf("Average Null Mallocs for Test D was %ld\n", average_nulls);	
	printf("Average Time for Test D was %ld microseconds\n", average_time);	

}

void testEF(){

}


int main( int number_of_args, char* arg_list[] ) {
	block_init();
	testA();
	testB();
	testC();
    testD();
    return 0;
}