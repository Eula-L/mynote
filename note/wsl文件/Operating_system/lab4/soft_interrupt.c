#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
void stop(int);
int main()
{
    int pid1, pid2;
    signal(SIGALRM, stop); // signal(14,stop); SIGALRM 14
    while ((pid1 = fork()) == -1)
        ;
    if (pid1 > 0)
    {
        while ((pid2 = fork()) == -1);
        if (pid2 > 0)
        {
            alarm(1);
            sleep(1);
            kill(pid1, 16); // SIGUSR1
            kill(pid2, 17); // SIGUSR2
            wait(0);
            wait(0);
            printf("Parent process is killed !!\n");
            exit(0);
        }
        else
        {
            signal(17, stop);
            sleep(2);
            printf("Child process 2 is killed by parent !!\n");
            exit(0);
        }
    }
    else
    {
        signal(16, stop);
        sleep(2);
        printf("Child process 1 is killed by parent !!\n");
        exit(0);
    }
}
void stop(int a)
{
    printf("Here is stop function!! Signal number is %d\n", a);
}
