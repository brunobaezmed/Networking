/*
 * @Author: Bruno Baez Medina 
 * @Date: 2023-03-22 07:34:38 
 * @Last Modified by:   Bruno Baez Medina 
 * @Last Modified time: 2023-03-22 07:34:38 
 */

/*Compilar Server.c y test.c*/
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
/* convierte val a char* segun la base que se de*/
char *itoa(int val, int base)
{

    static char buf[32] = {0};

    int i = 30;

    for (; val && i; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i + 1];
};
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(struct Server *server))
{
    struct Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain, service, protocol);
    if (server.socket < 0)
    {
        perror("fallo al conectar al socket...\n");
        exit(1);
    }

    if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0)
    {
        perror("fallo la funcion bind..\n");
        exit(1);
    }

    if ((listen(server.socket, server.backlog)) < 0)
    {
        perror("fallo en la solicitud de escucha...\n");
        exit(1);
    }
    server.launch = launch;
    return server;
};
void Dia_Semana(char *dia_S)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int dia = tm.tm_wday;

    switch (dia)
    {
    case Sun:
        strcpy(dia_S, "Sun,");
        break;
    case Mon:
        strcpy(dia_S, "Mon,");
        break;
    case Tue:
        strcpy(dia_S, "Tue,");
        break;
    case Wed:
        strcpy(dia_S, "Wed,");
        break;
    case Thu:
        strcpy(dia_S, "Thu,");
        break;
    case Fri:
        strcpy(dia_S, "Fri,");
        break;
    case Sat:
        strcpy(dia_S, "Sat,");
        break;
    default:
        break;
    }
    // Mon,27 Jul 2009 <-----formato
    char *dia_numero = itoa(tm.tm_mday, 10);
    strcat(dia_S, dia_numero);

    switch (tm.tm_mon)
    {
    case 0:
        strcat(dia_S, " Jan ");
        break;
    case 1:
        strcat(dia_S, " Feb ");
        break;
    case 2:
        strcat(dia_S, " Mar ");

        break;
    case 3:
        strcat(dia_S, " Apr ");

        break;
    case 4:
        strcat(dia_S, " May ");

        break;
    case 5:
        strcat(dia_S, " Jun ");

        break;
    case 6:
        strcat(dia_S, " Jul ");

        break;
    case 7:
        strcat(dia_S, " Aug ");

        break;
    case 8:
        strcat(dia_S, " Sept ");

        break;

    case 9:
        strcat(dia_S, " Oct ");

        break;
    case 10:
        strcat(dia_S, " Nov ");

        break;
    case 11:
        strcat(dia_S, " Dec ");

        break;
    default:
        break;
    }
    char *anh = itoa(tm.tm_year + 1900, 10);
    strcat(dia_S, anh);
}