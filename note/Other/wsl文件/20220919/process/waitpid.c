#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

void job()
{
    printf("Parent myJob Once..\n");
}
int main()
{
    pid_t pid;
    int i=0;
    for(i;i<5;i++)
    {
        pid=fork();
        if(pid==0)
        {
            break;
        }
    }
    if(pid>0)
    {
        pid_t zpid;
        while((zpid=waitpid(-1,NULL,WNOHANG))!=-1)
        {
            if(zpid>0) 
            {
                printf("Parent wait zombie sucess, zpid=%d\n",zpid);
            }
            else if (zpid==0){
                job(); 
            }
            sleep(1);
        }
    }
    else if(pid==0)
    {
        printf("child pid id %d\n",getpid());
        sleep(i*5); 
        exit(i*5);
    }
    else {
        perror("FORK CALL FAILED");
        exit(0);
    }
    while (1)
    {
        /* code */
        sleep(1);
    }
    
    
}
