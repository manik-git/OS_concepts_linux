#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char *str1 = "ps"; // running command like this will block the program until the process is complete
    const char *str2 = "ps &"; // running a process in background.. this makes the system call non-blocking
    printf("starting a new process with system call\n");
    int exit_code = system(str1);
    printf("\n done with exit code : %d\n", exit_code);
    exit(0);
}