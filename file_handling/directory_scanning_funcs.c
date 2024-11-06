/*
    <dirent.h> 
    <sys/types.h>
    
    DIR *opendir(const char *name);
    - opens a directory and establishes a directory stream
    - note, directory stream also uses a low-level file descriptor to acces directory

    struct dirent *readdir(DIR *dirstream);
    - returns pointer to a structure detailing the next directory entry. successive calls returns further directory entries.
    - returns null if error(errno set) or end-of-directory(errno unchanged) reached

    long int telldir(DIR *dirstream);
    - returns the value that records the current position in a directory stream

    void seekdir(SIR *dirstream, long int loc);
    - sets the directory entry pointer in the directory stream to the loc mentioned
    - value of loc used to update the position should be ebtained using telldir() beforehand

    int closedir(DIR *dirstram);
    - closes stream. returns 0 on success, -1 on failure.

    dirent structure :  
    - ino_t d_ino : the inode of the file
    - char dname[]: the name of the file
    - use stat() for more details about a file

    DIR structure is used for directory stream

    char *getcwd(char *buf, size_t size);
    - to get current working directory. current directory path is stored in buf. keep the size to PATH_MAX (from limits.h)

    int chdir(const char *path);
    - change the current working directory to the path mentioned

    use readdir() to determine entry d_ino and d_name. use lstat() to determine other details about the entry using d_name of that entry. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void printdirtree(char *dir, int depth)
{
    DIR *dir_stream;
    struct dirent *dir_entry;
    struct stat statbuf;

    dir_stream = opendir(dir); // open directory stream
    if(dir_stream == NULL)
    {
        perror("error :");
        exit(-1);
    }

    chdir(dir); // go to starting point

    while((dir_entry = readdir(dir_stream)) != NULL) // while end of directory entries is not reached
    {
        lstat(dir_entry->d_name, &statbuf); // get rest of the information about the entry and story in statbuf

        if(S_ISDIR(statbuf.st_mode)) // if current entry is a directory, printf directory name then call this function again
        {
            if(!strcmp(".", dir_entry->d_name) || !strcmp("..", dir_entry->d_name) || !strcmp(".git", dir_entry->d_name))
                continue;
            printf("%*s%s/\n", depth, " ", dir_entry->d_name);

            printdirtree(dir_entry->d_name, depth+4); // increase depth in the next function call to indicate depth
        }
        else // if current entry is a file, print file name
        {
            printf("%*s%s\n", depth, " ", dir_entry->d_name); 
        }
    }

    chdir("..");    // this gets executed when all the entries in the current directory are scanned. 
                    // move to upper level and exit
    closedir(dir_stream);
}

/*
int main(int argc, char *argv[])
{
    if(argc > 2)
        exit(-1);
    printf("Directory scan: %s\n", argv[1]);
    printdirtree(argv[1],0);
    exit(0);
}
*/

int main()
{
    printf("Directory scan:\n");
    printdirtree("/home/ubuntu/study",0);
    exit(0);
}
