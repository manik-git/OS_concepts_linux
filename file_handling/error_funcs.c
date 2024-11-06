#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        // Check the error number set by fopen
        printf("Error opening file: %s\n", strerror(errno));  // Using strerror
        perror("Error using perror");                         // Using perror
    } else {
        fclose(file);
    }
    return 0;
}
