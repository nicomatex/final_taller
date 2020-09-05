/*
4) Escribir un programa ISO C que procese el archivo “nros_2bytes_bigendian.dat” sobre sí
mismo, eliminando los número múltiplos de 7.
*/
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
bool read_number(FILE* file, long int *seek, uint16_t *number){
    fseek(file,*seek,SEEK_SET);
    size_t r = fread(number,sizeof(uint16_t),1,file);
    *seek = ftell(file);
    *number = ntohs(*number);
    return r == 0;
}

void write_number(FILE* file, long int *seek, uint16_t number){
    fseek(file,*seek,SEEK_SET);
    number = htons(number);
    fwrite(&number,sizeof(uint16_t),1,file);
    *seek = ftell(file);
}


int main(int argc, char* argv[]){

    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");

    long int seek_write = 0;
    long int seek_read = 0;


    bool eof = false;
    uint16_t number;
    size_t final_size = 0;

    while(!(eof = read_number(file,&seek_read,&number))){
        final_size += sizeof(uint16_t);
        if(number % 7 == 0){
            final_size -= sizeof(uint16_t);
        }else{
            write_number(file,&seek_write,number);
        }
    }
    fclose(file);
    truncate(filename,final_size);
    return 0;
}
