/*
    <semaphore.h> : sem_init(), sem_wait(), sem_post(), sem_destroy(), sem_trywait()

    int sem_init(sem_t *sem, int pshared, unsigned int val);
    - initialises semaphore that is pointed to by sem. 
    - pshared is 0 means semaphore is local to the process. 1 means may be shared between processes.
    

    int sem_post(sem_t *sem);
    - atomically increases the value of semaphore pointed by sem by 1.

    int sem_wait(sem_t *sem);
    - atomically decreases the value of semaphore pointed by sem by 1
    - if the semaphore is already 0, this function will wait til its non-zero and then decrease by 1 and continue.
    

    int sem_destroy(sem_t *sem);
    - destroy semaphore and frees up if any resources are linked with the sempahore.
    - if there is some thread waiting for sem to be 1, this func will return an error.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_func(void *);
sem_t bin_sem;

#define WORK_AREA_SIZE 1024
char work_area[WORK_AREA_SIZE];

int main()
{

    pthread_t thread_id;
    
    sem_init(&bin_sem, 0, 0);

    pthread_create(&thread_id, NULL, thread_func, NULL);

    printf("\nStart typing. Press enter after sentence. Type end to exit.\n");
    while(strncmp("end", work_area, 3) != 0)
    {
        fgets(work_area, WORK_AREA_SIZE, stdin);
        sem_post(&bin_sem);
    }

    pthread_join(thread_id, NULL);

    sem_destroy(&bin_sem);

    exit(0);
}

void *thread_func(void *arg)
{
    sem_wait(&bin_sem);
    while(strncmp("end", work_area, 3) != 0)
    {
        printf("you entered %d characters\n", strlen(work_area)-1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}