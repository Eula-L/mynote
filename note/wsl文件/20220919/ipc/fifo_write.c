#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG "123aabbcc"

int main ()
{
    int fd = open("myfifo",O_WRONLY);
    printf("aaaa\n");

    write(fd,MSG,strlen(MSG));
    printf("write success\n");
    close(fd);
    return 0;
}
