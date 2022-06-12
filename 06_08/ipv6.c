#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#define DGRAM_SIZE 65507

int main()
{
    printf("%lu\n", ULONG_MAX);
    struct sockaddr_in6 serv_addr; //!!
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6; //!!
    serv_addr.sin6_port = htons(2020); //!!
    serv_addr.sin6_addr = in6addr_any; //!!

    int socket_fd = socket(AF_INET6, SOCK_DGRAM, 0); //!!
    if (socket_fd == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created...\n");
    }

    if ((bind(socket_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))) == -1)
    {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded...\n");
    }

    while (1)
    {
        struct sockaddr_in6 client_addr; //!!
        memset(&client_addr, 0, sizeof(client_addr));
        socklen_t client_addr_size = sizeof(client_addr);

        char buffer[DGRAM_SIZE];
        char read_number[DGRAM_SIZE];
        int digit_count = 0;
        int number_count = 0;
        unsigned long int sum = 0;
        unsigned long int prev_sum = 0;
        unsigned long int current_number = 0;
        bool is_netcat_used = false;
        bool error_occured = false;
        ssize_t read_bytes = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_size);

        if (read_bytes == -1)
        {
            printf("Receiving datagram failed...\n");
            exit(0);
        }
        else if (read_bytes == 0)
        {
            printf("Received empty datagram...\n");
            error_occured = true;
        }
        printf("Read bytes: %ld\n", read_bytes);

        for (int i = 0; i <= read_bytes; i++)
        {
            if (buffer[i] == '\n' || (buffer[i] == '\r' && buffer[i + 1] == '\n'))
            {
                printf("Detected netcat\n");
                is_netcat_used = true;
            }
            if (buffer[i] == ' ' || i == read_bytes || (is_netcat_used && i == read_bytes - 2))
            {
                printf("Read space or end of datagram\n");
                read_number[digit_count] = '\0';
                prev_sum = sum;
                errno = 0;
                current_number = strtoul(read_number, 0, 10);
                if (errno == ERANGE)
                {
                    printf("Read number is too big...\n");
                    error_occured = true;
                    break;
                }
                sum += current_number;
                digit_count = 0;
                if (sum < prev_sum)
                {
                    printf("Overflow occured...\n");
                    error_occured = true;
                    break;
                }
            }
            else if (buffer[i] >= '0' && buffer[i] <= '9')
            {
                printf("Read digit\n");
                read_number[digit_count] = buffer[i];
                digit_count++;
                number_count++;
            }
            else if (buffer[i] != '\n' && (buffer[i] != '\r' && buffer[i + 1] != '\n'))
            {
                printf("Invalid character\n");
                error_occured = true;
                break;
            }
        }

        if (number_count == 0)
        {
            printf("No numbers were read...\n");
            error_occured = true;
        }

        if (error_occured)
        {
            if (is_netcat_used)
            {
                if (sendto(socket_fd, "ERROR\n", 6, 0, (const struct sockaddr *)&client_addr, client_addr_size) == -1)
                {
                    printf("Sending datagram failed...\n");
                    exit(0);
                }
            }
            else
            {
                if (sendto(socket_fd, "ERROR", 5, 0, (const struct sockaddr *)&client_addr, client_addr_size) == -1)
                {
                    printf("Sending datagram failed...\n");
                    exit(0);
                }
            }
        }
        else
        {
            int message_len = 0;
            if (is_netcat_used)
            {
                message_len = sprintf(read_number, "%lu\r\n", sum);
            }
            else
            {
                message_len = sprintf(read_number, "%lu", sum);
            }

            if (sendto(socket_fd, read_number, message_len, 0, (const struct sockaddr *)&client_addr, client_addr_size) == -1)
            {
                printf("Sending datagram failed...\n");
                exit(0);
            }
            printf("Sum = %lu\n", sum);
            printf("Sent number %s\n", read_number);
        }
    }
}