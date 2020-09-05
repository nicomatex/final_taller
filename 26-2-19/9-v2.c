/*
9) Escribir un programa ISO C que procese el archivo de texto cuyo nombre es recibido como
parámetro. El procesamiento consiste en leer oraciones y suprimir aquellas que tengan
más de 3 palabras. Asuma que el archivo no puede cargarse en memoria, pero una oración
sí puede.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 256

size_t word_count(char* sentence){
    size_t i = 0;
    size_t word_count = 1;

    while(sentence[i]){
        if(sentence[i++] == ' ') word_count++;
    }
    return word_count;
}

int readc(FILE* f,long int* seek){
    fseek(f,*seek,SEEK_SET);
    int out = fgetc(f);
    *seek = ftell(f);
    return out;
}

void writec(FILE* f,char c,long int* seek){
    fseek(f,*seek,SEEK_SET);
    fputc(c,f);
    *seek = ftell(f);
}

int main(int argc, char* argv[]){
    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");

    char buffer[BUFSIZE];
    memset(buffer,0,BUFSIZE);
    size_t bytes_read;
    
    long int seek_read = 0;
    long int seek_write = 0;

    long int c_final = 0;

    int c = 0;
    
    size_t buff_pos = 0;

    bool end_found = false;

    while( (c = readc(file,&seek_read)) != EOF){
        c_final++;
        if(!end_found){
            buffer[buff_pos] = c;
            end_found = (c == '.');
            buff_pos++;
            if(!end_found) continue;
        }
        int spaces = 0;
        for(size_t i = 0;i < buff_pos; i++){
            if(buffer[i] == ' ') spaces++;
        }

        bool too_many_words = (spaces >= 3);
        if(too_many_words){
            c_final -= buff_pos;
        }else{
            for(size_t i = 0;i < buff_pos;i++){
                writec(file,buffer[i],&seek_write);
            }
        }

        end_found = false;
        memset(buffer,0,BUFSIZE);
        buff_pos = 0;
    }
    int spaces = 0;
    for(size_t i = 0;i < buff_pos; i++){
        if(buffer[i] == ' ') spaces++;
    }

    bool too_many_words = (spaces >= 3);
    if(too_many_words){
        c_final -= buff_pos;
    }else{
        for(size_t i = 0;i < buff_pos;i++){
            writec(file,buffer[i],&seek_write);
        }
    }
    fclose(file);
    truncate(filename,c_final);
    return 0;
}
