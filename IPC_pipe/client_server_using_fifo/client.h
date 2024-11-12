/*
    common header file for client.c and server.c
    - FIFO name macros
    - data structure for the data to be passed between server and client

    client would pass its own PID and some data to be processed
    the PID sent by client would be used by server to open a FIFO (created by that client) to send response to the request
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO_NAME "/tmp/server_fifo"
#define CLIENT_FIFO_NAME "/tmp/client_%d_fifo"

#define BUFFER_SIZE 20

struct data_to_pass_st 
{
    pid_t client_pid;
    char some_data[BUFFER_SIZE-1];
};