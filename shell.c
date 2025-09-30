#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LINE 1024
#define MAX_NUM_TOKENS 10
#define MAX_PID_HISTORY 5

pid_t pid_history[MAX_PID_HISTORY];
int pid_count;

void add_pid(pid_t pid)
{
    int index;
    index = pid_count % MAX_PID_HISTORY;
    pid_history[index] = pid;
    pid_count = pid_count + 1;
}

void show_pid_history()
{
    int start;
    int i;

    if (pid_count >= MAX_PID_HISTORY)
    {
        start = pid_count - MAX_PID_HISTORY;
    }
    else
    {
        start = 0;
    }

    i = start;
    while (i < pid_count)
    {
        int index;
        index = i % MAX_PID_HISTORY;
        printf("%d\n", pid_history[index]);
        i = i + 1;
    }
}

void print_prompt()
{
    char cwd[1024];
    char *result;

    result = getcwd(cwd, sizeof(cwd));
    if (result != NULL)
    {
        printf("\033[38;5;208m%s$\033[0m ", cwd);
    }
    else
    {
        printf("prompt$ ");
    }
    fflush(stdout);
}

int main()
{
    char line[MAX_LINE];
    char *args[MAX_NUM_TOKENS + 1];
    char *token;
    int i;
    pid_t pid;
    int status;
    int result;

    pid_count = 0;

    while (1)
    {
        print_prompt();

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0)
        {
            continue;
        }

        i = 0;
        while (i <= MAX_NUM_TOKENS)
        {
            args[i] = NULL;
            i = i + 1;
        }

        token = strtok(line, " ");
        i = 0;
        while (token != NULL && i < MAX_NUM_TOKENS)
        {
            args[i] = token;
            i = i + 1;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
        {
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            printf("exit\n");
            break;
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                fprintf(stderr, "cd: missing argument\n");
            }
            else
            {
                result = chdir(args[1]);
                if (result != 0)
                {
                    perror("cd");
                }
                else
                {
                    setenv("PWD", args[1], 1);
                }
            }
            continue;
        }
        else if (strcmp(args[0], "showpid") == 0)
        {
            show_pid_history();
            continue;
        }

        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
        }
        else if (pid == 0)
        {
            result = execvp(args[0], args);
            if (result == -1)
            {
                fprintf(stderr, "Error: Command could not be executed\n");
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            add_pid(pid);
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}