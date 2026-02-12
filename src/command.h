#ifndef MYSH_H
#define MYSH_H

#include <stdbool.h>

#define MAX_ARGS 256
// This is the "Command Structure" mentioned in your design notes 
typedef struct {
    char *command;        // Command name (e.g., "ls")
    char *args[MAX_ARGS];      // Arguments (NULL-terminated)
    char *input_file;     // For < redirection
    char *output_file;    // For > or >> redirection
    bool append;          // true for >>, false for >
    bool background;      // true if & present
} Command;

Command parseInput(char *input);
void execute_command(Command cmd);

#endif