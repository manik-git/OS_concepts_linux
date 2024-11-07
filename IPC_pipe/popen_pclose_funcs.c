/*
    <stdio.h>

    FILE *popen(const char *cmd, const char *open_mode);
    - allows a program to invoke another program as a new process and either pass data to it or receive data from it
    - cmd is the name of the program to run along with any parameters
    - open_mode must be either "r" or "w", not both
        - "r" : output from the invoked program is read in the invoking program from the stream returned by popen, using fread()
        - "w" : the invoking program can send data to the invoked program from the stream returned by popen, using fwrite()
    - if a bidirectional communication is required with the cmd, open 2 pipes.

    int pclose(FILE *stream);
    - close the stream opened by popen
    - blocking. will return only when the invoked program is finished
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    /*read input from a command*/

    char buf[BUFSIZ + 1];
    memset(buf, '\0', sizeof(buf));

    FILE *in_stream = popen("uname -a", "r");
    if(in_stream)
    {
        int nbytes;
        if((nbytes = fread(buf, sizeof(char), BUFSIZ, in_stream)) > 0)
        {
            printf("command(program) returned:\n%s\n", buf);
        }
        pclose(in_stream);

    }
    else
    {
        perror("error runing command: ");
        exit(-1);
    }

    /*give some input to another program*/
    
    memset(buf, '\0', sizeof(buf));
    sprintf(buf, "good vibes.....\n");

    FILE *out_stream = popen("od -c", "w");
    if(out_stream)
    {
        printf("writing to command(program) ...\n");
        fwrite(buf, sizeof(char), BUFSIZ, out_stream);
        pclose(out_stream);
    }
    else
    {
        perror("error running command: ");
        exit(-1);
    }

    exit(0);
}