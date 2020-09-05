/*
6) Escriba una función ISO C que permita procesar un archivo texto sobre sí mismo, que
contenga una palabra por línea. El procesamiento consiste en ordenar las palabras (líneas)
alfabéticamente considerando que el archivo no entra en memoria.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 256

bool read_word(FILE *file, char *buffer, long int *seek)
{
    fseek(file, *seek, SEEK_SET);
    char *word = fgets(buffer, BUFSIZE, file);
    *seek = ftell(file);
    return (word != NULL);
}

void write_word(FILE *file, char *buffer, long int *seek)
{
    fseek(file, *seek, SEEK_SET);
    fputs(buffer, file);
    *seek = ftell(file);
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    char word1[BUFSIZE];
    char word2[BUFSIZE];

    long int read_seek = 0;
    long int write_seek = 0;
    long int read_seek_before = 0;
    long int write_seek_before = 0;

    bool ordered = false;
    bool eof = false;
    FILE *file = fopen(filename, "r+");

    while (!ordered)
    {
        ordered = true;
        while (!eof)
        {
            eof = !read_word(file, word1, &read_seek);
            size_t word1_long = strlen(word1);
            eof |= !read_word(file, word2, &read_seek);
            if(eof) break;
            size_t word2_long = strlen(word2);

            if (strcmp(word1, word2) <= 0)
            {
                write_word(file, word1, &write_seek);
                write_word(file, word2, &write_seek);
                read_seek -= word2_long;
                write_seek -= word2_long;
            }
            else
            {
                write_word(file, word2, &write_seek);
                write_word(file, word1, &write_seek);
                read_seek -= word1_long;
                write_seek -= word1_long;
                ordered = false;
            }
        }
        eof = false;
        read_seek = 0;
        write_seek = 0;
    }
    fclose(file);
    return 0;
}
