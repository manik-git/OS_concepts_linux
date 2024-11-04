/*
    <unistd.h>      : lseek()
    <sys/types.h>   : off_t

    off_t lseek(int fd, off_t offset, int whence);
    - set the read/write pointer of the fd to the offset.
    - whence describe the offset is to be used
        - SEEK_SET : offset is an absolute position
        - SEEK_CUR : offset is relative to current position
        - SEEK_END : offset is relative to the end of file
    - returns offset measured in bytes from the beginning of the file
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    exit(0);
}