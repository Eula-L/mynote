#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// 定义一些管道的宏，方便使用
#define READ_END 0
#define WRITE_END 1

int pid1, pid2;
int main()
{
    // 定义一个管道
    int fd[2];
    // 定义两个字符串数组，用于存储子进程发送的消息
    char OutPipe[100], InPipe[100];
    // 创建一个管道 
    pipe(fd); 
    // 创建第一个子进程
    pid1 = fork();
    if (pid1 == -1)
    { // 创建失败，打印错误信息并退出
        perror("fork");
        exit(1);
    }
    if (pid1 == 0)
    {
        // 子进程1
        // 关闭管道的读端
        close(fd[READ_END]);
        // 将消息写入字符串数组
        sprintf(OutPipe, "Child process 1 is sending message !\n");
        // 将字符串数组写入管道
        write(fd[WRITE_END], OutPipe, strlen(OutPipe) + 1);
        // 关闭管道的写端
        close(fd[WRITE_END]);
        // 睡眠五秒
        sleep(5);
        // 退出程序
        exit(0);
    }
    else
    { // 父进程 
        // 创建第二个子进程
        pid2 = fork();
        if (pid2 == -1)
        { // 创建失败，打印错误信息并退出
            perror("fork");
            exit(1);
        }
        if (pid2 == 0)
        {
            // 子进程2 
            // 关闭管道的读端
            close(fd[READ_END]);
            // 将消息写入字符串数组
            sprintf(OutPipe, "Child process 2 is sending message !\n");
            // 将字符串数组写入管道
            write(fd[WRITE_END], OutPipe, strlen(OutPipe) + 1);
            // 关闭管道的写端
            close(fd[WRITE_END]);
            // 睡眠五秒
            sleep(5);
            // 退出程序
            exit(0);
        }
        else
        {
            // 父进程 
            // 关闭管道的写端
            close(fd[WRITE_END]);
            // 等待第一个子进程结束，并获取它的状态
            int status1;
            waitpid(pid1, &status1, 0);
            // 从管道读取第一个子进程发送的消息，并打印出来
            read(fd[0],InPipe, sizeof(InPipe));
            printf("%s\n", InPipe);
            // 等待第二个子进程结束，并获取它的状态
            int status2;
            waitpid(pid2, &status2, 0);
            // 从管道读取第二个子进程发送的消息，并打印出来
            read(fd[0], InPipe, sizeof(InPipe));
            printf("%s\n", InPipe);
            // 关闭管道的读端
            close(fd[READ_END]);
            // 退出程序
            exit(0);
        }
    }
}