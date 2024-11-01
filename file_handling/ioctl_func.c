/*
    <unistd.h> : ioctl()

    int ioctl(int fildes, int cmd, ...); 
    - first argument is the fd of the file/device you want to access
    - second argument cmd is the macro defined for the action to be taken
    - rest are the additional data needed, like arguments to the action mentioned in cmd macro definition
*/


/* ------------ mydevice.h --------------- */

// my_device.h
#ifndef MY_DEVICE_H
#define MY_DEVICE_H

#include <linux/ioctl.h>

#define IOCTL_MAGIC 'x'  // Unique magic number for the device

// Define IOCTL commands
#define IOCTL_GET_STATUS _IOR(IOCTL_MAGIC, 1, int)    // Read data from the device
#define IOCTL_SET_STATUS _IOW(IOCTL_MAGIC, 2, int)    // Write data to the device
#define IOCTL_RESET      _IO(IOCTL_MAGIC, 3)          // Command without arguments

#endif // MY_DEVICE_H


/* --------------- user_application.c ----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "my_device.h"  // Include the ioctl command definitions

int main()
{
    int fd;
    int status;

    // Open the device file
    fd = open("/dev/my_device", O_RDWR);
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Get device status
    if (ioctl(fd, IOCTL_GET_STATUS, &status) == -1) {
        perror("IOCTL_GET_STATUS failed");
    } else {
        printf("Device status: %d\n", status);
    }

    // Set device status
    status = 1;  // New status value
    if (ioctl(fd, IOCTL_SET_STATUS, &status) == -1) {
        perror("IOCTL_SET_STATUS failed");
    } else {
        printf("Device status set to: %d\n", status);
    }

    // Reset the device
    if (ioctl(fd, IOCTL_RESET) == -1) {
        perror("IOCTL_RESET failed");
    } else {
        printf("Device reset successfully\n");
    }

    // Close the device file
    close(fd);
    return 0;
}
