#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

#define MSG "HI"

int main()
{
    pid_t pid;
    int fds[2];

    pipe(fds);
    pid = fork();
    // 父进程写，子进程读
    if (pid > 0)
    {

        close(fds[0]); // 父进程关闭读功能，文件描述符-1
        printf("parent pid %d alive..\n", getpid());
        sleep(5);
        write(fds[1], MSG, strlen(MSG)); // 父进程写入信息
        printf("parent pid %d send msg success..\n", getpid());
        close(fds[1]); // 父进程使用完成写的功能，关闭写功能，文件描述符-1
    }
    else if (pid == 0)
    {
        close(fds[1]); // 子进程关闭写功能，文件描述符-1
        char buffer[1024];
        bzero(buffer, sizeof(buffer));
        read(fds[0], buffer, sizeof(buffer)); // 子进程读管道中的内容

        printf("child read msg %s \n", buffer);
        close(fds[0]); // 子进程使用完成读的功能，关闭写功能，文件描述符-
        exit(0);
    }
    else
    {
        perror("FORK CALL FAILED");
        exit(0);
    }
}