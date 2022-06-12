#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <arpa/inet.h>

#define B_SIZE 20

bool drukowalne_array(const char * buf)
{
    int i = 0;
    while(buf[i] != '\0')
    {
        if (buf[i] < 32 || buf[i] > 126)
        {
            if(buf[i] != 13 && buf[i] != 10)
            {
                return false;
            }
        }
        i++;
    }

    return true;
}

int main(int argc, const char *argv[])
{
    int socket_fd;
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_address;
    char message[B_SIZE] = "";

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
    server_address.sin_addr.s_addr = inet_addr(ip);

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("Connection failed...\n");
        exit(0);
    }
    else
    {
        printf("Connection successful...\n");
    }

    int read_bytes = 0;
    read_bytes = read(socket_fd, message, B_SIZE);
    if(read_bytes == -1)
    {
        printf("Read error...\n");
        exit(0);
    }

    if (drukowalne_array(message))
    {
        printf("%s", message);
    }
    else
    {
        printf("Invalid message...\n");
        printf("%s", message);
    }

    if (close(socket_fd) == -1)
        {
            printf("Connection closing failed...\n");
        }
        else
        {
            printf("Connection closed successfully...\n");
        }

}