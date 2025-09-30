#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LINE 1024
#define MAX_TOKENS 10
#define MAX_HISTORY 5

// store last 5 child PIDs
pid_t pid_history[MAX_HISTORY];
int pid_count = 0;

void add_pid(pid_t pid) {
    pid_history[pid_count % MAX_HISTORY] = pid;
    pid_count++;
}

void show_pid_history() {
    int start = (pid_count >= MAX_HISTORY) ? pid_count - MAX_HISTORY : 0;
    
    int i;
    for (i = start; i < pid_count; i++) {
        printf("%d\n", pid_history[i % MAX_HISTORY]);
    }
}

void print_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        
        // orange color
        printf("\033[38;5;208m%s$\033[0m ", cwd);
    } else {
        printf("prompt$ ");
    }
    fflush(stdout);
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_TOKENS + 1];

    while (1) {
        print_prompt();

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break; // exit on Ctrl+D
        }

        // remove newline
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;

        // tokenize input
        memset(args, 0, sizeof(args));
        char *token = strtok(line, " ");
        int i = 0;
        while (token != NULL && i < MAX_TOKENS) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        // built in
        if (strcmp(args[0], "exit") == 0) {
            printf("exit\n");
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                } else {
                    setenv("PWD", args[1], 1);
                }
            }
            continue;
        } else if (strcmp(args[0], "showpid") == 0) {
            show_pid_history();
            continue;
        }

        // external
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                fprintf(stderr, "Error: Command could not be executed\n");
            }
            exit(EXIT_FAILURE);
        } else {
            add_pid(pid);
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
