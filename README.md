# Shell Implementation - Project 1

## Group Members

[Add your name(s) here]

## Files Included

### shell.c

Main implementation file containing:

- Main shell loop that displays prompt and processes commands
- Command parsing using `strtok()`
- External command execution using `fork()`, `execvp()`, and `waitpid()`
- Built-in commands: `exit`, `cd`, `showpid`
- Enhanced prompt with current directory and color

### Makefile

Automates the compilation process:

- Compiles shell.c with appropriate flags
- Creates executable named `shell`
- Includes `clean` target to remove build artifacts
- Includes `run` target to execute the shell

### README.md

This file - contains project documentation

## Compilation Instructions

To compile the shell program:

```bash
make
```

This will create an executable named `shell`.

To clean build artifacts:

```bash
make clean
```

## Execution Instructions

To run the shell:

```bash
./shell
```

Or use the Makefile:

```bash
make run
```

## Features Implemented

### Part 1: Basic Prompt (5 points)

- Displays `prompt$ ` with space after dollar sign
- Shell waits for user input

### Part 2: Command Line Parsing (10 points)

- Parses input into tokens using `strtok()`
- Supports up to 10 tokens per command
- Maximum token length: 80 characters
- Handles single-space delimiters

### Part 3: Command Execution (30 points)

- **fork()**: Creates child process for command execution
- **execvp()**: Executes external programs
- **waitpid()**: Parent waits for child completion, prevents zombie processes
- Error handling for invalid commands

### Part 4: Built-in Commands (15 points)

- **exit**: Prints "exit" and terminates shell cleanly
- **cd [PATH]**: Changes directory using `chdir()` and updates PWD environment variable
- **showpid**: Displays last 5 child process IDs

### Part 5: Enhanced Prompt (10 points)

- Displays current working directory using `getcwd()`
- Cyan color for prompt using ANSI escape codes
- Format: `/current/directory$ `

## Usage Examples

```bash
# Basic commands
/home/user$ ls
file1.txt  file2.txt  shell.c

# Change directory
/home/user$ cd /tmp
/tmp$ pwd
/tmp

# Show process IDs
/tmp$ ls
/tmp$ echo hello
hello
/tmp$ showpid
12345
12346

# Exit shell
/tmp$ exit
exit
```

## Challenges Encountered

1. **Memory Management**: Ensuring proper cleanup of buffers between commands using `memset()`
2. **PID History**: Implementing circular buffer logic to maintain only the last 5 PIDs
3. **Error Handling**: Gracefully handling invalid commands without crashing
4. **Built-in vs External Commands**: Distinguishing between commands that need fork/exec and those that don't

## Implementation Notes

- The shell does not crash under any circumstances
- All system calls include proper error checking
- No use of the forbidden `system()` call
- Follows all parsing assumptions (no leading/trailing whitespace, single spaces)

## Testing Performed

- Basic external commands: `ls`, `pwd`, `echo`, `date`
- Built-in commands: `exit`, `cd`, `showpid`
- Error cases: invalid commands, non-existent directories
- Zombie process prevention verified
- Maximum token handling (10 tokens)
- Edge cases: empty input, EOF handling

## Sources and References

- Linux man pages: `fork(2)`, `execvp(3)`, `waitpid(2)`, `chdir(2)`, `getcwd(3)`
- C standard library documentation: `strtok()`, `fgets()`, `memset()`
- ANSI color codes: https://en.wikipedia.org/wiki/ANSI_escape_code
- Course lecture notes and textbook

## Compilation Requirements

- Compiler: gcc
- Standard: C99
- Operating System: Linux/Unix

### Building on Windows

This project uses POSIX APIs (fork, execvp, waitpid, getcwd, chdir) and includes headers
like `<sys/wait.h>` which are not available in native Windows toolchains. If you tried
to run `make` on PowerShell or Command Prompt you may see an error like:

```
fatal error: sys/wait.h: No such file or directory
```

Options to build and run the shell on Windows:

1. WSL (recommended)

   - Install WSL and a Linux distribution (Ubuntu) from Microsoft Store.
   - Open the WSL terminal in the project folder and run:

```powershell
# from Windows PowerShell, open WSL in the current folder
wsl -d Ubuntu -- cd "$(pwd -W)"; make
```

    - Or inside WSL (bash):

```bash
make
./shell
```

2. MSYS2 / MinGW (alternative)

   - Install MSYS2 (https://www.msys2.org/), open the MSYS2 MinGW64 shell.
   - Install packages: `pacman -Syu mingw-w64-x86_64-gcc make`
   - From the MSYS2 shell, run:

```bash
make
./shell.exe
```

3. Use a Linux VM or build inside a container.

If you prefer to keep compiling on Windows without WSL/MSYS2, you'd need to port the
program to use Windows-specific process APIs (CreateProcess, WaitForSingleObject, etc.),
which is beyond the scope of this assignment.

---

**Due Date**: September 30, 2025 at 11:59 PM

Go 'Runners! 🏃
