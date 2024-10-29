/*
    <pthread.h> : pthread_cancel(), pthread_setcancelstate(), pthread_setcanceltype()

    int pthread_cancel(pthread_t thread_id);
    - called by the thread that wants the cancel the thread with thread_id.

    int pthread_setcancelstate(int state, int *oldstate);
    - called by the thread that wants to handle the cancel request coming form another thread.
    - state :   PTHREAD_CANCEL_ENABLE   (act upon cancel request coming from another thread), 
                PTHREAD_CANCEL_DISABLE  (ignore cancel request coming from other threads) 
    - oldstate points to the previous state.
    
    int pthread_setcanceltype(int type, int *oldstate);
    - called if cancel state is PTHREAD_CANCEL_ENABLE.
    - type :    PTHREAD_CANCEL_ASYNCHRONOUS (causes cancel request to be acted upon immediately)
                PTHREAD_CANCEL_DEFFERED (wait until thread executes one of the following func's)
                    - pthread_join()
                    - pthread_cond_wait()
                    - pthread_cond_timedwait()
                    - pthread_testcancel()
                    - sem_wait() 
                    - sig_wait()

    by default : PTHREAD_CANCEL_ENABLE, PTHREAD_CANCEL_DEFFERED

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg);

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_func, NULL);
    
    sleep(5);

    pthread_cancel(thread_id);

    pthread_join(thread_id, NULL);

    printf("\nthread_joined.\n");

    exit(0);
}

void *thread_func(void *arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    printf("thread running ");
    while(1)
    {
        printf(". ");
        sleep(1);
    }
    printf("exiting thread"); // never executes cause type is asynchronous
    pthread_exit(NULL);
}