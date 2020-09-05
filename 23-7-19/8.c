/*
8) Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes de la forma [nnn+nn+....+nnnn] (numeros separados por +, encerrados entre
corchetes) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un
paquete vacío (“[]”) debe cerrarse ordenadamente. No considere errores.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CLIENT_QUEUE 1
#define BUFSIZE 256

int get_package_sum(char* buffer){
    int sum = 0;
    char* num = strtok(buffer,"+");

    while(num){
        sum += atoi(num);
        // sum += ntohl()
        num = strtok(NULL,"+");
    }
    return sum;
}

int main(int argc, char* argv[]){
    char* ip = argv[1];
    char* port = argv[2];
    
    char buffer[BUFSIZE];
    char package[BUFSIZE];

    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    struct addrinfo* results;
    getaddrinfo(ip,port,&hints,&results);

    int acceptor_socket = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
    int val = 1;
    setsockopt(acceptor_socket,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
    bind(acceptor_socket,results->ai_addr,results->ai_addrlen);
    listen(acceptor_socket,CLIENT_QUEUE);
    int peer = accept(acceptor_socket,NULL,NULL);

    ssize_t bytes_received = 0;
    size_t package_i = 0;
    bool done = false;

    while(!done){
        bytes_received = recv(peer,buffer,BUFSIZE,0);
        for(size_t i = 0; i < bytes_received ;i++){
            package[package_i] = buffer[i];
            if(package[package_i] == ']' || package[package_i] == '\n'){
                package[package_i+1] = '\0';
                if(strcmp("[]",package) == 0){
                    done = true;
                    break;
                }
                package[i] = '\0';
                int sum = get_package_sum(&package[1]);
                printf("%d\n",sum);
                package_i = 0;
                i++; //Esquivo el salto de linea.
            }else{
                package_i++;
            }
        }
    }

    shutdown(peer,SHUT_RDWR);
    shutdown(acceptor_socket,SHUT_RDWR);
    close(peer);
    close(acceptor_socket);
    freeaddrinfo(results);
    return 0;
}
