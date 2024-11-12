/*
    Named pipes(FIFO) are files that act as pipes for unrelated processes to communicate
    Use FIFO to pass in one direction only, otherwise the program might end up reading its own output back. For birectional communication, open 2 separate pipes

    ls -lF /tmp/my_fifo
    prwxr-xr-x 1 ubuntu ubuntu 0 Nov  8 20:57 /tmp/my_fifo|
    - notice the p in the starting of the file. indicates that the file is a pipe
 
    <sys/types.h>
    <sys/stat.h>

    int mkfifo(const char *filename, mode_t mode);
    - makes a FIFO(named pipe) of the filename mentioned. pass the absolute path for less confusion
    - second argument is the permissions this FIFO is opened with.

    open(const char *path, open_flag);
    - opens the FIFO created by mkfifo()
    - second argument should not be O_RDWR (since, FIFO's need to be uni-directinoal only)
    - second argument can take the following arguments
        - O_RDONLY - opens a FIFO for read only. open() will block until another process opens same FIFO for writing
        - O_WRONLY - opens a FIFO for write only. open() will block until another process opens same FIFO for reading
        - O_NONBLOCK - not passed alone. passed with OR-ing with above two. makes tham unblocking. 
    - returns file descriptor for read and write
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
        mkfifo(FIFO_NAME, 0777); // this 0777  is further modified user mask(umask) value of the system
    }

    int pipe_fd = open(FIFO_NAME, O_WRONLY);
    if(pipe_fd != -1)
    {
        int nbytes = 0, res = 0;
        char buffer[BUFFER_SIZE]; // we will pass an empty buffer of 10 MB through FIFO
        
        while(nbytes < TEN_MEG)
        {
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            nbytes += res;
        }

        close(pipe_fd); // close the fd related to the FIFO after use
    }
    else
    {
        perror("error: ");
        exit(-1);
    }

    exit(0);
}
