#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
    pid_t pid;
    pid=fork();
    if(pid>0)
    {
        //这是父进程
        printf("parent....\n");
        while(1)
        {
            sleep(1);
        }

    }
    else if(pid==0)
    {
        //这是子进程
        printf("child....\n");
        while(1)
        {
            sleep(1);
        }
    }
    else 
    {
        printf("error\n");
    }
    return 0;
}
