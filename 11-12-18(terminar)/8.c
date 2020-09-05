/*
8) Escribir un programa ISO C que procese el archivo “valuesword.dat” sobre sí mismo,
eliminando los words (2 bytes) múltiplos de 16.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

bool read_number(FILE* file, long* seek,uint16_t* number_store){
    fseek(file,*seek,SEEK_SET);
    size_t read = fread(number_store,sizeof(uint16_t),1,file);
    *seek = ftell(file);
    return read != 0;
}


void write_number(FILE* file, long* seek, uint16_t number){
    fseek(file,*seek, SEEK_SET);
    fwrite(&number,sizeof(uint16_t),1,file);
    *seek = ftell(file);
}


int main(int argc, char* argv[]){

    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");
    
    long seek_write = 0;
    long seek_read = 0;

    uint16_t number;
    size_t final_size = 0;
    while(read_number(file,&seek_read,&number)){
        final_size += sizeof(uint16_t);
        if(number % 16 == 0){
            final_size -= sizeof(uint16_t);
        }else{
            write_number(file,&seek_write,number);
        }
    }
    ftruncate(fileno(file),final_size);
    fclose(file);
    return 0;
}