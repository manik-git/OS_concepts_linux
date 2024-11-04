/*
    int fstat(int fildes, struct stat *buf);
    int stat(const char *path, struct stat *buf);
    int lstat(const char *path, struct stat *buf);
    - all of the above return information about the file mentioned through path or a file desc'or.
    - lstat and stat return the same results except when the path given is a link, then lstat returns info about the link itself while stat will return info about the file pointed by the link
    - infor is returned in buf, a stat structure. members of stat struct are
        - st_mode   : file permissions and file-type info
        - st_ino    : inode associated with the file
        - st_dev    : device this file resides on
        - st_uid    : user id of the file owner
        - st_gid    : group id of the file owner
        - st_atime  : time of last access
        - st_ctime  : time of last change to permissions, owner, group or content
        - st_mtime  : time of last modification to content
        - st_nlink  : number of hard links to the file
    - associated macros with st_mode flags in stat buffer, as defined in sys/stat.h
        - file type flags
            - S_IFBLK   : entry is block special device
            - S_IFDIR   : entry is directory 
            - S_IFCHR   : entry is a character special device
            - S_IFIFO   : entry is a FIFO(names pipe)
            - S_IFREG   : entry is a regular file
            - S_IFLNK   : entry is a symbolic link 
        - other mode flags include
            - S_ISUID   : entry has setUID for execution
            - S_ISGID   : entry has setGID for execution
        - masks to interpret st_mode flags. these are &'d with st_mode output and compared with permission flags(used in open())
            - S_IFMT    : file type
            - S_IRWXU   : user read/write/execute permissions
            - S_IRWXG   : group read/write/execute permissions
            - S_IRWXO   : other read/write/execute permissions
        - macros to determine file types
            - S_ISBLK(mode)     : test for block special file
            - S_ISCHR(mode)     : test for character special file 
            - S_ISDIR(mode)     : test for directory
            - S_ISFIFO(mode)    : test for FIFO
            - S_ISREG(mode)     : test for regular file
            - S_ISLNK(mode)     : test for symbolic link
*/

/*
    For example, to test that a file 
        - is not a directory 
        - has execute permission set for the owner, read permission set for the group and no other persmission

    struct stat statbuf;
    mode_t mode;

    stat("filename", &statbuf);
    mode = statbuf.st_mode;

    if( !S_ISDIR(mode) && ((mode & S_IRWXU) == (S_IXUSR & S_IRGRP)))
    { ... }
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    exit(0);
}