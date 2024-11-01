/*
    <unistd.h> : ioctl()

    int ioctl(int fildes, int cmd, ...); 
    - first argument is the fd of the file/device you want to access
    - second argument cmd is the macro defined for the action to be taken
    - rest are the additional data needed, like arguments to the action mentioned in cmd macro definition
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Define the ioctl command
#define IOCTL_MAGIC 'x'
#define IOCTL_UPDATE_VALUE _IOR(IOCTL_MAGIC, 1, int)

// Mock ioctl function to simulate a device updating the variable
int mock_ioctl(int fd, unsigned long request, int *value) {
    if (request == IOCTL_UPDATE_VALUE) {
        *value = 42; // Set the variable to a new value
        return 0; // Indicate success
    }
    return -1; // Indicate failure if an unsupported request
}

// Function to update a variable using ioctl
void update_variable_with_ioctl(int *variable) {
    int fd = open("file2.txt", O_CREAT | O_RDWR, 0766);  // Simulate device open
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Call the mock ioctl to update the variable
    if (mock_ioctl(fd, IOCTL_UPDATE_VALUE, variable) == -1) {
        perror("ioctl failed");
    } else {
        printf("Variable updated to: %d\n", *variable);
    }

    close(fd);
}

int main() {
    int my_variable = 0;
    printf("Original value of variable: %d\n", my_variable);

    // Call the function that updates the variable using ioctl
    update_variable_with_ioctl(&my_variable);

    printf("Updated value of variable: %d\n", my_variable);
    return 0;
}

// output :
// Original value of variable: 0
// Variable updated to: 42
// Updated value of variable: 42


/*
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

// define IOCTL command codes, usually done in a header file for other files to access these codes. you can only pass Macros in ioctl and not the function names
// Although this doesn't directly associate a function with a macro in user-space code, it does indirectly map a command code to a function in the driver.
#define IOCTL_MAGIC 'x'
#define IOCTL_GET_STATUS _IOR(IOCTL_MAGIC, 1, int)
#define IOCTL_SET_STATUS _IOW(IOCTL_MAGIC, 2, int)
#define IOCTL_RESET      _IO(IOCTL_MAGIC, 3)

int main()
{
    int fd;
    int status;

    // Open the device file
    fd = open("device_path.txt", O_CREAT | O_RDWR, 0766);
    if (fd == -1) 
    {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Get device status
    if (ioctl(fd, IOCTL_GET_STATUS, &status) == -1) 
    {
        perror("IOCTL_GET_STATUS failed");
    } 
    else 
    {
        printf("Device status: %d\n", status);
    }

    // Set device status
    status = 1;  // New status value
    if (ioctl(fd, IOCTL_SET_STATUS, &status) == -1) 
    {
        perror("IOCTL_SET_STATUS failed");
    } 
    else 
    {
        printf("Device status set to: %d\n", status);
    }

    // Reset the device
    if (ioctl(fd, IOCTL_RESET) == -1) 
    {
        perror("IOCTL_RESET failed");
    } 
    else 
    {
        printf("Device reset successfully\n");
    }

    // Close the device file
    close(fd);
    return 0;
}
*/