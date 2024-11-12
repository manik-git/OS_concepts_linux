/*
    to be run in parallel with fifo_named_pipe_2.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

int main()
{
    int pipe_fd = open(FIFO_NAME, O_RDONLY);

    if(pipe_fd != -1)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);

        int nbytes = 0, res = 0;
        do{
            res = read(pipe_fd, buffer, BUFFER_SIZE);
            nbytes += res;
        }while(res > 0);

        close(pipe_fd);

        printf("data received: %f MB\n", (((float)nbytes/1024.0)/1024.0));
    }
    else
    {
        perror("error: ");
        exit(-1);
    }

    exit(0);
}
