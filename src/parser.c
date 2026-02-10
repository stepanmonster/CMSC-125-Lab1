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

void parseInput(char* args[], Command *cmd, int i, bool append, bool background, char *input_file, char *output_file){
    if(args[0] == NULL){
        return;
    }
    cmd->append = append;
    cmd->background = background;
    cmd->input_file = input_file;
    cmd->output_file = output_file;

    for(int j = 0; j < i; j++){
    cmd->command = args[0];
    cmd->args[j] = args[j];
    }
    cmd->args[i] = NULL;
}