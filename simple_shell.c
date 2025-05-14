#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h> 
 
#define MAXLINE 1024 
#define MAXARGS 128 
 
int main() { 
    char line[MAXLINE]; 
    char *argv[MAXARGS]; 
    while (1) { 
        printf("osh> "); 
        if (!fgets(line, MAXLINE, stdin)) break; 
        // delete the line break 
        line[strcspn(line, "\n")] = 0; 
        if (strcmp(line, "exit") == 0) break; 
        // resolve the parameter 
        int argc = 0; 
        char *token = strtok(line, " "); 
        while (token && argc < MAXARGS - 1) { 
            argv[argc++] = token; 
            token = strtok(NULL, " "); 
        } 
        argv[argc] = NULL; 
        // fork + exec 
        pid_t pid = fork(); 
        if (pid < 0) { 
            perror("fork error"); 
        } else if (pid == 0) { 
            execvp(argv[0], argv); 
            perror("exec error");  // return when error 
            exit(1); 
        } else { 
            wait(NULL); 
        } 
    } 
    return 0; 
}
