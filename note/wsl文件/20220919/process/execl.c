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
        printf("parent pid = %d\n",getpid());
    }
    else if(pid == 0)
    {
        printf("child pid = %d\n",getpid());
        execl("/usr/bin/tree","tree",NULL);
        printf("child ok");
        exit(0);
    }
    else {
        printf("error");
        exit(0); 
    }
    return 0;
}
