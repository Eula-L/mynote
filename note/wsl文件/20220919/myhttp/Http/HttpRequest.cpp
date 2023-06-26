#include "HttpRequest.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
 
HttpRequest::HttpRequest(unsigned int port, unsigned int timeout) {
    this->sockfd = 0;
    this->port = port;
    this->timeout = timeout;
}
 
int HttpRequest::get(char *content, const char *host, const char *uri, const char *ip) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // sprintf(content, "sockfd=%d\n", sockfd);
    int ret = 0;
    struct sockaddr_in addr{};
    socklen_t addrlen;
 
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
    addr.sin_addr.s_addr = inet_addr(ip);
    addrlen = sizeof(addr);
    ret = connect(sockfd, (struct sockaddr *)(&addr), addrlen);
    if (ret != 0) {
        close(sockfd);
        return errno;
        // delete this;
    }
 
    char buf[BUFSIZ] = {'\0'};
    size_t n = 0;
    sprintf(buf, "GET %s HTTP/1.0\r\n", uri);
    n = strlen(buf);
    write(sockfd, buf, n);
    memset(buf, 0, n+1);
 
    sprintf(buf, "Host: %s\r\n", host);
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, BUFSIZ);
 
    strcpy(buf, "Content-Type: text/html\r\n");
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, BUFSIZ);
    // strcpy(buf, "Accept: */*\r\n");
    write(sockfd, "\r\n\r\n", 4);
 
    const size_t MAX_PAGE_SIZE = 65535;
    memset(content, 0, MAX_PAGE_SIZE);
    readn(sockfd, content, MAX_PAGE_SIZE);
    close(sockfd);
    sockfd = 0;
    return errno;
}
 
ssize_t HttpRequest::readn(int fd, void *vptr, size_t n) {
    size_t nleft;
    ssize_t nread;
    char *ptr;
 
    ptr = static_cast<char *>(vptr);
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) {
                nread = 0; /* and call read() again */
            } else {
               return -1;
            }
        } else if (nread == 0) {
            break;  /* EOF */
        } else {}
        nleft -= nread;
        ptr += nread;
    }
    return (ssize_t)(n-nleft);
}
 
HttpRequest::~HttpRequest() {
    if (this->sockfd != 0) {
        close(this->sockfd);
        this->sockfd = 0;
    }
}
 
int HttpRequest::post(char *content, const char *host, const char *uri, const char *ip, const char *data) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // sprintf(content, "sockfd=%d\n", sockfd);
    int ret = 0;
    struct sockaddr_in addr{};
    socklen_t addrlen;
 
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
    addr.sin_addr.s_addr = inet_addr(ip);
    addrlen = sizeof(addr);
    ret = connect(sockfd, (struct sockaddr *)(&addr), addrlen);
    if (ret != 0) {
        close(sockfd);
        return errno;
    }
    // sprintf(content, "connect return=%d\n", ret); return 0;
 
    char buf[BUFSIZ] = {'\0'};
    size_t n = 0;
    sprintf(buf, "POST %s HTTP/1.0\r\n", uri);
    n = strlen(buf);
    write(sockfd, buf, n);
    memset(buf, 0, n+1);
 
    sprintf(buf, "Host: %s\r\n", host);
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, BUFSIZ);
 
    sprintf(buf, "UserAgent: Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1\r\n");
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, BUFSIZ);
 
    strcpy(buf, "Content-Type: application/x-www-form-urlencoded\r\n");
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, 64);
 
    size_t len = strlen(data);
    sprintf(buf, "Content-Length: %lu\r\n", len);
    write(sockfd, buf, strlen(buf));
    memset(buf, 0, BUFSIZ);
    write(sockfd, "\r\n", 2);  // header body separator
 
    write(sockfd, data, len);  // post body
    write(sockfd, "\r\n\r\n", 4);
 
    ssize_t bytesRead;
    char *p = content;
    int i;
    do {
        memset(buf, 0, 4096);
        // bytesRead = readn(sockfd, buf, 4096);
        bytesRead = read(sockfd, buf, 4096);
        for (i = 0; i < bytesRead; i++) {
            *p = buf[i];
            p++;
        }
        *p = '\0';
    } while (bytesRead > 0);
    return errno;
}
