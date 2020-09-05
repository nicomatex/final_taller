/*
9) Escriba una función ISO C que permita procesar un archivo texto que contenga frases (1
por línea) sobre sí mismo, sin generar archivos intermedios ni cargar el archivo completo a
memoria. El procesamiento consiste en eliminar las palabras de más de 3 letras de cada línea.
*/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 256
#define MAXLONG 3

int read_c(FILE* file, long int* seek){
    fseek(file,*seek,SEEK_SET);
    int c = fgetc(file);
    *seek = ftell(file);
    return c;
}

void write_c(FILE* file,int c, long int* seek){
    fseek(file,*seek,SEEK_SET);
    fputc(c,file);
    *seek = ftell(file);
}

int main(int argc, char* argv[]){
    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");

    char buffer[BUFSIZE] = {0};

    int c;
    long int read_seek = 0;
    long int write_seek = 0;
    size_t word_size = 0;

    size_t final_size = 0;
    while((c = read_c(file,&read_seek)) != EOF){
        buffer[word_size++] = c;
        final_size++;
        if(c == ' ' || c == '\n'){
            if(word_size > (MAXLONG + 1)){
                final_size -= word_size;
            }else{
                for(size_t i = 0;i < word_size;i++){
                    write_c(file,buffer[i],&write_seek);
                }
            }
            word_size = 0;
        }
    }
    fclose(file);
    truncate(filename,sizeof(char)*final_size);
    return 0;
}
