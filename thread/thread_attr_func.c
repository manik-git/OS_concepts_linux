/*
    <pthread.h> :   pthread_attr_init(), 
                    pthread_attr_setdetachstate(),
                    pthread_attr_getdetachstate(),
                    pthread_attr_setschedpolicy(),
                    pthread_attr_getschedpolicy().. etc. 

    int pthread_attr_init(&pthread_attr_t *attr);
    - init's attributed that will be used in pthread_create().
    - 0 on success, non-zero otherwise.

    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    - second parameter decides if the main thread should wait for the thread to finish or not. 
    - possible values of detachstate : PTHREAD_CREATE_JOINABLE(by default) and PTHREAD_CREATE_DETACHED.
    - if state is PTHREAD_CREATE_DETACHED, pthread_join() can not be used. 
    - this can be useful where a thread is created to do some tasks on which main thread is not dependant.

    int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate)
    - notice the pointer in second argument. 

    rest of the functions are for setting scheduling policy and thread priorities of execution. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg);
int time_to_exit = 0;
char msg[] = "this is a sample message";

int main()
{
    pthread_t thread_id;
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    printf("[main]\t\tstarting thread now.\n");
    pthread_create(&thread_id, &thread_attr, thread_func, (void *)msg);

    pthread_attr_destroy(&thread_attr);

    while(!time_to_exit)
    {
        sleep(1);
    }

    printf("[main]\t\texiting now.\n");

    exit(0);
}

void *thread_func(void *arg)
{
    printf("[thread]\tstarted with arg : %s\n", (char *)arg);
    sleep(1);
    printf("[thread]\texiting now.\n");
    time_to_exit = 1;
    pthread_exit(NULL);
}