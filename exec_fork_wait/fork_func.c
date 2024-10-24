/*
    <unistd.h> : fork()
    <sys/types.h> : pid_t

    pid_t fork(void);

    fork returns pid means this process is parent process and the returned pid is that of the child process
    fork returns zero means this process is child process
    fork returns -1 means some error during forking

    if parent finishes before child, init becomes child's parent 
    if child finishes before parent and parent has not collected its return status, child becomes a zombie/defunct process
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int n;
    char *msg;

    printf("This is parent. forking now. \n");

    pid = fork();

    switch(pid)
    {
        case -1:
        printf("error while forking\n");
        exit(-1);

        case 0:
        msg = "\t\t\t\tchild";
        n = 1;
        break;

        default:
        msg = "parent";
        n = 5;
    }
    while(n--)
    {
        printf("%s(%d)[%d]\n",msg,getpid(), getppid());
        sleep(1);
    }
    exit(0);
}