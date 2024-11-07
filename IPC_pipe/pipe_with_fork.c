/*
    use of pipe() to send data from parent to child
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char data[] = "some_data_from_parent_to_child";
    char buf[BUFSIZ + 1];

    int fd[2];

    if(pipe(fd) == 0)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            int nbytes = read(fd[0], buf, BUFSIZ);
            printf("[CHILD]\t\tData read\t:\t%s [%d bytes]\n", buf, nbytes);
        }
        else
        {
            write(fd[1], data, strlen(data));
            printf("[PARENT]\tData written\t:\t%s\n", data);
        }
   
        exit(0);
    } 

    exit(-1);
}