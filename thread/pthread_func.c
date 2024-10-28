/*

    <pthread.h> : pthread_t, pthread_create(), pthread_exit(), pthread_join()
    <string.h> : sleep functions

    int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *)), void *arg);
    - first argument is a thread identifier. points to a memory location where this identifier is stored. 
    - second argument sets thread attributes
    - third argument is a function pointer that points to that function that runs in this thread
      this function takes a void pointer and returns a void pointer. So you can pass any type of argument and return any type of argument. 
    - fourth argument is arguments passed to the thread function. notice the void *. 
    - returns 0 on success, non zero otherwise

    void pthread_exit(void *retval);
    - when a thread function is to exit, this function is called much like exit() is called when a process is ended. 
    - this function terminates the thread. returning a pointer to retval. never return a pointer to a local object as it will cease to exist. 

    int pthread_join(pthread_t *thread, void **thread_retval);
    - this is like wait function in process. It is called in main function to wait for a specific thread to be terminated. 
    - the first argument is pointer to the thread identifier created by pthread_create().
    - second argument is a double pointer that holds the address of the pointer that points to the object returned by thread. 
    - returns 0 on success, non-zero otherwise. 

*/

#include <stdio.h>
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