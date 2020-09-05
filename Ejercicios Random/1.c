/*
Escriba un programa ISO C que procese el archivo de texto a.txt sobre sí mismo.
El sistema debe recibir dos cadenas por línea de comando: clave y valor. El
procesamiento consiste en recorrer el archivo a.txt y reemplazar todas las
ocurrencias de clave por el contenido de valor. Ej de ejecución:
*/
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


#define BUFSIZE 1024

bool read_line(FILE* file, char* buffer, size_t buffsize, long *seek, bool backwards, size_t *start){
    fseek(file,*seek,SEEK_SET);
    char* r;
    bool eof;

    if(backwards){
        int c;
        buffer[buffsize-1] = '\0';
        buffer[buffsize-2] = '\n';
        size_t i = buffsize - 3;

        while(((c = fgetc(file)) != '\n') && (ftell(file) > 0)){
            buffer[i--] = c;
        }
        *start = (c == '\n') ? i + 1 : i;
        eof = ftell(file) == 0;
    }else{
        r = fgets(buffer,buffsize,file);
        eof = r == NULL;
    }
    *seek = ftell(file);
    return eof;
}
 
void write_line(FILE* file, char* buffer, long *seek){
    fseek(file,*seek,SEEK_SET);
    fputs(buffer,file);
    *seek = ftell(file);
}


int main(int argc, char* argv[]){
    FILE* file = fopen("a.txt","r+");

    char* token = argv[1];
    char* value = argv[2];

    int token_len = (int)strlen(token);
    int value_len = (int)strlen(value);

    long seek_read = 0;
    long seek_write = 0;
    char buffer[BUFSIZE];
    bool eof = false;
    
    int original_size = 0;
    int final_size = 0;

    size_t line_long = 0;

    while(!(eof = read_line(file,buffer,BUFSIZE,&seek_read,false,NULL))){
        line_long = strlen(buffer);
        size_t token_occurences = 0;
        char* occurence = buffer;
        while((occurence = strstr(occurence,token))){
            occurence++;
            token_occurences++;  
        } 

        original_size += line_long;
        final_size += line_long + token_occurences * (value_len - token_len);
    }

    bool truncate_bigger = (final_size > original_size);

    if(truncate_bigger) ftruncate(fileno(file),final_size);

    while(seek_read > 0){
        size_t start;
        read_line(file,buffer,BUFSIZE,&seek_read,true,&start);
    }
}
