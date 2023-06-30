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
        while (1)
        {
            /* code */
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        printf("子进程%d\n",getpid());
        while (1)
        {
            /* code */
            sleep(1);
        }
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
    return 0;
}
