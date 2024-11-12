/*
    file locking is a form of advisory(voluntary, process must check) locking (as opposed to mendatory locking, where the system will enforce lock behaviour). the program needs to take care
    this method creates a lock file in an atomic way, if a file is already created the process needs to wait until it can create the file with the same name
    a process can only access the critical section if it can create that specific lock file
    the programmer needs to be careful to use the same file name

    run multiple instances of the following file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

const char lock_file[] = "/tmp/LCK.text";

int main()
{
    int try_count = 10;

    while(try_count)
    {
        int fd = open(lock_file, O_RDWR | O_CREAT | O_EXCL, 0444);
        if(fd == -1)
        {
            printf("%d - file already exists\n", getpid());
            sleep(1);
        }
        else
        {
            printf("%d - file created and opened successfully [%d]\n", getpid(), try_count);
            sleep(1);
            close(fd);
            unlink(lock_file);
            try_count--;
            sleep(1);
        }
    }
    exit(0);
}