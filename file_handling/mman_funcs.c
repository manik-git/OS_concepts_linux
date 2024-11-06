/*
    <sys/mman.h>

    void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t offset);
    - creates a pointer to a region of memory( a segment in the virtual memory allocated to the process ) that is mapped to the memory where the content of the files are stored.
    - addr  : request a particular memory address. 0(recommended) means pointer is allocated automatically. 
    - len   : length of the memory segment
    - prot  : access permissions for the memory segment. bitwise OR of the following
        - PROT_READ     : the segment can be read
        - PROT_WRITE    : the segment can be written
        - PROT_EXEC     : the segment can be executed
        - PROT_NONE     : the segment can not be accessed
    - flags : how changes made to the segment are reflected elsewhere
        - MAP_PRIVATE   : the segment is private, changes are local
        - MAP_SHARED    : the changes made in segment are made in the file
        - MAP_FIXED     : the segment must be a the given addess, addr
    - fildes: open file's fd
    - offset: start of the file data that is shared by the memory
    - returned pointer will make file as an array of data, so it can be accessed like an array only

    int msync(void *addr, size_t len, int flags);
    - causes the changes made on part or all of the memory segment to be written(or read back from) the mapped file
    - addr  : the starting addess of the memory from/to where the data is to be read/written
    - len   : length of the memory segment
    - flags : how the update should be perfomed
        - MS_ASYNC      : perform async writes
        - MS_SYNC       : perform sync writes
        - MS_INVALIDATE : read data back in from the file

    int munmap(void *addr, size_t size);
    - release the memory segment
*/

/*
    note : If you need to use mmap and msync with RECORD structures, you should be aware that mmap will work with binary data, not text. Since each int is stored in binary format, it won’t appear in decimal as plain text. To view the data as you expect, you should open the file using a binary viewer or interpret the data in your program as binary.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define NRECORDS (100)

#pragma pack(1) // Ensure there is no padding in the RECORD struct
typedef struct
{
    int data;
    char string[24];
} RECORD;

int main()
{
    RECORD record;

    FILE *stream = fopen("records.txt", "w+");

    for(int i = 0; i < NRECORDS; i++)
    {
        record.data = i;
        sprintf(record.string, "RECORD-%d\n", i);
        fwrite(&record, sizeof(RECORD), 1, stream);
    }
    
    fclose(stream);

    /***** access 43rd record and change data to 243 *****/
    
    int fd = open("records.txt", O_RDWR);
    
    RECORD *memseg = (RECORD *)mmap(0, NRECORDS*sizeof(RECORD), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    memseg[43].data = 243;
    sprintf(memseg[43].string, "RECORD-%d\n", 243);

    msync((void *)memseg, NRECORDS*sizeof(RECORD), MS_ASYNC);

    munmap((void *)memseg, NRECORDS*sizeof(RECORD));

    close(fd);

    exit(0);
}