#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 1024

int readc(FILE* file,long int *seek){
    fseek(file,*seek,SEEK_SET);
    int c = fgetc(file);
    *seek = ftell(file);
    return c;
}

void writec(FILE* file, char c, long int *seek){
    fseek(file,*seek,SEEK_SET);
    fputc(c,file);
    *seek = ftell(file);
}

int main(int argc, char* argv[]){
    char* filename = argv[1];

    long int write_seek = 0;
    long int read_seek = 0;

    FILE* file = fopen(filename,"r+");

    int c;
    char buffer[BUFSIZE];
    memset(buffer,0,sizeof(buffer));
    size_t buff_i = 0;

    size_t final_size = 0;

    while((c = readc(file,&read_seek)) != EOF){
        final_size++;
        buffer[buff_i] = c;

        if(c != '\n'){
            buff_i++;
            continue;
        }

        size_t words = 1;
        for(size_t i = 0; i < buff_i; i++){
            if(buffer[i] == ' ') words++;
        }

        if(words == 1){
            final_size -= buff_i + 1;
        }else{
            for(size_t i =0; i <= buff_i; i++){
                writec(file,buffer[i],&write_seek);
            }
        }
        buff_i = 0;
        memset(buffer,0,sizeof(buffer));
    }

    fclose(file);
    truncate(filename,sizeof(char) * final_size);
    return 0;
}