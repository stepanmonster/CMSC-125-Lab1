// main file for running UNIX shell
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "mysh.h"
// #include <parser.c> or makefile

int main(){
    while(true){
        printf("mysh> ");
        char input[64];
        fgets(input, sizeof input, stdin);

        Command cmd;
        //Zero out the command structure before parsing
        memset(&cmd, 0, sizeof(Command));
        // parse input
        if (parseInput(input, &cmd) == 0) {
            // execute input (if applicable) or probably pass from parser to executor
            execute_command(&cmd);
        }
        
    }
}