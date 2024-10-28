#include <stdio.h>
#include <pthread.h>

int run1 = 1, run2 = 0, main_thread_running = 1;
void *thread_func(void *);

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_func, NULL);
    int run_count = 0;
    while(run_count < 5)
    {
        if(run1)
        {
            run_count++;
            printf("main [%d]\n", run_count);
            run1 = 0;
            run2 = 1;
        }
        else 
        {
            sleep(1);
        }
    }
    main_thread_running = 0;
    printf("[main]\t\twaiting for thread to join.\n");
    pthread_join(thread_id, NULL);
    printf("[main]\t\tthread joined.\n");
    exit(0);
}

void *thread_func(void *arg)
{
    int run_count = 0;
    while(run_count < 20)
    {
        if(!main_thread_running)
        {
            printf("[thread]\tmain thread not running.\n");
            sleep(5);
            pthread_exit(NULL);
        }
        if(run2)
        {
            run_count++;
            printf("\t\tthread [%d]\n", run_count);
            run2 = 0;
            run1 = 1;
        }
        else
        {
            sleep(1);
        }
    }
    pthread_exit(NULL);
}