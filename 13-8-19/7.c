#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void read_number(FILE* file, char* buffer, long* seek, size_t number_size, bool backwards){
    fseek(file,*seek,SEEK_SET);
    fread(buffer,sizeof(char),number_size,file);
    buffer[number_size] = '\0';
    if(backwards){
        *seek -= number_size;
    }else{
        *seek += number_size; 
    }
}

void write_number(FILE* file, char* buffer, long* seek, size_t number_size, bool backwards){
    fseek(file,*seek,SEEK_SET);
    fwrite(buffer,sizeof(char),number_size,file);
    if(backwards){
        *seek -= number_size;
    }else{
        *seek += number_size; 
    }
}


int main(int argc, char* argv[]){
    char* filename = argv[1];
    FILE* file = fopen(filename,"r+");

    long seek_write = 0;
    long seek_read = 0;

    fseek(file,0,SEEK_END);
    long file_size = ftell(file);

    long number_count = file_size / 4;

    size_t final_size = number_count * 5;

    seek_read = file_size - 4;
    
    ftruncate(fileno(file),final_size);

    seek_write = final_size - 5;

    char read_buffer[5];
    char write_buffer[5];

    while(seek_read >= 0){
        read_number(file,read_buffer,&seek_read,4,true);
        long number = strtol(read_buffer,NULL,16);
        fseek(file,seek_write,SEEK_SET);
        fprintf(file,"%05li",number);
        seek_write -= 5;
    }

    fclose(file);
    return 0;
}
