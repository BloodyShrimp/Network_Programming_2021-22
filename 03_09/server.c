#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int socket_fd;
    int port = atoi(argv[1]);
    struct sockaddr_in server_address;
    char message[] = "Hello, world!\r\n";

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created...\n");
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) != 0)
    {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded...\n");
    }

    if ((listen(socket_fd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening...\n");
    }

    while(1)
    {
        int client_fd = accept(socket_fd, 0, 0);
        if (client_fd == -1)
        {
            printf("Server accept failed...\n");
            exit(0);
        }
        else
        {
            printf("Server accepted the client...\n");
        }

        write(client_fd, message, sizeof(message));
        if (close(client_fd) == -1)
        {
            printf("Connection closing failed...\n");
        }
        else
        {
            printf("Connection closed successfully...\n");
        }
    }
}