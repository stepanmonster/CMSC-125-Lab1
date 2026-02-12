// main file for running UNIX shell
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
// #include <parser.c> or makefile
void testPrint(char *args[], int i);

int main()
{
    size_t len = 0;
    char *input = NULL;
    while (true)
    {
        printf("mysh> ");
        if (getline(&input, &len, stdin) == -1)
        {
            printf("\nExiting...\n");
            break;
        }
        Command cmd = parseInput(input);

        // put execution calls here (before free input)
        execute_command(cmd);

        // free memory allocated for input
        free(input);
        input = NULL;
    }
}