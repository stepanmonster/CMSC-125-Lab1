// responsible for parsing user commands
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"

// function prototype declarations
bool handle_redirection(char **file_ptr, char *operator)
{
    char *filename = strtok(NULL, " \n");
    if (filename != NULL)
    {
        *file_ptr = filename;
        return true;
    }
    else
    {
        fprintf(stderr, "mysh: syntax error: expected file after '%s'\n", operator);
        return false;
    }
}

Command parseInput(char *input)
{
    Command cmd;
    memset(&cmd, 0, sizeof(Command)); // This sets everything to NULL/false

    int i = 0;
    char *token = strtok(input, " \n");

    while (token != NULL)
    {
        if (strcmp(token, ">") == 0)
        {
            if (!handle_redirection(&cmd.output_file, ">"))
            {
                cmd.command = NULL;
                return cmd;
            }
            cmd.append = false;
        }
        else if (strcmp(token, ">>") == 0)
        {
            if (!handle_redirection(&cmd.output_file, ">>"))
            {
                cmd.command = NULL;
                return cmd;
            }
            cmd.append = true;
        }
        else if (strcmp(token, "<") == 0)
        {
            if (!handle_redirection(&cmd.input_file, "<"))
            {
                cmd.command = NULL;
                return cmd;
            }
        }
        else if (strcmp(token, "&") == 0)
        {
            cmd.background = true;
        }
        else
        {
            if (i < MAX_ARGS - 1)
            {
                cmd.args[i++] = token;
            }
        }
        token = strtok(NULL, " \n");
    }

    if (i > 0)
    {
        cmd.command = cmd.args[0];
        cmd.args[i] = NULL;
    }

    return cmd;
}