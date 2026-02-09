// main file for running UNIX shell
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "command.h"
// #include <parser.c> or makefile

char *builtins[] = {"exit", "cd", "pwd"};

void exitShell(void);

int checkIfBuiltIn(char *input){
    for(int i = 0; i < sizeof(builtins[0]); i++){
        if(strcmp(input, builtins[0])){
            return 0;
        } else if (strcmp(input, builtins[1])){
            return 1;
        } else if (strcmp(input, builtins[2])){
            return 2;
        }
    }
}

int main(){
    // note: build switch case for built ins

    // main loop for taking string input and storing in command struct
    while(true){
        printf("mysh> ");
        char input[64];
        char *args[64];
        fgets(input, sizeof input, stdin);

        char* token = strtok(input, " \n");
        int i = 0;
        while(token != NULL){
            args[i] = token;
            i++;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        // print args for tests
        for(int j = 0; j < i; j++){
            printf("%s \n", args[j]);
        }
    }

}

// note: move the built in logic to executor