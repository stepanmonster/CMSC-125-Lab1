// responsible for executing user commands
#include <stdio.h>    // For printf and perror
#include <stdlib.h>   // For exit
#include <string.h>   // For strcmp
#include <unistd.h>   // For fork, execvp, dup2, close
#include <fcntl.h>    // For open and O_RDONLY, O_WRONLY, etc.
#include <sys/wait.h> // For waitpid
#include "command.h"     // Include the header file for Command structure

//
static int job_id = 1;

void execute_command(Command cmd) {
    //Check Built-in commands
    if(strcmp(cmd.command, "cd") == 0){
        if(cmd.args[1] == NULL){
            fprintf(stderr, "cd: missing argument \n");
            return;
        }
        if(chdir(cmd.args[1]) != 0){
            perror("cd failed");
            return;
        }
        return;
    }
    if(strcmp(cmd.command, "pwd") == 0){
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) != NULL){
            printf("%s\n", cwd);
            return;
        } else {
            perror("pwd failed");
            return;
        }
        return;
    }
    if(strcmp(cmd.command, "exit") == 0){
        exit(0);
        return;
    }
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {  // Child process
        // Apply redirections if needed
        if (cmd.input_file) {
            int fd = open(cmd.input_file, O_RDONLY);
            if (fd < 0) {
                perror("open input file");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        
        if (cmd.output_file) {
            int flags = O_WRONLY | O_CREAT;
            flags |= cmd.append ? O_APPEND : O_TRUNC;
            int fd = open(cmd.output_file, flags, 0644);
            if (fd < 0) {
                perror("open output file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        
        // Execute command
        execvp(cmd.command, cmd.args);
        perror("exec failed");
        exit(127);
    } else {  // Parent process
        if (!cmd.background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                if (exit_code != 0) {
                    printf("Command exited with code %d\n", exit_code);
                }
            }
        } else {
            char cmd_str[256] = ""; 
            for (int j = 0; cmd.args[j] != NULL; j++) {
                strcat(cmd_str, cmd.args[j]);
                strcat(cmd_str, " "); // Add space between arguments
            }
            printf("[%d] Started Background Job: %s (PID: %d)\n", job_id, cmd_str, pid);
            job_id++;
            // Add to background job list
        }
    }

}