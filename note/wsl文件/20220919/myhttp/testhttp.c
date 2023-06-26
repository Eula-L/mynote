#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define HTTP_PORT 80
// 发送HTTP请求
int send_http_request(char *host, char *path, char *method, char *data, char *headers)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[1024];
    char request[2048];
    portno = HTTP_PORT;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        return -1;
    }

    server = gethostbyname(host);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        return -1;
    }
    if (strcmp(method, "GET") == 0)
    {
        sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\n%s\r\n\r\n", path, host, headers);
    }
    else if (strcmp(method, "POST") == 0)
    {
        sprintf(request, "POST %s HTTP/1.1\r\nHost: %s\r\n%s\r\nContent-Length: %d\r\n\r\n%s", path, host, headers, strlen(data), data);
    }
    else
    {
        return -1;
    }
    n = write(sockfd, request, strlen(request));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));
    while (read(sockfd, buffer, sizeof(buffer) - 1) > 0)
    {
        printf("%s", buffer);
        int i = 0;
        // while (buffer[i] != '\0')
        // {
        //     if((buffer[i]>'a'&&buffer[i]<'z')||(buffer[i]>'A'&&buffer[i]<'Z'))
        //     {

        //     }
        //     else
        //     {
        //         printf("%c",buffer[i]);
        //     }
        //     i++;
        // }
        memset(buffer, 0, sizeof(buffer));
    }
    close(sockfd);
    return 0;
}
int main()
{
    char *host = "www.baidu.com";
    char *path = "/";
    char *method = "GET";
    char *data = "";
    char *headers = "";
    send_http_request(host, path, method, data, headers);
    return 0;
}