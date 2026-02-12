// responsible for parsing user commands
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"

// function prototype declarations

Command parseInput(char *input) {
    Command cmd;
    memset(&cmd, 0, sizeof(Command)); // This sets everything to NULL/false

    int i = 0;
    char *token = strtok(input, " \n");

    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            cmd.output_file = strtok(NULL, " \n");
            cmd.append = false;
        } else if (strcmp(token, ">>") == 0) {
            cmd.output_file = strtok(NULL, " \n");
            cmd.append = true;
        } else if (strcmp(token, "<") == 0) {
            cmd.input_file = strtok(NULL, " \n");
        } else if (strcmp(token, "&") == 0) {
            cmd.background = true;
        } else {
            // Write directly to the struct's array
            if (i < MAX_ARGS - 1) { 
                cmd.args[i++] = token;
            }
        }
        token = strtok(NULL, " \n");
    }

    if (i > 0) {
        cmd.command = cmd.args[0];
        cmd.args[i] = NULL; // Correctly NULL-terminate the list
    }

    return cmd;
}