# CMSC 125-1 Laboratory Activity 1: UNIX Shell (mysh)

**Authors:** Dale Louize Almonia & Stefan Niedes

## 1. Problem Analysis
A primary challenge in developing a shell is proper modularization and delegation of responsibilities. Stashing the entire processing and execution logic in a single file is poor practice, as it decreases readability and makes debugging significantly harder. 

To ensure a clean "separation of concerns," this project breaks the program into three distinct components to manage shell operations effectively.

## 2. Solution Architecture
The program is divided into three major source files and a build configuration:

* **`mysh.c`**: The entry point of the program responsible for taking user input. It hosts the main input loop and acts as the "glue" that ties the system together by passing input to the parser and then to the executor.
* **`parser.c`**: Responsible for processing raw user input. It tokenizes the input strings into individual strings, builds the command structure, checks for flags, and identifies the command type.
* **`executor.c`**: Handles the majority of the shell logic. This is where the actual execution of commands (POSIX process API) takes place.
* **`Makefile`**: Crucial for compiling and linking the separate files into a single functional executable.



---

## 3. Implementation Roadmap

### Week 1: Foundation & Tokenization
* Create repository structure.
* Research UNIX shell mechanics and Makefile configurations.
* Implement the interactive loop with a prompt using `fgets()` to read input.
* Implement a tokenizer using `strtok()` to split the command line.

### Week 2: Core Logic & Features
* Learn how to implement POSIX process API.
* Implement shell built-in commands: `exit`, `cd`, and `pwd`.
* Implement I/O redirection.
* Implement background execution.

### Week 3: Testing & Refinement
* Distinguish between built-in commands and external commands.
* Test all built-in and external commands.
* Test redirection logic.
* Test file permissions and error handling.
