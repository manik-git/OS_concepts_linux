/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024 * 1024 * 10)

int main()
{
    if(access(FIFO_NAME, F_OK) == -1)
    {
        mkfifo(FIFO_NAME, 0777);
    }

    int pipe_fd = open(FIFO_NAME, O_WRONLY);
    if(pipe_fd != -1)
    {
        int nbytes = 0, res = 0;
        char buffer[BUFFER_SIZE];
        
        while(nbytes < TEN_MEG)
        {
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            nbytes += res;
        }

        close(pipe_fd);
    }
    else
    {
        perror("error: ");
        exit(-1);
    }

    exit(0);
}
