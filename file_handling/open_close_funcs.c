/*
    <fcntl.h> : open()
    <unistd.h> : close()

    int open(const char *path, int oflags);
    int open(const char *path, int oflags, mode_t mode); mode is useful at the time of creating a new file, otherwise above form is enough
    - opens an access path to a file or device
    - returns a file descriptor used in read, write and other system calls
    - first argument is the name and path of the file to be opened or created
    - second argument spcifies action to be taken as following 
            - O_RDONLY  : open for read only
            - O_WRONLY  : open for write only
            - O_RDWR    : open for reading and writing
            - o_APPEND  : write at the end of the file. that means at the time of opening the offset will start from the end of the file. 
            - O_TRUNC   : set length of the file to zero, discarding existing content. that means at the time of opening the offset will start at the start of the file. if you start writing there and stop writing before the last text, the remaining text will still be there. 
            - O_CREAT   : create the file, if necessary, with permissions given in mode
            - O_EXCL    : used with O_CREAT. now if the file already exists, open will fail
    - the third argument mode is about user, group and others permission request to read, write and execute the file being created.
      this parameter will be avoided if the file is not being created. 
        - S_I[read/write/execute(1 letter)][user/group/others(3 letters)]
            - S_IRUSR: read persmision, owner
            - S_IWGRP: write permission, group
            - S_IXOTH: execute permission, others
            - etc.
      the final permissions set are based on output of "mode & !umask". mode is just a programs request to give mentioned permissions to the create file, final call is based on umask values set in system
      "umask" is a system variable. encodes a mask for file permissions. 
            - 3 digits, each for user, group, others. (in this order only) 
            - each digit is of 3 bits, each bit for read, write, execute permissions (in this order only). when a bit is set, that means that permissoin is disallowed
            - if umask is 032, means 
                - user is allowed everything
                - group is 3 (i.e. 011) means NOT allowed to write and execute
                - other is 2 (i.e. 010) means NOT allowed to write
                - means that "Do not create any files with write permissions to others and with write and execute permissions to groups even if the program creating it is requesting these permissions"

    note:
    - if 2 programs accessing same file will have separate fd's for that file. Each keeps its own idea of how far in the file they have read or written
    - new fd given will always will be the lowest one available. if some existing fd is closed, it will become available for the taking in the next open() call
    - OPEN_MAX in <limits.h> tells the number of files a running program can have open

    int close(int fildes);
    - terminates association between fildes and it file
    - the fildes becomes available to reuse
    - importand to check the return value. sometimes read write return error after closing thr fd.
    - returns 0 for success, -1 for error
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd = open("file2.txt", O_CREAT | O_RDWR, 0766); // Create the file with read-write permissions
                                                        // 0766: initial 0 is to represent octal. 7(111) is for user permissions, 6(110) is for group permissons, 6(110) is for others permissions

    if (fd == -1) 
    {
        perror("Error opening file");
        exit(1);
    }

    printf("fd : %d\n", fd);

    if (write(fd, "this is text\n", 13) != 13) 
    {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }

    // important : reset file offset to the beginning for reading
    lseek(fd, 0, SEEK_SET);

    char buf[15] = {0};
    if (read(fd, buf, 15) == -1) 
    {
        perror("Error reading from file");
        close(fd);
        exit(1);
    }

    printf("file contains:\n%s\n", buf);

    close(fd);

    return 0;
}
