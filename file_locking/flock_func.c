/*
    #include <sys/file.h>
    
    int flock(int fd, int operation);
    - fd: File descriptor for the file you want to lock.
    - operation: Specifies the lock type.
        - LOCK_SH: Shared lock (read-only access, multiple processes can acquire).
        - LOCK_EX: Exclusive lock (write access, only one process can acquire).
        - LOCK_UN: Unlock the file.
        - LOCK_NB: Non-blocking option (optional); returns immediately if the lock can’t be acquired.

    note: create /tmp/LCK.test before running this code
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

const char lock_file[] = "/tmp/LCK.test";

int main() {
    int fd = open(lock_file, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Acquire an exclusive lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("flock");
        close(fd);
        exit(1);
    }

    // Perform some work while the lock is held
    printf("File locked exclusively. Doing some work...\n");

    // Release the lock
    if (flock(fd, LOCK_UN) == -1) {
        perror("flock unlock");
    }

    close(fd);
    unlink(lock_file);
    return 0;
}
