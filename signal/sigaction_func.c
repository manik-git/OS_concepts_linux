/*
    <signal.h>: sigaction(), struct sigaction, sigset_t
    <stdlib.h>: exit()
    <unistd.h>: sleep()

    int sigaction(int sig, const struct sigaction *act, const struct sigaction *oact);
    - sig is the signal to be caught and acted upon
    - act is the sigaction struct that specifies the action to be taken
    - oact is the sigaction struct where previous act values will be stored

    struct sigaction as at least the following three
    - void (*) (int) sa_handler : signal handler function or SIG_DFL(restore default behaviour) or SIG_IGN(ignore signal)
    - sigset_t sa_mask : signal to block IN sa_handler
    - int sa_flags : signal action modifiers
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static int sig_rx = 0;

void func(int sig)
{
    sig_rx = 1;
}

int main()
{
    struct sigaction act;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, 0);

    while(1)
    {
        if(sig_rx)
        {
            printf("signal received\n");
            sig_rx = 0;
        }
    }

    exit(0);
}