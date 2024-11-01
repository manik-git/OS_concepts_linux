/*
    <unistd.h> : write(), read()
    <fcntl.h> : open() 

    size_t write(int fildes, const void *buf, size_t nbytes);
    - write TO file associated with file descriptor "fildes" FROM buffer "buf"
    - returns the number of bytes successfully written. this could be less than what was intended.

    size_t read(int fildes, void *buf, size_t nbytes);
    - read FROM file associated with file descripted "fildes" TO buffer "buf"
    - returns the bytes of data read which may be less than the number of bytes requested. 

    int open(const char *path, int oflags);
    int open(const char *path, int oflags, mode_t mode);


*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    size_t nread;
    char buf[128];

    nread = read(0, buf, 128);
    if(nread == -1)
        write(2, "error1\n", 7);

    if(write(1, buf, nread) != nread)
        write(2, "error2\n", 7);


    exit(0);
}