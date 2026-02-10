// responsible for parsing user commands
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"

// function prototype declarations


char* outputinput(char* command){

    char* output = command;

    return output;
}

// should return string array
void parseInput(char* input, Command cmd){
    input[strcspn(input, "\n")] = '\0';
    char* token = strtok(input, " ");
    if(token == NULL){
        return;
    }

    // should be in shell
    if(strcmp(token, "exit") == 0){
        exit(0);
    }
}

Command buildCommand(char *args[], Command cmd, int i){
    cmd.command = args[0];
    for(int j = 0; j < i; j++){
    cmd.args[j] = args[j];
    }
    cmd.args[i] = NULL;
    return cmd;
}

/* 
void checkFlags(){
    // check flags and store and pass to executor
}

void backgroundProcess(){
    // implement logic where parser passes to appropriate executor function
}

void ioFunction(){
    // implement logic where parser passes to appropriate executor function
}

*/

// int main(){
//     /*
//     char* output = outputinput("Hello World");
//     printf("%s \n", output);
//     return 0;*/
    
    
//     while(true){
//         printf("mysh> ");
//         char input[64];
//         fgets(input, sizeof input, stdin);
//         // parse input
//         parseInput(input, Command cmd);
//         // execute input (if applicable) or probably pass from parser to executor
//     }
// }