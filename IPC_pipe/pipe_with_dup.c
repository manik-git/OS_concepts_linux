/*
    implement output of 
        echo "this is message" | od -c

    echo "this is message" is implemented in parent process
    od -c is implemented in child process
    output of parent process is to be sent on fd 0 of child process i.e. standard input of the child process is replaced with read end of the pipe created
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    char msg[] = "Hello from parent";

    if(pipe(fd) == 0)
    {
        pid_t pid = fork();

        switch(pid)
        {
            case 0:
                close(fd[1]); // this is necessary otherwise the data passed to execlp() might not be complete
                close(0);
                dup(fd[0]); // this will duplicate the fd[0] file descriptor to smallest fd available, which will be 0 only since fd 0 was just freed
                execlp("od", "od", "-c", (char *)0);    // now the stdin of the new program being run will be same as fd[0]
                                                        // note, od is just another program that considers anything written next to it as input, but now since the stdin is changed it will take input from fd[0]
                exit(-1);

            default:
                close(fd[0]);
                write(fd[1], msg, strlen(msg)); 
        }
    }
    else
    {
        perror("error:  ");
        exit(-1);
    }
    exit(0);
}