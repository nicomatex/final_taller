/*
9) Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes de texto delimitados por corchetes angulares (“<...>”) y los imprima completos por
pantalla. Al recibir un paquete vacío (“<>”) debe cerrarse ordenadamente. No considere
errores.
*/

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define CLIENT_QUEUE 1
#define BUFSIZE 1024

int main(int argc, char* argv[]){
    char* port = argv[1];

    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //Socket TCP
    hints.ai_flags = AI_PASSIVE; //Server

    struct addrinfo* results;
    getaddrinfo("localhost",port,&hints,&results);

    int acceptor = socket(results->ai_family,results->ai_socktype,results->ai_protocol);

    //Solo para pruebas
    int val = 1;
    setsockopt(acceptor,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
    //-----


    bind(acceptor,results->ai_addr,results->ai_addrlen);
    
    listen(acceptor,CLIENT_QUEUE);

    int peer = accept(acceptor,NULL,NULL);

    char buffer[BUFSIZE];
    char package[BUFSIZE];

    size_t bytes_received;
    size_t package_i = 0;
    bool done = false;

    while(!done){
        bytes_received = recv(peer,buffer,BUFSIZE,0);
        for(size_t i = 0; i< bytes_received; i++){
            package[package_i] = buffer[i];
            if(package[package_i] == '>'){
                package[package_i+1] = '\0';
                if(strcmp("<>",package) == 0){
                    done = true;
                }else{
                    printf("%s\n",package);
                    i++;  //Para esquivar el salto de linea
                }
                package_i = 0;
            }else{
                package_i++;
            }
        }
    }
    shutdown(peer,SHUT_RDWR);
    shutdown(acceptor,SHUT_RDWR);
    close(peer);
    close(acceptor);
    freeaddrinfo(results);
    return 0;
}