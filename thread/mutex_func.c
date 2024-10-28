/*
    <pthread.h> : pthread_mutex_init(), pthread_mutex_lock(), pthread_mutex_unlock(), pthread_mutex_destroy()

    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
    - first parameter points to the mutex that is being init'd.
    - second parameter decides the behaviour of the mutex. by default is 'fast'. For now let's not change that and pass NULL.
    
    int pthread_mutex_lock(pthread_mutex_t *mutex);
    - locks the mutex. 
    - if mutex is already locked, the code waits till the mutex is unlocked elsewhere. 

    int pthread_mutex_unlock(pthread_mutex_t *mutex);
    - unlocks the mutex. 

    int pthread_mutex_destroy(pthread_mutex_t *mutex);
    - destroys the mutex and releases any resources linked with the mutex.

    all of the above returns 0 on success, non-zero otherwise.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_func(void *);
pthread_mutex_t my_mutex;

#define WORK_AREA_SIZE 1024
char work_area[WORK_AREA_SIZE];
int time_to_exit = 0;

int main()
{
    pthread_t thread_id;
    
    pthread_mutex_init(&my_mutex, NULL);

    pthread_create(&thread_id, NULL, thread_func, NULL);

    pthread_mutex_lock(&my_mutex);
    while(!time_to_exit)
    {
        fgets(work_area, WORK_AREA_SIZE, stdin);
        while(work_area[0] != '\0')
        {
            pthread_mutex_unlock(&my_mutex);
            sleep(1);
            pthread_mutex_lock(&my_mutex);
        }        
    }
    printf("[main]\t\ttime to exit.\n[main]\t\twaiting for thread to join.\n");
    pthread_join(thread_id, NULL);
    printf("[main]\t\tthread joined.\n");
    exit(0);
}

void *thread_func(void *arg)
{
    sleep(1);
    pthread_mutex_lock(&my_mutex);
    while(strncmp("end", work_area, 3) != 0)
    {
        printf("[thread]\tyou entered %d characters.\n", strlen(work_area)-1);
        work_area[0] = '\0';
        pthread_mutex_unlock(&my_mutex);
        sleep(1);
        pthread_mutex_lock(&my_mutex);
        while(work_area[0] == '\0')
        {
            pthread_mutex_unlock(&my_mutex);
            sleep(1);
            pthread_mutex_lock(&my_mutex);
        }
    }
    printf("[thread]\texiting.\n");
    time_to_exit = 1;
    work_area[0] = '\0';
    pthread_mutex_unlock(&my_mutex);
    pthread_exit(NULL);
}