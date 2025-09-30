#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_TOKEN_LEN 80
#define MAX_TOKENS 10
#define MAX_PID_HISTORY 5
#define COLOR_CYAN "\033[1;36m"
#define COLOR_RESET "\033[0m"

// Global array to store last 5 child PIDs
pid_t pid_history[MAX_PID_HISTORY];
int pid_count = 0;

// Function to add PID to history
void add_pid(pid_t pid)
{
    if (pid_count < MAX_PID_HISTORY)
    {
        pid_history[pid_count++] = pid;
    }
    else
    {
        // Shift array left and add new PID at end
        for (int i = 0; i < MAX_PID_HISTORY - 1; i++)
        {
            pid_history[i] = pid_history[i + 1];
        }
        pid_history[MAX_PID_HISTORY - 1] = pid;
    }
}

// Function to display enhanced prompt with color and current directory
void display_prompt()
{
    char cwd[MAX_INPUT];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s%s$ %s", COLOR_CYAN, cwd, COLOR_RESET);
    }
    else
    {
        printf("%sprompt$ %s", COLOR_CYAN, COLOR_RESET);
    }
    fflush(stdout);
}

// Function to parse input into tokens
int parse_input(char *input, char *tokens[])
{
    int token_count = 0;

    // Remove newline if present
    input[strcspn(input, "\n")] = 0;

    // Tokenize input
    char *token = strtok(input, " ");
    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, " ");
    }
    tokens[token_count] = NULL; // NULL-terminate for execvp

    return token_count;
}

// Built-in: exit command
void builtin_exit()
{
    printf("exit\n");
    exit(0);
}

// Built-in: cd command
void builtin_cd(char *tokens[])
{
    if (tokens[1] == NULL)
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    if (chdir(tokens[1]) != 0)
    {
        perror("cd");
    }
    else
    {
        // Update PWD environment variable
        char cwd[MAX_INPUT];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            setenv("PWD", cwd, 1);
        }
    }
}

// Built-in: showpid command
void builtin_showpid()
{
    for (int i = 0; i < pid_count; i++)
    {
        printf("%d\n", pid_history[i]);
    }
}

// Function to execute external commands
void execute_command(char *tokens[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        // Child process
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("Error: Command could not be executed\n");
            exit(1);
        }
    }
    else
    {
        // Parent process
        add_pid(pid);
        int status;
        waitpid(pid, &status, 0);
    }
}

// Main shell loop
int main()
{
    char input[MAX_INPUT];
    char *tokens[MAX_TOKENS + 1]; // +1 for NULL terminator

    while (1)
    {
        // Clear buffers
        memset(input, 0, sizeof(input));
        memset(tokens, 0, sizeof(tokens));

        // Display prompt
        display_prompt();

        // Get user input
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break; // EOF or error
        }

        // Parse input
        int token_count = parse_input(input, tokens);

        // Skip if no input
        if (token_count == 0)
        {
            continue;
        }

        // Check for built-in commands
        if (strcmp(tokens[0], "exit") == 0)
        {
            builtin_exit();
        }
        else if (strcmp(tokens[0], "cd") == 0)
        {
            builtin_cd(tokens);
        }
        else if (strcmp(tokens[0], "showpid") == 0)
        {
            builtin_showpid();
        }
        else
        {
            // Execute external command
            execute_command(tokens);
        }
    }

    return 0;
}