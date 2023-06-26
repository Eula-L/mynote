
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
    int i=0;
    pid_t pid;
    for(i=0;i<5;i++)
    {
        pid=fork();
        if(pid==0)
            break;
    }
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
        if(i==0)
        {
            printf("id = %d , pid = %d \n",i,getpid());
        }
        else if(i==1)
        {
            printf("id = %d , pid = %d \n",i,getpid());
        }
        else if(i==2)
        {
            printf("id = %d , pid = %d \n",i,getpid());
        }
        else if(i==3)
        {
            printf("id = %d , pid = %d \n",i,getpid());
        }
        while(1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("erroe\n");
        exit(0);
    }
    return 0;
}
