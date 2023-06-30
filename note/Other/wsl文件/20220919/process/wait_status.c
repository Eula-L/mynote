#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>


int main ()
{
    pid_t pid;
    int i=0;
    for(i;i<2;i++)
    {
        pid=fork();
        if(pid==0)
        {
            break;
        }
    }
    if(pid>0)
    {
        printf("parent waitpid..\n");
        pid_t zpid;
        int status;
        while ((zpid=waitpid(-1,&status,WNOHANG))!=-1)
        {
            if(zpid)
            {
                if(WIFEXITED(status))
                {
                    printf("wait success, zpid %d, exit or return, %d \n",zpid,WEXITSTATUS(status));
                    
                }
                if(WIFSIGNALED(status))
                {
                    printf("wait success, zpid %d, child process killed, signo %d \n",zpid,WTERMSIG(status));
                }
            }
        }
        
    }
    else if(pid==0)
    {
        if(i==0)
        {
            while(1)
            {
                printf("Child %d pid %d, Runing..\n",i,getpid());
                sleep(5);
            }
        }
        else if(i==1)
        {
            printf("Child %d pid %d, exit..\n",i,getpid());
            exit(16);
        }
    }
    else
    {
        perror("FORK FAILED");
    }
}