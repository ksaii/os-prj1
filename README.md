# UTSA CS 3733 - Operating Systems

## Project 1: Shell Implementation

### GROUP MEMBERS

- Javier Rios
- Abram Ortiz

### FILES INCLUDED

- `shell.c`: Main source code for the shell program.
- `Makefile`: Build automation file for compiling the program.
- `README.txt`: This documentation file.

### COMPILATION INSTRUCTIONS

To compile the program:

```bash
make
```

To clean compiled files:

```bash
make clean
```

### EXECUTION INSTRUCTIONS

To run the shell:

```bash
./shell
```

The shell supports the following built-in commands:

- `exit`: Terminates the shell.
- `cd [directory]`: Changes the current working directory to the specified path.
- `showpid`: Displays the process IDs (PIDs) of the last 5 child processes.

Any other input is treated as an external command (e.g., `ls`, `pwd`, `echo`) and executed using the system's `execvp`.

**Example Usage**:

```bash
prompt$ ls -l
prompt$ cd /tmp
prompt$ pwd
prompt$ showpid
prompt$ exit
```

### CHALLENGES ENCOUNTERED

- **Testing External Commands**: Ensuring all external commands (e.g., `ls`, `cat`, `grep`) executed correctly via `fork` and `execvp` was challenging, as some commands behaved unexpectedly due to argument parsing issues.
- **PID Logic Implementation**: Managing the PID history array to store only the last 5 child processes required careful handling of array indexing and modulo operations to avoid overwriting or accessing invalid data.
- **Tokenizing Logic**: Parsing user input into tokens using `strtok` was difficult, particularly handling edge cases like empty inputs, multiple spaces, or long command lines, which required robust error checking.

### SOURCES/REFERENCES USED

- **Lecture Slides**: Provided core concepts on process creation (`fork`, `execvp`) and system calls.
- **Operating System Concepts (ZyBook)**: Referenced for understanding shell design, process management, and POSIX system calls.
- **Official Linux Command Documentation**: Used `man` pages for `fork`, `execvp`, `waitpid`, `chdir`, and `getcwd` to ensure correct usage and error handling.
- No Stack Overflow or external websites were used.

### NOTES

- The shell is designed to be simple yet functional, meeting the project requirements for built-in commands and external program execution.
- We tested the shell on a Linux environment (e.g., Ubuntu) to ensure compatibility with POSIX systems.
- Any feedback on improving the tokenization or PID history features would be appreciated.
