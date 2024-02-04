#include <asm-generic/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#define     EXIT_SUCCESS    0
#define     EXIT_ERROR      1

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        fprintf(stderr, "ERROR: Failed to create server socket.\n");
        exit(EXIT_ERROR);
    }
    
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htonl(4221),
        .sin_addr = htonl(INADDR_ANY)
    };
    
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "ERROR: Faild to bind (assign) server to address.\n");
        exit(EXIT_ERROR);
    }

    if (listen(server_fd, 4096) == -1) {
        fprintf (stderr, "ERROR: Server faild in passive connect.\n");
        exit(EXIT_ERROR);
    }

    printf("Waiting for client to connect...\n");
    
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    if (accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len) == -1) {
        fprintf(stderr, "ERROR: Coudlent accept the connection.\n");
    }
    else printf("Client Connected.\n");

    if (close(server_fd) == -1) {
        fprintf(stderr, "ERROR: Server didint close properly.");
        exit(EXIT_ERROR);
    }    

    return EXIT_SUCCESS;
}
