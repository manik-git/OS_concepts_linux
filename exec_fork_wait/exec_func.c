/*
    <unistd.h>

    char **environ;

    int execl  (const char *path, const char *arg0, ..., (char *)0);
    int execlp (const char *file, const char *arg0, ..., (char *)0);
    int execle (const char *path, const char *arg0, ..., (char *)0, char *const envp[]);

    int execv  (const char *path, char *const argv[]);
    int execvp (const char *file, char *const argv[]);
    int execve (const char *path, char *const argv[], char *const envp[]);
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("\nRunning exec_func.c\n");

    char *const argv[] = {"ps", "ax", (char *)0};
    char *const envp[] = {"PATH=/bin:/usr/bin", "TERM=console", (char *)0};

    // printf("running execl\n");
    // execl("/bin/ps", "ps", "ax", (char *)0);

    // printf("running execlp\n");
    // execlp("ps", "ps", "ax", (char *)0);

    // printf("running execle\n");
    // execle("/bin/ps", "ps", "ax", (char *)0, envp);

    // printf("running execv\n");
    // execv("/bin/ps", argv);

    // printf("running execvp\n");
    // execvp("ps", argv);

    // printf("running execve\n");
    // execve("/bin/ps", argv, envp);

    printf("running another c code\n");
    char *const a[] = {"", (char *)0};
    int x = execv("./system_func", a);

    printf("..Done.. %d\n", x);

    exit(0);
}