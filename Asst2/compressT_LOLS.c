#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


char* file_to_compress_name;

/* this struct will hold each individual thread's data */
struct thread_data {

    int start_index;
    int end_index;
    char* output_file_number;

};

/* thread function, where all the work is done */
void* thread_worker(void* thread_args) {

    /* creates struct pointer to retrieve data necessary to compress the 
    part of file for a specific thread */
    struct thread_data* my_data = (struct thread_data*)thread_args;
    int start = my_data->start_index;
    int end = my_data->end_index;

    FILE* file_to_compress = fopen(file_to_compress_name, "r");

    //goes to the specific start index in the input file for this thread
    fseek(file_to_compress, start, SEEK_CUR); 

    char * output_string = (char*)malloc(sizeof(char)*(end-start));
    char * current_buffer = (char*)malloc(sizeof(char)*(end-start));

    char prev_letter; 
    char current_letter;
    int compressor_counter = 0;

    char * output_file_name = (char*)(malloc(sizeof(char)*25)); //output file name
    strcpy(output_file_name,file_to_compress_name); 

    //gets rid of any file extension that file to compress may have and adds number
    int len = strlen(output_file_name);
    int i;
    for(i = 0; i < len; i++) {
        if(output_file_name[i] == '.') {
          output_file_name[i] = '_';
          break;
        }
    }
    //creates output file name
    sprintf(output_file_name,"%s_LOLS%s", output_file_name, my_data->output_file_number);
    
    //checks if current file already exists -> and outputs a warning
    int result = access(output_file_name, F_OK);
    if(result == 0) {
        printf("WARNING: %s exists...overwriting file\n",output_file_name);
    }

    //the compression takes place here
    while(start <= end) {

        fscanf(file_to_compress, "%c", &current_letter); 

        if(isalpha(current_letter) != 0) {

          if(start == 0 || current_letter == prev_letter) {
            current_buffer = strncat(current_buffer, &current_letter, 1);
            compressor_counter++;
            }
          else if(current_letter != prev_letter) {
            if(compressor_counter <= 2) {
            strncat(output_string, current_buffer, compressor_counter);
            }
            else {
              memset(current_buffer,0,strlen(current_buffer));
              sprintf(current_buffer, "%d%c", compressor_counter, prev_letter);
              strcat(output_string, current_buffer);
            }
            memset(current_buffer,0,strlen(current_buffer));
            current_buffer = strncat(current_buffer, &current_letter, 1);
            compressor_counter = 1;
          }
        prev_letter = current_letter; 

        }
        if (start == end) {
          if(compressor_counter <= 2) {
              strncat(output_string, current_buffer, compressor_counter);
            }
          else {
            memset(current_buffer,0,strlen(current_buffer));
            sprintf(current_buffer, "%d%c", compressor_counter, prev_letter);
            strcat(output_string, current_buffer);
          }
          break;
        }
        else {
          start++;
        }
    }
    FILE* output_file = fopen(output_file_name, "w");
    fprintf(output_file, "%s", output_string);
    fclose(file_to_compress);
    fclose(output_file);
    free(output_string);
    free(current_buffer);
    free(output_file_name);
    pthread_exit(NULL);
    

}

int main(int number_of_args, char* arg_list[] ) {
 

    if(number_of_args != 3) {
        printf("INPUT FORMAT: ./compressT_LOLS.c <file to compress> <number of parts>\n");
        exit(1);
    }

    FILE* file_to_compress = fopen(arg_list[1], "r");

    if(file_to_compress == NULL) {
        printf("ERROR: INVALID FILE TO COMPRESS\n");
        exit(1);
    }
    
    char* number_of_parts_str = arg_list[2];
    while (*number_of_parts_str) {
        if (isdigit(*number_of_parts_str++) == 0) {
            printf("ERROR: NUMBER OF PARTS MUST BE AN INTEGER\n");
            exit(1);
        } 
    }
    int number_of_parts = atoi(arg_list[2]);

    if(number_of_parts < 1) {
        printf("ERROR: NUMBER OF PARTS MUST BE > 0\n");
        exit(1);

    }
    file_to_compress_name = (char*)malloc(strlen(arg_list[1]));
    strcpy(file_to_compress_name,arg_list[1]);
    fseek(file_to_compress, 0, SEEK_END);
    int characters_in_file = ftell(file_to_compress) - 1; //POSIX standard is that file will end with '\n' so subtracting 1 accounts for that
    fclose(file_to_compress); 

    if(characters_in_file <= 0) {
        printf("ERROR: INPUT FILE IS EMPTY\n");
        exit(1);
    }

    if(number_of_parts > characters_in_file) {
        printf("ERROR: NUMBER OF PARTS EXCEEDS CHARACTERS IN FILE\n");
        exit(1);
    }

    int characters_per_child = characters_in_file/number_of_parts;
    int extra_characters = characters_in_file%number_of_parts;


    pthread_t threads[number_of_parts];
    struct thread_data thread_data_array[number_of_parts];


    int rc;
    int counter = 0;
    int start_index = 0;
    int end_index = 0;

    //splits into multiple threads
    while(counter < number_of_parts) {
        //initializes the intial start and end indices 
        if(counter == 0) {
            start_index = 0;
            end_index = start_index + characters_per_child + extra_characters - 1;
            thread_data_array[counter].start_index = start_index;
            thread_data_array[counter].end_index = end_index;
        } else {
            start_index = end_index + 1;
            end_index = start_index + characters_per_child - 1;
            thread_data_array[counter].start_index = start_index;
            thread_data_array[counter].end_index = end_index;
        }
        thread_data_array[counter].output_file_number = (char*)malloc(25);
        if(number_of_parts == 1) {
            thread_data_array[counter].output_file_number = "";
        } else {
            snprintf(thread_data_array[counter].output_file_number,25, "%d", counter);
        }

        rc = pthread_create(&threads[counter], NULL,thread_worker, &thread_data_array[counter]);
        if (rc) {
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
        }
        counter++;
    }

    counter = 0;
    while(counter < number_of_parts) {
       rc = pthread_join(threads[counter], NULL);
       if (rc) {
          printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
          }
        counter++;
    }

    pthread_exit(NULL);
    counter = 0;
    free(file_to_compress_name);
    while(counter < number_of_parts) {
        free(thread_data_array[counter].output_file_number);
        counter++;
    }
    return 0;


}