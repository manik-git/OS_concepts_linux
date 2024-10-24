/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_func(void *arg);

char msg[] = "This is a thread program";

int main()
{
    printf("this is the main application\n");

    pthread_t thread_1;

    int res = pthread_create(&thread_1, NULL, thread_func, (void *)msg);
    if(res)
    {
        printf("error creating thread\n");
        exit(-1);
    }

    printf("waiting for thread to join\n\n");

    void *thread_res;
    res = pthread_join(thread_1, &thread_res);
    if(res)
    {
        printf("error joining thread\n");
        exit(-1);
    }

    printf("\nthread joined.\nThread returned : %s\n", (char *)thread_res);
    printf("msg is now : %s\n", msg);

    exit(0);
}

void *thread_func(void *arg)
{
    printf("thread will run for 2 seconds.\narg : %s\n", (char *)arg);
    sleep(2);
    strcpy(msg,"thread complete");
    pthread_exit("This was a good thread");
}