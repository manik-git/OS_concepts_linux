/*
    to use exec with pipe(), convert the populated fd array element to string then send as argument in exec call
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char msg[] = "Hello from invoking program";
    char buf[BUFSIZ+1];
    int fd[2];
    pid_t pid;

    if(pipe(fd) == 0)
    {
        pid = fork();

        switch(pid)
        {
            case 0:
                sprintf(buf, "%d %d", fd[0], fd[1]); //convert fd[0] and fd[1] values to string to pass as parameter in exec()
                (void)execl("pipe_with_exec_2", "pipe_with_exec_2", buf, (char *)0);
                exit(-1);
            
            default:
                write(fd[1], msg, strlen(msg));
        }
    }
    else
    {
        perror("error: ");
        exit(-1);
    }

    exit(0);
}