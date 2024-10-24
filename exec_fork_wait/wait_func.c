/*
    <unistd.h> : fork()
    <sys/types.h> : pid_t
    <sys/wait.h> : wait()

    pid_t wait(int *stat_val); 
    - blocking function

    Macros to analyse stat_val:
    
        WIFEXITED(stat_val)     : [if exited] Nonzero if child process is terminated normally
        WEXITSTATUS(status_val) : [exit status] If WIFEXITED is nonzero, this returns child exit code

        WIFSIGNALED(stat_val)   : [if signaled] Nonzero if the child is terminated on an uncought signal
        WTERMSIG(stat_val)      : [terminate signal] If WIFSIGNALED is nonzero, this returns the signal nnumber

        WIFSTOPPED(stat_val)    : [if stopped] Nonzero if child has stopped
        WSTOPSIG(stat_val)      : [stop signal] IF WIFSTOPPED is nonzero, this returns a signal number
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int n;
    char *msg;
    pid_t pid;
    int exit_code;

    pid = fork();

    switch(pid)
    {
        case -1:
        printf("error while forking\n");
        exit(-1);

        case 0:
        msg = "\t\t\t\tchild";
        n = 1;
        exit_code = 37;
        break;

        default:
        msg = "parent";
        n = 5;
        exit_code = 0;
    }
    while(n--)
    {
        printf("%s(%d)[%d]\n",msg,getpid(), getppid());
        sleep(1);
    }

    if(pid)
    {
        int stat_val;
        pid_t child_pid = wait(&stat_val);

        if(WIFEXITED(stat_val))
        {    printf("child(%d) has finished with code: %d\n", child_pid, WEXITSTATUS(stat_val)); }
        else 
        {    printf("child exited abnormally"); }
    }

    exit(exit_code);
}