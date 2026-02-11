// main file for running UNIX shell
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
// #include <parser.c> or makefile
void testPrint(char *args[], int i);

int main(){
    // note: build switch case for built ins

    // main loop for taking string input and storing in command struct
    size_t len = 0;
    char *input = NULL;
    while(true){
        Command cmd;
        memset(&cmd, 0, sizeof(Command)); // initialize command struct to zero
        
        // initialized struct members
        char *args[64];
        char *output_file = NULL;
        char *input_file = NULL;
        bool append = false;
        bool background = false;

        printf("mysh> ");
        if (getline(&input, &len, stdin) == -1) {
            printf("\nExiting...\n");
            break;
        }

        char* token = strtok(input, " \n");
        if(token == NULL){ continue; };
        int i = 0;
        while(token != NULL){
            if(strcmp(token, ">") == 0){
                output_file = strtok(NULL, " \n");
                if(output_file == NULL){
                    printf("Error: No specified output file\n");
                }
            } else if (strcmp(token, ">>") == 0){
                output_file = strtok(NULL, " \n");
                append = true;
                if(output_file == NULL){
                    printf("Error: No specified output file\n");
                }
            } else if (strcmp(token, "<") == 0){
                input_file = strtok(NULL, " \n");
                if(input_file == NULL){
                    printf("Error: No specified input file\n");
                }
            } else if (strcmp(token, "&") == 0){
                background = true;
            } else {
                args[i] = token;
                i++;
            }
        token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        parseInput(args, &cmd, i, append, background, input_file, output_file);

        // put execution calls here (before free input)
        execute_command(cmd);

        // free memory allocated for input
        free(input);
        input = NULL;
    }
}