// main file for running UNIX shell
#include <stdio.h>
#include <stdbool.h>
// #include <parser.c> or makefile

int main(){
    while(true){
        printf("mysh> ");
        char input[64];
        fgets(input, sizeof input, stdin);
        // parse input
        // execute input (if applicable) or probably pass from parser to executor
    }
}