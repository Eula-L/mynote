#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int main ()
{
    pid_t pid ,zpid;
    pid = fork();
    if(pid>0)
    {
        printf("父进程 pid = %d 运行中\n",getpid());
        while(1)
        {
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        printf("子进程 pid = %d 运行中\n",getpid());
        sleep(10);
        printf("子进程结束\n");
        exit(0);
    }
    else
    {
        perror("fork error");
        exit(0);
    }
    return 0;
}
