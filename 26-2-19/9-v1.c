/*
9) Escribir un programa ISO C que procese el archivo de texto cuyo nombre es recibido como
parámetro. El procesamiento consiste en leer oraciones y suprimir aquellas que tengan
más de 3 palabras. Asuma que el archivo no puede cargarse en memoria, pero una oración
sí puede.
*/

#include <stdio.h>
#include <string.h>

#define BUFFSIZE 256

size_t word_count(const char* sentence){
    size_t i = 0;
    size_t word_count = 1;

    while(sentence[i]){
        if(sentence[i++] == ' ') word_count++;
    }
    return word_count;
}



int main(int argc, char* argv[]){
    char* filename = argv[1];
    
    char buffer[BUFFSIZE];
    char sentence_buffer[BUFFSIZE];

    FILE* file = fopen(filename,"r");
    FILE* out_file = fopen("temp","w");
    
    size_t bytes_read;
    size_t buffer_i = 0;
    size_t sentence_i = 0;

    while((bytes_read = fread(buffer,sizeof(char),sizeof(buffer),file)) > 0){
        for(buffer_i = 0;buffer_i < bytes_read;buffer_i++){
            sentence_buffer[sentence_i] = buffer[buffer_i];
            if(sentence_buffer[sentence_i] == '.'){
                sentence_buffer[sentence_i+1] = '\0';
                if(word_count(sentence_buffer) <= 3){
                    fwrite(sentence_buffer,sizeof(char),strlen(sentence_buffer),out_file);
                }
                sentence_i = 0;
            }else{
                sentence_i++;
            }
        }
    }
    fclose(file);
    fclose(out_file);
    remove(filename);
    rename("temp",filename);
    return 0;
}