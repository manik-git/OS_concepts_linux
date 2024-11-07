/*
    example to demonstrate how to read from a command multiple times. 
    in the following example, if the output received from command is bigger than the buffer size(#define SIZE), it will read again. 
    if the output is smaller than the buffer size it will exit. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 75

int main()
{
    char buf[SIZE];
    memset(buf, '\0', sizeof(buf));

    FILE *in_stream = popen("ps","r");
    if(in_stream)
    {
        int nbytes;
        while((nbytes = fread(buf, sizeof(char), SIZE, in_stream)) > 0)
            printf("\noutput of command:\n%s\n", buf);
    }
    else
    {
        perror("error running command: ");
        exit(-1);
    }

    exit(0);
}