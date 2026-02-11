// main file for running UNIX shell
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
// #include <parser.c> or makefile

// char *builtins[] = {"exit", "cd", "pwd"};

// void exitShell(void);
void testPrint(char *args[], int i);

// ignore (in progress)
/* int checkIfBuiltIn(char *input){
    for(int i = 0; i < sizeof(builtins[0]); i++){
        if(strcmp(input, builtins[0])){
            return 0;
        } else if (strcmp(input, builtins[1])){
            return 1;
        } else if (strcmp(input, builtins[2])){
            return 2;
        }
    }
} */

// void testPrint(char *args[], int i){
//     for(int j = 0; j < i; j++){
//             printf("%s \n", args[j]);
//     }
// }

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
        getline(&input, &len, stdin);

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