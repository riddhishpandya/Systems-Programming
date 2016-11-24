#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int main(int number_of_args, char** arg_list ) {
 
 
  FILE* file_to_compress = fopen(arg_list[1], "r");


  int start_index = atoi(arg_list[2]);
  int end_index =  atoi(arg_list[3]);

  //goes to the specific start index in the input file for this thread
  fseek(file_to_compress, start_index, SEEK_CUR); 

  char * output_string = (char*)malloc(sizeof(char)*(end_index-start_index));
  char * current_buffer = (char*)malloc(sizeof(char)*(end_index-start_index));

  char prev_letter; 
  char current_letter;
  int compressor_counter = 0;

  char * output_file_name = (char*)(malloc(sizeof(char)*25)); //output file name
  strcpy(output_file_name,arg_list[1]); 

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
  sprintf(output_file_name,"%s_LOLS%s", output_file_name, arg_list[4]);
 
  //checks if current file already exists -> and outputs a warning
  int result = access(output_file_name, F_OK);
  if(result == 0) {
  	printf("WARNING: %s exists...overwriting file\n",output_file_name);
  }

  //the compression takes place here
  while(start_index <= end_index) {

    fscanf(file_to_compress, "%c", &current_letter); 

    if(isalpha(current_letter) != 0) {

      if(start_index == 0 || current_letter == prev_letter) {
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
    if (start_index == end_index) {
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
      start_index++;
    }
  }
  FILE* output_file = fopen(output_file_name, "w");
	fprintf(output_file, "%s", output_string);
	fclose(file_to_compress);
	fclose(output_file);
  free(output_string);
  free(current_buffer);
  free(output_file_name);
  	
  return 0;
}