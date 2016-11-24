#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main( int number_of_args, char* arg_list[] ) {


    if(number_of_args != 3) {
        printf("INPUT FORMAT: ./compressR_LOLS.c <file to compress> <number of parts>\n");
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
            printf("ERROR: NUMBER OF PARTS MUST BE AN INTEGER > 0\n");
            exit(1);
        } 
    }
    int number_of_parts = atoi(arg_list[2]);

    if(number_of_parts < 1) {
        printf("ERROR: NUMBER OF PARTS MUST BE > 0\n");
        exit(1);

    }

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

    char ** child_arg_list = (char**)malloc(6*sizeof(char*));
    
    child_arg_list[0] = (char*)(malloc(50)); //executable from parent
    child_arg_list[1] = (char*)(malloc(50)); //name of file to be compressed 
    child_arg_list[2] = (char*)(malloc(25)); //start_index
    child_arg_list[3] = (char*)(malloc(25)); //end_index
    child_arg_list[4] = (char*)(malloc(25)); //output file number

    strcpy(child_arg_list[0],arg_list[0]);
    strcpy(child_arg_list[1],arg_list[1]);

    int counter = 0;
    int start_index = 0;
    int end_index = 0;
    


    pid_t child_pids[number_of_parts];
    pid_t pid;

    //splits into multiple processes 
    while(counter < number_of_parts) {
        //initializes the intial start and end indices 
        if(counter == 0) {
            start_index = 0;
            end_index = start_index + characters_per_child + extra_characters - 1;
        } else {
            start_index = end_index + 1;
            end_index = start_index + characters_per_child - 1;
        }

        snprintf(child_arg_list[2], 25, "%d", start_index);
        snprintf(child_arg_list[3], 25, "%d", end_index);
        if(number_of_parts == 1) {
            char* empty = "";
            strcpy(child_arg_list[4],empty);
        } else {
            snprintf(child_arg_list[4], 25 , "%d", counter);
        }

        pid = fork();

        if (pid == -1) {
            printf("ERROR: FORK FAILED\n");
            exit(1);
        }
        else if (pid == 0) {
            /* in child */
            execvp("./compressR_worker_LOLS", child_arg_list);
            printf("ERROR: EXEC FAILED\n");
            exit(1);
        }
        else {
            /* in parent */
            child_pids[counter] = pid;
        }
        counter++;
    }

    counter = 0;
    while(counter < number_of_parts) {
       waitpid(child_pids[counter], NULL, 0);
       if(errno == ECHILD) {
        break;
       }
       counter++;
    }
    

    free(child_arg_list[0]);
    free(child_arg_list[1]);
    free(child_arg_list[2]);
    free(child_arg_list[3]);
    free(child_arg_list[4]);
    free(child_arg_list);

    return 0;
}