#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define CLIENT_QUEUE 1
#define BUFF_LEN 256


int main(int argc, char* argv[]){
    char* ip = argv[1];
    char* port = argv[2];
    char buffer[BUFF_LEN];
    char exit_ward[] = "FIN";

    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    struct addrinfo* results;
    getaddrinfo(ip,port,&hints,&results);

    int acceptor = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
    int val = 1;
    setsockopt(acceptor, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bind(acceptor,results->ai_addr,results->ai_addrlen);
    listen(acceptor,CLIENT_QUEUE);

    int peer = accept(acceptor,NULL,NULL);

    size_t received = 0;
    bool alive = true;

    while(alive){
        received = recv(peer,buffer,sizeof(buffer),0);
        buffer[received] = '\0';
        if(strncmp(exit_ward,buffer,strlen(exit_ward)) == 0){
            alive = false;
        }else{
            printf("%s",buffer);
        }
    }
    shutdown(peer,SHUT_RDWR);
    shutdown(acceptor,SHUT_RDWR);
    close(peer);
    close(acceptor);
    return 0;
}