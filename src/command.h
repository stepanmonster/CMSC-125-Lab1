#ifndef MYSH_H
#define MYSH_H

#include <stdbool.h>

// This is the "Command Structure" mentioned in your design notes 
typedef struct {
    char *command;        // Command name (e.g., "ls")
    char *args[256];      // Arguments (NULL-terminated)
    char *input_file;     // For < redirection
    char *output_file;    // For > or >> redirection
    bool append;          // true for >>, false for >
    bool background;      // true if & present
} Command;

// Function prototypes - tells the compiler these functions exist elsewhere
void parseInput(char *args[], Command *cmd, int i, bool append, bool background, char *outputfile, char *inputfile);
void execute_command(Command cmd);
/* Command buildCommand(char* args[], Command *cmd, int i); */

#endif