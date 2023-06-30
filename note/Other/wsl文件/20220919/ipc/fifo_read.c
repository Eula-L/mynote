#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main ()
{
    char buf[1500];
    bzero(buf,sizeof(buf));
    int fd = open("myfifo",O_RDONLY);

    read(fd,buf,sizeof(buf));
    printf("fifo read msg %s\n",buf);
    close(fd);
    return 0;
}
