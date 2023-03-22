/*
 * @Author: Bruno Baez Medina 
 * @Date: 2023-03-18 11:21:16 
 * @Last Modified by:   Bruno Baez Medina 
 * @Last Modified time: 2023-03-18 11:21:16 
 */

//creando la libreria del servidor

#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <bits/types.h>
enum dia{
 Sun,Mon,Tue,Wed,Thu,Fri,Sat
};

void Dia_Semana(char *);
char *itoa(int , int);
struct Server{
    int domain;
    int protocol;
    int service;
    u_long interface;
    int port;
    int backlog;
    int socket;

    struct sockaddr_in address;

    void (*launch) (struct Server *server);
};
struct Server server_constructor(int domain,int service,int protocol,u_long interface,int port ,int backlog ,void(*launch)(struct Server *server));


















#endif













