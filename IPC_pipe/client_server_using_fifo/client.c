/*
    - open server fifo created by sever.c
    - create a client name string with own PID and create client fifo with that name
        - fill data structure to be passed to server on server fifo
        - write data to server fifo
        - open cllient fifo create above
        - read precessed data (response) sent from the server on client fifo
        - close client fifo
        - repeat the number of times the data needs to be sent to server on server fifo
*/

#include "client.h"

int main()
{
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    char client_fifo_name[256];

    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    
    sprintf(client_fifo_name, CLIENT_FIFO_NAME, my_data.client_pid);
    mkfifo(client_fifo_name, 0777);

    my_data.client_pid = getpid();

    for(int i = 0; i < 5; i++)
    {
        sprintf(my_data.some_data, "Hello from %d", my_data.client_pid);
        printf("%d sent %s", my_data.client_pid, my_data.some_data);
        
        write(server_fifo_fd, &my_data, sizeof(struct data_to_pass_st));

        client_fifo_fd = open(client_fifo_name, O_RDONLY);
        if(read(client_fifo_fd, &my_data, sizeof(struct data_to_pass_st)) > 0)
        {
            printf(" | received %s\n", my_data.some_data);
        }

        close(client_fifo_fd);
    }

    close(client_fifo_fd);
    unlink(client_fifo_name);
    
    exit(0);
}