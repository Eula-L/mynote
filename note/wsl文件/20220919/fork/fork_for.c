#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid > 0)
    {
        printf("父进程%d\n",getpid());
    }
    else if (pid == 0)
    {
        printf("子进程%d\n",getpid());
        exit(0);
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
    printf("xxxxxxxx%d\n",getpid());
    return 0;
}
