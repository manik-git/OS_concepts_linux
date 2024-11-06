/*
    note: see fcntl_flags.txt

    <fcntl.h>

    int fcntl(int fildes, int cmd);
    int fcntl(int fildes, int cmd, long arg);
    - perform several misc. operations on open fd's such as
        - duplicating fd's
        - getting and settig fd flags
        - getting and setting file status flags
        - managing file locking
        - etc.
    - operations are selected by cmd. based on cmd, a third arg might need to be passed
        - F_DUPFD : fcntl(fildes, F_DUPFD, new_fildes) : returns a new fd equal to or greater than new_fildes
        - F_GETFD : fcntl(fildes, F_GETFD) : returns the file descriptor flags
        - F_SETFD : fcntl(fildes, F_SETFD, flags) : set the fd flags
        - F_GETFL : fcntl(fildes, F_GETFL) : get file status flags and access modes. you can extract the file access modes by using the mask O_ACCMODE define in <fcntl.h>
        - F_SETFL : fcntl(fildes, F_SETFL, flags) : set file status flags and access modes
*/

// example to set FD_CLOEXEC so that the open fd closes when one of the exec calls happen

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int fd;

    fd = open("example.txt", O_RDWR | O_CREAT | O_APPEND, 0644);

        if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) 
    {
        perror("Error setting FD_CLOEXEC");
        close(fd);
        return 1;
    }

    printf("File opened successfully with descriptor %d\n", fd);

    close(fd);
    return 0;
}