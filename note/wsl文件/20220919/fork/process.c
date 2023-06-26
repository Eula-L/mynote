#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>

int main()
{
    pid_t pid;
    int i = 0;
    for(;i < 3;i++)
    {
        fork();
        sleep(10);
    }
    return 0;
}