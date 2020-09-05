#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

bool read_number(FILE* file, long *seek, uint16_t* number, bool backwards){
    fseek(file,*seek,SEEK_SET);
    size_t r = fread(number,sizeof(uint16_t),1,file);
    if(backwards){
        (*seek)-= sizeof(uint16_t);
    }else{
        *seek = ftell(file);
    }
    return r == 0;
}

void write_number(FILE* file, long *seek, uint16_t number, bool backwards){
    fseek(file,*seek,SEEK_SET);
    fwrite(&number,sizeof(uint16_t),1,file);
    if(backwards){
        (*seek)-= sizeof(uint16_t);
    }else{
        *seek = ftell(file);
    }
}


int main(int argc, char* argv[]){
    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");

    long seek_write = 0;
    long seek_read = 0;
    bool eof = false;
    uint16_t number;
    size_t final_size = 0;

    while(!(eof = read_number(file,&seek_read,&number,false))){
        final_size += sizeof(uint16_t);
        if(number % 3 == 0) final_size += sizeof(uint16_t);
    }

    ftruncate(fileno(file),final_size);
    seek_write = final_size - sizeof(uint16_t); //Posicionamos el cursor de escritura al final.
    seek_read -= 2; //Posicionamos el cursor de lectura en el ultimo elemento.

    while(seek_read > 0){
        read_number(file,&seek_read,&number,true);
        write_number(file,&seek_write,number,true);
        if(number % 3 == 0) write_number(file,&seek_write,number,true);
    }

    fclose(file);
    return 0;
}
    