# CMSC 125-1 Laboratory Activity 1: UNIX Shell (mysh)

**Authors:** Dale Louize Almonia & Stefan Niedes

# mysh - A Minimalist UNIX Shell

`mysh` is a robust, lightweight UNIX shell implemented in C. It provides a command-line interface for executing system programs, managing background tasks, and handling I/O redirection.

## 🚀 Compilation and Usage

### Prerequisites
* A C compiler (gcc)
* A POSIX-compliant environment (Linux or WSL)

### Building the Shell
Since a `Makefile` is provided, simply run:
```bash
make all
```

### Running the shell
```bash
./mysh
```

## ✨ Implemented Features

| Feature           | Description                                                           |
| ----------------- | --------------------------------------------------------------------- |
| Command Execution | Launches system programs via fork() and execvp().                     |
| Built-in Commands | Internal support for cd, pwd, and exit for better performance.        |
| I/O Redirection   | Supports < (input), > (overwrite), and >> (append).                   |
| Background Jobs   | Appending & runs tasks in the background without blocking the prompt. |
| Zombie Reaping    | Uses WNOHANG to clean up finished background processes automatically. |
| Operator Handling | Custom pre-processor handles tokens without spaces (e.g., ls>file).   |

## 🏗️ Architecture & Design Decisions

### 1. Modular Organization
The project is divided into four distinct layers:

| Module | Responsibility |
|--------|----------------|
| **mysh.c** | Main REPL (Read-Eval-Print Loop). Manages the prompt and ensures background jobs are reaped before every new input cycle. |
| **command.h** | Defines the `Command` data structure, which stores the command name, arguments, redirection files, and execution flags. |
| **parser.c** | Tokenizes input strings into the `Command` struct. |
| **executor.c** | Handles the logic for `fork()`, process execution, and file descriptor redirection using `dup2()`. |

### 2. Space-Agnostic Parsing
**Core Design Choice**: Implementation of `add_spaces_to_operators`.

- **Problem**: Many basic shells fail if users type `ls>output` (no spaces around operators).
- **Solution**: Pre-processes input strings to inject spaces around operators (`<`, `>`, `>>`, `&`).
- **Benefit**: Tokenizer always reads operators correctly, improving user experience.

**Example**:

```bash
Input: ls>output.txt
Pre-processed: ls > output.txt
```

→ Correctly parsed as command + redirection


### 3. Background Process Management
**Zombie Prevention Strategy**:

- **Problem**: Background processes (`cmd &`) create zombie processes if ignored.
- **Solution**: At the start of **every loop iteration**, check for completed children using `waitpid()` with `WNOHANG`.
- **Benefits**:
  - Keeps process table clean
  - No complex signal-handling required
  - Automatic cleanup without user intervention

**Process Flow**:
```
REPL Loop:

Reap finished background jobs (WNOHANG)

Print prompt

Read user input

Parse & execute
→ Repeat
```

## ⚠️ Known Limitations & Bugs

| Limitation | Description |
|------------|-------------|
| **No Piping** | Pipe operator (`\|`) not implemented |
| **No Quotes** | Doesn't handle spaces inside quotes (e.g., `mkdir "My Folder"` → 2 args) |
| **No Variables** | Cannot expand `$PATH`, `$HOME`, or environment variables |
| **Arg Limit** | Fixed at 256 arguments (`MAX_ARGS`) |
| **No Signals** | No `Ctrl+C`, `Ctrl+Z` job control |
| **Simple Paths** | Basic path handling only (no `~` expansion) |
