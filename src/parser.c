// responsible for parsing user commands
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// function prototype declarations
void exitShell(void);


char builtins[3][5] = {"exit", "cd", "pwd"};

char* outputinput(char* command){

    char* output = command;

    return output;
}

// should return string array
void parseInput(char* input){
    input[strcspn(input, "\n")] = '\0';
    char* token = strtok(input, " ");
    if(token == NULL){
        return;
    }

    if(strcmp(token, "exit") == 0){
        exit(0);
    }
}

/* void checkFlags(){
    //
}


*/


// int main(){
    
//     char* output = outputinput("Hello World");
//     printf("%s \n", output);
//     return 0;
    
//     /*
//     while(true){
//         printf("mysh> ");
//         char input[64];
//         fgets(input, sizeof input, stdin);
//         // parse input
//         parseInput(input);
//         // execute input (if applicable) or probably pass from parser to executor
//     }
//     */
// }