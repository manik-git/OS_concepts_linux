/*
    <unistd.h> : fork()
    <sys/types.h> : pid_t
    <sys/wait.h> : waitpid()

    pid_t waitpid(pid_t pid, int *stat_val, int options);
    - blocking, but can be made non-blocking by passing WNOHANG in options

    - pid argument specifies which pid to wait for
    - if pid argument is -1, waitpid returns info of any child process
    - stat_val same as in wait(). same macros can be used. 
    - stat_val when passed a null pointer will not store the child process info
    - options modify the behaviour of waitpid
    - most useful option is WNOHANG. this makes waitpid nonblocking
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int n, exit_code, child_terminated = 0;
    char *msg;
    pid_t pid;

    printf("this is parent process. forking now..\n");
    pid = fork();

    switch(pid)
    {
        case -1:
        printf("error while forking\n");
        exit(-1);

        case 0:
        msg = "\t\t\t\tchild";
        n = 3;
        exit_code = 37;
        break;

        default:
        msg = "parent";
        n = 10;
        exit_code = 0;
    }

    while(n--)
    {
        printf("%s(%d)[%d]\n",msg, getpid(), getppid());
        if(pid && !child_terminated)
        {
            pid_t child_pid = waitpid(-1, (int *)0, WNOHANG); // wait for anychild to finish, stat_val is not stored, do not hang(block)
            if(child_pid)
            {
                printf("child [%d] has terminated\n",child_pid);
                child_terminated = 1;
            }
        }
        sleep(1);
    }

    exit(0);
}