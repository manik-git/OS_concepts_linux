#include "client.h"

int main()
{
    mkfifo(SERVER_FIFO_NAME, 0777);
    
    int server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);

    sleep(10);

    int nbytes = 0;
    
    struct data_to_pass_st my_data;
    char *tmp_str_ptr;

    char client_fifo_name[256];
    int client_fifo_fd;

    do{
        
        nbytes = read(server_fifo_fd, &my_data, sizeof(struct data_to_pass_st));
        tmp_str_ptr = my_data.some_data;
        while(*tmp_str_ptr)
        {
            *tmp_str_ptr = toupper(*tmp_str_ptr);
            tmp_str_ptr++;
        }
        
        sprintf(client_fifo_name, CLIENT_FIFO_NAME, my_data.client_pid);
        client_fifo_fd = open(client_fifo_name, O_WRONLY);
        write(client_fifo_fd, &my_data, sizeof(struct data_to_pass_st));
        close(client_fifo_fd);

    }while(nbytes > 0);

    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
    exit(0);
}