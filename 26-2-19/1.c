#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CLIENT_QUEUE 1
#define MAX_PACKAGE 1024

/* 
Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe aceptar
una única conexión y recibir paquetes (cada paquete inicia con [ y finaliza con ]). Para cada paquete
recibido debe imprimir el checksum (sumatoria de bytes del paquete) del mismo, excepto que el paquete
esté vacío ([]), en cuyo caso debe finalizar.
*/

int main(int argc, char* argv[]){
    char* host = argv[1];
    char* port = argv[2];

    struct addrinfo hints;
    struct addrinfo* results;
    memset(&hints,0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; //Protocolo IPV4
    hints.ai_socktype = SOCK_STREAM; //Socket TCP
    hints.ai_flags = AI_PASSIVE; //Server

    if( getaddrinfo(host,port,&hints,&results) != 0){
        fprintf(stderr,"Error getting address info\n");
        return -1;
    }

    int acceptor_socket = socket(results->ai_family,results->ai_socktype,results->ai_protocol);

    int val = 1;
    int r;

    if ((r = setsockopt(acceptor_socket,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))) < 0){
        freeaddrinfo(results);
        return -1;
    }

    if ((r = bind(acceptor_socket,results->ai_addr,results->ai_addrlen)) < 0){
        freeaddrinfo(results);
        return -2;
    }

    if ((r = listen(acceptor_socket,MAX_CLIENT_QUEUE)) < 0){
        freeaddrinfo(results);
        return -3;
    }

    int peer = accept(acceptor_socket,NULL,NULL);

    char buffer[MAX_PACKAGE] = {0};
    char package[MAX_PACKAGE + 1] = {0};

    size_t bytes_received = 0;
    size_t package_i = 0;

    bool done = false;
    while(!done){
        bytes_received = recv(peer,buffer,MAX_PACKAGE,0);
        for(size_t i = 0; i < bytes_received; i++){
            package[package_i] = buffer[i];
            if(buffer[i] == ']'){
                package[package_i+1] = '\0';
                printf("Received %s\n",package);
                if(strcmp(package,"[]") == 0){
                    done = true;
                    break;
                }else{
                    int checksum = 0;
                    size_t package_long = strlen(package);
                    for(size_t j = 1;j < package_long-1;j++){
                        checksum += package[j];
                    }
                    printf("Checksum is %d\n",checksum);
                    package_i = 0;
                }
            }else{
                package_i++;
            }
        }
    }
    shutdown(peer,SHUT_RDWR);
    shutdown(acceptor_socket,SHUT_RDWR);
    close(acceptor_socket);
    close(peer);
    freeaddrinfo(results);
    return 0;
}
