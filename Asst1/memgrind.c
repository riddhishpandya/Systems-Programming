 /*
 * memgrind.c
 */
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"
#include <string.h>
#include <time.h>

/* malloc() 1 byte 3000 times, then free() the 3000 1 byte pointers one by one */
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
	  		if(malloc_pointers[pointer_counter] == NULL) {
	  			null_counter++;
	  		}
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
	int average_nulls = null_counter/100;
	long int average_time = time_total/100;
	printf("Average Null Mallocs for Test A was %d\n", average_nulls);	
	printf("Average Time for Test A was %ld microseconds\n", average_time);	
}

/* malloc() 1 byte and immediately free it 3000 times in a row */
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
	printf("Average Null Mallocs for Test B was %d\n", average_nulls);	
	printf("Average Time for Test B was %ld microseconds\n", average_time);	

}

/* Randomly choose between a 1 byte malloc() or free() 6000 times
 - Keep track of each operation so that you eventually malloc() 3000 bytes, in total
 - Keep track of each operation so that you eventually free() all pointers */ 
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
	printf("Average Null Mallocs for Test C was %d\n", average_nulls);	
	printf("Average Time for Test C was %ld microseconds\n", average_time);	
    
}

/* Randomly choose between a randomly-sized malloc() or free 6000 times
 - Keep track of each malloc so that your mallocs do not exceed your memory capacity
 - Keep track of each operation so that you eventually malloc() 3000 times
 - Keep track of each operation so that you eventually free() all pointers */
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
	   		int random_number = rand() % 2; //free is 1 malloc is 0

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

		   		int random_size = rand() % 5000;
	   			malloc_pointers[malloc_counter] = malloc(random_size);
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

	printf("Average Null Mallocs for Test D was %d\n", average_nulls);	
	printf("Average Time for Test D was %ld microseconds\n", average_time);	

}

/*Test case E randomly chooses between a malloc or a free 6000 times and for each malloc, stores a string in each character pointer.
 This shows that the implementation of malloc can in fact store data and that free frees up space for more data. */
void testE(){

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
	   		char* hello = "hello";

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

	   			malloc_pointers[malloc_counter] = malloc(strlen(hello) + 1);
	   			if(malloc_pointers[malloc_counter] == NULL) {
	  				null_counter++;
	  			} else {
	  				strcpy(malloc_pointers[malloc_counter], hello);
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
	printf("Average Null Mallocs for Test E was %d\n", average_nulls);	
	printf("Average Time for Test E was %ld microseconds\n", average_time);	
    

}

/* Test case F allocates randomly sized pointers 3000 times, and then frees every other pointer so that there is significant 
fragmentation within the memory block in mymalloc.c. The function then attempts to allocated 3000 more randomly sized pointers,
testing malloc's ability to find blocks that fit the requested allocation.  
Note that this would result in many null pointers since the first 3000 mallocs would fill up the memory block and the
spread out pointers will result in minimal coalescing. Therefore the second round of mallocs may not fit in many blocks. */
void testF() {

	int null_counter = 0;
	char* malloc_pointers[3000];
	int pointer_counter = 0;
	int workload_counter = 0;
	long int time_total = 0;

	time_t t;
  
   /* Intializes random number generator */
   srand((unsigned) time(&t));

	while(workload_counter < 100) {
		block_init();
		pointer_counter = 0;

		struct timeval start, end;
		gettimeofday(&start, NULL);

		int random_size;

  		while(pointer_counter < 3000) {
			random_size = rand() % 150;
	  		malloc_pointers[pointer_counter] = malloc(random_size);
	  		if(malloc_pointers[pointer_counter] == NULL) {
	  			null_counter++;
	  		}
	  		pointer_counter++;

	  	}
	  	
	  	pointer_counter = 0;
	  	while(pointer_counter < 3000) {
			
	  		free(malloc_pointers[pointer_counter]);
	  		pointer_counter+= 2;

	  	}

		while(pointer_counter < 3000) {
			random_size = rand() % 150;
			malloc_pointers[pointer_counter] = malloc(random_size);
			if(malloc_pointers[pointer_counter] == NULL) {
				null_counter++;
			}
			pointer_counter++;
		}
	  	gettimeofday(&end, NULL);
	  	time_total = time_total + ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
		workload_counter++;
	}
	int average_nulls = null_counter/100;
	long int average_time = time_total/100;
	printf("Average Null Mallocs for Test F was %d\n", average_nulls);	
	printf("Average Time for Test F was %ld microseconds\n", average_time);	

}


int main( int number_of_args, char* arg_list[] ) {
	block_init();
	testA();
	testB();
	testC();
    testD();
    return 0;
}