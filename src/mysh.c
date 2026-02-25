// main file for running UNIX shell
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command.h"

// to handle edge cases with no spaces
char *add_spaces_to_operators(const char *input)
{
    char *expanded = malloc(strlen(input) * 3 + 1);
    if (!expanded)
        return NULL;

    int j = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Check for redirection or background operators
        if (input[i] == '>' || input[i] == '<' || input[i] == '&')
        {
            expanded[j++] = ' ';
            expanded[j++] = input[i];

            // Handle ">>" append case
            if (input[i] == '>' && input[i + 1] == '>')
            {
                expanded[j++] = input[++i];
            }
            expanded[j++] = ' ';
        }
        else
        {
            expanded[j++] = input[i];
        }
    }
    expanded[j] = '\0';
    return expanded;
}

// reap zombie processes
bool reap_background_jobs()
{
    int status;
    pid_t pid;
    bool reaped = false;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        // Only print the newline once before the first finished job message
        if (!reaped) printf("\n"); 
        printf("[Background Job %d finished]\n", pid);
        reaped = true;
    }
    return reaped;
}

int main()
{
    size_t len = 0;
    char *input = NULL;

    while (true)
    {
        // Check for finished background jobs before every new command line
        reap_background_jobs();

        if (isatty(STDIN_FILENO))
        {
            printf("mysh> ");
        }

        if (getline(&input, &len, stdin) == -1)
        {
            if (isatty(STDIN_FILENO)) printf("\n");
            printf("Exiting...\n");
            break;
        }

        char *cleaned_input = add_spaces_to_operators(input);

        if (cleaned_input)
        {
            Command cmd = parseInput(cleaned_input);
            
            // Handle 'exit' built-in manually if needed, or let executor handle it
            execute_command(cmd);

            free(cleaned_input);
        }

        free(input);
        input = NULL;
    }
    return 0;
}