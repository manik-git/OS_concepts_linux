/*
    <unistd.h>

    int pipe(int fd[2]);
    - arg is a pointer to an array of 2 file descriptors. 
    - it fills the array with 2 fd's. 
    - data written to fd[1] using write() can be read from fd[2] using read() in a FIFO fashion

    unlike popen() a new shell is not created for this. pipe() is a lower level function
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd[2] = {0};
    char data[] = "some_data_over_pipe";
    char buf[BUFSIZ + 1];

    if(pipe(fd) == 0)
    {
        write(fd[1], data, strlen(data));
        printf("written on fd[1]: %s\n", data);

        read(fd[0], buf, BUFSIZ);
        printf("read from fd[0]: %s\n", buf);

        exit(0);
    }

    exit(-1);
}