/*
    <signal.h>: kill(), signal()
    <stdlib.h>: exit()
    <unistd.h>: sleep(), pause()
    <sys/types.h>: pid_t

    int kill(pid_t pid, int sig);
    - pid to which signal is to be sent
    - sig is the signal to be sent
    - returns -1 if fails, 0 on success
    - calling process must have permissions to send signal( i.e. both processes must have same user ID)

    int pause(void);
    - used to suspend a process until a signal is received
    - sigsuspend is more commonly used
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int alarm_fired = 0;

void func(int sig)
{
    alarm_fired = 1;
}

int main()
{
    printf("starting main application\n");

    pid_t pid = fork();

    switch(pid)
    {
        case -1: 
        printf("error while forking\n");
        exit(-1);

        case 0: /*child*/
        printf("child: alarm will be fired in 5 sec\n");
        sleep(5);
        kill(getppid(),SIGALRM);
        exit(0);
    }

    printf("parent: waiting...\n");

    (void) signal(SIGALRM, func);
    pause();
    if(alarm_fired)
        printf("parent: alarm fired!\n");

    exit(0);
}