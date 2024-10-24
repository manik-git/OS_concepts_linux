/*
    <signal.h>: sigaddset(), sigemptyset(), sigfillset(), sigdelset()
                sigismember(), sigprocmask(), sigpending(), sigsuspend()
    <unistd.h>: sleep()
    <stdlib.h>: exit()

    sigset_t: data type for sets of signals

    int sigaddset(sigset_t *set, int signo) : to add a signal signo to set
    int sigemptyset(sigset_t *set) : remove all signals in set
    int sigfillset(sigset_t *set) : add all defined signals to set
    int sigdelset(sigset_t *set, int signo) : remove signal signo from set
    - all of the above returns -1 if failed, 0 if successful

    int sigismember(sigset_t *sig, int signo) : returns 1 if signal signo is a member of set, returns 0 otherwise

    int sigprocmask(int how, const sigset_t *set, const sigset_t *oset)
    - change the signal mask of the process using set argument based on how argument
    - how : 
            - SIG_BLOCK : signals in set are added to the signal mask
            - SIG_SETMASK : set becomes the signal mask
            _ SIG_UNBLOCK : signals in set are removed from signal mask
    - oset stores the previous value of the mask
    - returns -1 if failed, 0 if successful

    int sigpending(sigset_t *set) : writes a set of signals in set argument, that are blocked from delivery and are pending
    - if a signal is blocked by a process using signal mask, it will not be delivered, but will remain pending

    int sigsuspend(const sigset_t *set)
    - when this is function is called, set replaces the process signal mask. 
    - the execution is then suspended until a signal from this set is received and signal handler function is done handling it
    - if the received signal terminates the process, sigsuspend() will never return

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    exit(0);
}