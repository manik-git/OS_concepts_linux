/*
    to be used in execl() in pipe_with_exec_1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fildes_in, fildes_out;
    
    int nbytes;
    char buf[BUFSIZ+1];
    memset(buf, '\0', sizeof(buf));

    sscanf(argv[1], "%d %d", &fildes_in, &fildes_out);

    nbytes = read(fildes_in, buf, BUFSIZ);

    printf("Data from invoking program:\n%s [%d bytes]\n", buf, nbytes);

    exit(0);
}