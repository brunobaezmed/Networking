/*
 * @Author: Bruno Baez Medina
 * @Date: 2023-03-18 11:21:27
 * @Last Modified by:   Bruno Baez Medina
 * @Last Modified time: 2023-03-18 11:21:27
 */
#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void launch(struct Server *server)
{

    char dia[15];
    Dia_Semana(dia);
    char *buffer = calloc(30000, sizeof(char));
    printf("====Esperando conexion ===\n");

    int addr_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addr_length);
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);
    char mensaje[220] = "HTTP/1.1 200 OK\nDate:";
    
    strcat(mensaje,dia);

    char *m2 = " GMT\nServer: BR-SERVER {Win32}\nLast-Modified:Wed,22 Jul 2009 19:15 GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n<html><body><h1>Bruno</h1><body></hmtl>";
    strcat(mensaje,m2);
    write(new_socket, mensaje, strlen(mensaje));
    close(new_socket);
    free(buffer);
}

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);

    server.launch(&server);
}
