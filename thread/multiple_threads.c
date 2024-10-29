#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NO_OF_THREADS 5

void *thread_func(void *arg);

int main()
{
    pthread_t thread_id[NO_OF_THREADS];
    
    for(int i = 0; i < NO_OF_THREADS; i++)
    {
        printf("[main]\t\tcreating thread %d\n", i);
        pthread_create(&thread_id[i], NULL, thread_func, (void *)&i);
        sleep(1);
    }

    for(int i = 0; i < NO_OF_THREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    printf("[main]\t\tall done.\n");

    exit(0);
}

void *thread_func(void *arg)
{
    int num = *(int *)arg; // important to save arg val in another variable coz value of arg is being changed in main thread and arg is passed by ref in thread_func

    printf("[thread]\t\t\t\t\targ : %d\n", num);

    sleep((int)(9.0*rand()/(RAND_MAX+1.0)));

    printf("[thread]\t\t\t\t\texiting thread %d\n", num);

    pthread_exit("exit.");
}