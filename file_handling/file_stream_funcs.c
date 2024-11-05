/*
    <stdio.h>   

    FILE *fopen(const char *filename, const char *mode);
    - returns a stream(pointer to a structure FILE) to a file filename. if fails returns null
    - mode specifies how the file is to be opened
        - r / rb            : open for reading only
        - w / wb            : open for writing, truncate to zero length
        - a / ab            : open for writing, append to end of file
        - r+ / rb+ / r+b    : open for update (reading and writing)
        - w+ / wb+ / w+b    : open for update, truncate to length zero
        - a+ / ab+ / a+b    : open for update, append to end of file
        -- b means the file is a binary file and not a normal text file
    - number of available streams are limited - FOPEN_MAX define in <stdio.h>

    size_t fread(void *bufptr, size_t size, size_t nitems, FILE *stream); 
    - read nitems(third arg) of size size(second arg) from file stream stream(fourth arg) and store in buffer pointed to by bufptr(first arg)
    - returns the number of items of mentioned size read. not the bytes, but the count of nitems of mentioned size.
      this can be less then nitems(third arg) or zero.

    size_t fwrite(const void *bufptr, size_t size, size_t nitems, FILE *stream);
    - takes data from buffer pointed by bufptr, writes them in stream nitems times. each nitem is of size size. 
    - returns count of items written. 

    int fclose(FILE *stream);
    - closes the stream
    - to make sure that the data is completely written, make sure to call fclose()

    int fflush(FILE *stream);
    - outstanding data on a file stream to be written immediately
    - implicit flush happens on fclose(). no need to call fflush() before fclose()

    int fseek(FILE *stream, long int offset, int whence);
    - similar to lseek() system call
    - sets position in the stream for the next read and write operation
    - returns 0 on success, -1 on failure

    int feof(FILE *stream);
    - returns non-zero if end of file is reached, 0 if not.

    int fgetc(FILE *stream);
    int getc(FILE *stream);
    int getchar();
    - fgetc returns the next int from the file stream
    - getc is same as fgetc but may be implemented as a macro
    - getchar is getc(stdin);

    int fputc(int c, FILE *stream);
    int putc(int c, FILE *stream);
    int putchar(int c);
    - same as above but it writes on the output stream

    char *fgets(char *buf, int n, FILE *stream);
    char *gets(char *s);
    - fgets reads string from input stream, writes it on buf until
        - newline is encountered
        - n-1 characters have been transferred 
        - EOF is reached
    - returns pointer to buf. if EOF file is reached then set EOP indicator in stream and returns null. if error then returns null and errno shows the error.

    FILE *fdopen(int fildes, const char *mode);
    - opens a stream for the passed file descriptor. 
    - basically, the function provides a stdio buffer on an already opened file descriptor

    int fileno(FILE *stream);
    - returns low-level file descriptor opened for the file for this stream

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    exit(0);
}