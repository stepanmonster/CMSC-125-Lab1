// responsible for executing user commands
#include <stdio.h>    // For printf and perror
#include <stdlib.h>   // For exit
#include <unistd.h>   // For fork, execvp, dup2, close
#include <fcntl.h>    // For open and O_RDONLY, O_WRONLY, etc.
#include <sys/wait.h> // For waitpid
#include "mysh.h"     // Include the header file for Command structure
//
void execute_command(Command *cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {  // Child process
        // Apply redirections if needed
        if (cmd->input_file) {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0) {
                perror("open input file");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        
        if (cmd->output_file) {
            int flags = O_WRONLY | O_CREAT;
            flags |= cmd->append ? O_APPEND : O_TRUNC;
            int fd = open(cmd->output_file, flags, 0644);
            if (fd < 0) {
                perror("open output file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        
        // Execute command
        execvp(cmd->command, cmd->args);
        perror("exec failed");
        exit(127);
    } else {  // Parent process
        if (!cmd->background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                if (exit_code != 0) {
                    printf("Command exited with code %d\n", exit_code);
                }
            }
        } else {
            printf("Started: (PID: %d)\n", pid);
            // Add to background job list
        }
    }
}