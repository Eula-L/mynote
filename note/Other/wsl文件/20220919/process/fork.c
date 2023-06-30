#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
    pid_t pid;
    printf("父进程");
    printf("\n");

    pid = fork();
    if(pid>0)
    {
        printf("parent pid = %d\n",getpid());
        while(1)
        {
            sleep(1);
        }
    }
    else if(pid==0)
    {
        while(1)
        {
            sleep(1);
        }
        
    }
    pid = fork();
    if(pid>0)
    {
        printf("parent pid = %d\n",getpid());
        while(1)
        {
            sleep(1);
        }
    }
    else if(pid==0)
    {
        while(1)
        {
            sleep(1);
        }
        
    }
    pid = fork();
    if(pid>0)
    {
        printf("parent pid = %d\n",getpid());
        while(1)
        {
            sleep(1);
        }
    }
    else if(pid==0)
    {
        while(1)
        {
            sleep(1);
        }
        
    }
    pid = fork();
    if(pid>0)
    {
        printf("parent pid = %d\n",getpid());
        while(1)
        {
            sleep(1);
        }
    }
    else if(pid==0)
    {
        while(1)
        {
            sleep(1);
        }
        
    }
    //printf("fork后进程\n");
    return 0;
}

