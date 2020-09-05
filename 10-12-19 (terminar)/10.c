/*
10) Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe
establecer una unica conexión, quedar en escucha e imprimir en stdout todo lo recibido. Al recibir
el texto ‘FINAL’ debe finalizar el programa sin imprimir dicho texto.
*/

#define _POSIX_C_SOURCE 200112L

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    char* ip = argv[1];
    char* port = argv[2];

    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo* results;
    getaddrinfo(ip,port,&hints,&results);

    int acceptor = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
    bind(acceptor,results->ai_addr,results->ai_addrlen);
    listen(acceptor,1);

    int peer = accept(acceptor,NULL,NULL);
    
}
