/*
    <stdio.h>

    int printf(const char *format, ...);
    int fprintf(FILE *stream, const char *format, ...);
    int sprintf(char *s, const char *format, ...);
    - printf data to stdout, stream or string respectively according to the format 

    int scanf(const char *format, ...);
    int fprintf(FILE *stream, const char *format, ...);
    int sprintf(char *s, const char *format, ...);
    - read data from stdin, stream or string respectively according to the format
    - note, format mentioned in second parameter should be same as the data is stored in file or string
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *file = fopen("file_format.txt", "r");
    if(file == NULL)
        exit(-1);

    int id;
    float weight;
    char name[50];
    char s[100];

    while(!feof(file))
    {
        if(fscanf(file, "%d %10s %f", &id, name, &weight) == 3)
            sprintf(s, "ID: %d\nName: %s\nWeight: %2.1f\n", id, name, weight);

        printf("%s\n",s);
    }

    exit(0);
}
