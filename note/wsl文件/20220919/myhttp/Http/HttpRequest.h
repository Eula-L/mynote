#ifndef MYTHREAD_HTTPREQUEST_H
#define MYTHREAD_HTTPREQUEST_H
 
#ifndef ssize_t
typedef signed long ssize_t;
#endif
#ifndef size_t
typedef unsigned long size_t;
#endif
 
class HttpRequest {
public:
    explicit HttpRequest(unsigned port = 80, unsigned timeout = 30);
    int get(char *content, const char *host, const char *uri, const char *ip);
    int post(char *content, const char *host, const char *uri, const char *ip, const char *data);
    ~HttpRequest();
 
private:
    /* Read "n" bytes from a descriptor. */
    static ssize_t readn(int fd, void *vptr, size_t n);
 
    int sockfd;
    unsigned port;
    unsigned timeout;
};
 
 
#endif //MYTHREAD_HTTPREQUEST_H
