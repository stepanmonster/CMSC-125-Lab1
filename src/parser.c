// responsible for parsing user commands
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"

// function prototype declarations

Command parseInput(char *input) {
    Command cmd;
    memset(&cmd, 0, sizeof(Command));

    char *output_file = NULL;
    char *input_file = NULL;
    bool append = false;
    bool background = false;
    int i = 0;
    char *args[64] = {0}; // Initialize to NULL

    char *token = strtok(input, " \n");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            output_file = strtok(NULL, " \n");
        } else if (strcmp(token, ">>") == 0) {
            output_file = strtok(NULL, " \n");
            append = true;
        } else if (strcmp(token, "<") == 0) {
            input_file = strtok(NULL, " \n");
        } else if (strcmp(token, "&") == 0) {
            background = true;
        } else {
            if (i < 63) args[i++] = token; // Prevent overflow
        }
        token = strtok(NULL, " \n");
    }

    // Only assign if we actually found arguments
    if (i > 0) {
        cmd.command = args[0];
        for (int j = 0; j < i; j++) {
            cmd.args[j] = args[j];
        }
        cmd.args[i] = NULL;
    }

    cmd.append = append;
    cmd.background = background;
    cmd.input_file = input_file;
    cmd.output_file = output_file;

    return cmd;
}
