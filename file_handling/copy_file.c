/*
    purpose of this code is to copy a 1 KB file in chunks of 1 KB to another file 1024 times to make a 1 MB file.
    run: la -al after running this code to verify
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("file.txt", O_RDONLY);
    int fd_c = open("file_copy.txt", O_CREAT | O_WRONLY | O_TRUNC, 0766);
    if(fd == -1 || fd_c == -1)
    {
        perror("unable to open file\n");
        exit(-1);
    }

    char chunk[1024];
    int nread = 0, i = 1024;
    while(i--)
    {   
        lseek(fd, 0, SEEK_SET); // reset file offset to the beginning to read
        nread = read(fd, chunk, 1024);
        write(fd_c, chunk, nread);
        printf(".");
    }

    printf("\n");
    exit(0);
}