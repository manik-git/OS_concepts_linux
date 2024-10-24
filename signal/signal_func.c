/*
    - not recommended. better to use sigaction

    <signal.h> : signal()
    <unistd.h> : sleep()
    <stdlib.h> : exit()

    void (*signal(int sig, int *(func)(int)))(int);
    - sig is signal to catch
    - func is function(signal handler) to call when signal is caught
    - returns -1 if failed, 0 if successful
    - better to use a flag inside signal handler than to call functions like printf
    - need to re-establish the signal handler function inside signal handler after the signal handler is called. otherwise, default behaviour will happen

    - the problem with this code is ctrl-c happens before signal handler is re-established. so the program terminates in one-go only.
*/

/*
    Note:

    int (*func) (int, int)
    - this is a function pointer. 
    - it points to a function that takes 2 int's as arguments and returns int.
    - if you have a function named func_task()
      then, 
            func = func_task;
      now, func points to func_task

    int (*func(char, float)) (int,int)
    - this is a function. NOT a function pointer. Similar to the signal() mentioned above. 
    - this function takes a char and a float as arguments. 
    - this function returns a pointer to a function that takes 2 int arguments and returns an int.
    - func(1,2) can directly be called. 
    - a function pointer should be made to get what the func() returns.
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int sig_rx_flag = 0;
int sig_rx = 0;

void func(int sig)
{
    sig_rx_flag = 1;
    sig_rx = sig;
    sleep(1);
    (void) signal(SIGINT, SIG_DFL);
}

int main()
{
    (void) signal (SIGINT, func);

    while(1)
    {    
        if(sig_rx_flag)
            printf("signal received %d\n", sig_rx);
    }
    exit(0);
}