#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// 定义一些信号的宏，方便使用
#define SIG_ALARM 14
#define SIG_USER1 16
#define SIG_USER2 17

// 定义一个处理信号的函数
void stop(int sig)
{
    // 打印信号的编号
    printf("Here is stop function!! Signal number is %d\n", sig);
}

int main()
{
    // 定义两个进程的ID
    int pid1, pid2;
    // 注册信号处理函数
    signal(SIG_ALARM, stop);
    // 创建第一个子进程
    pid1 = fork();
    if (pid1 == -1)
    {
        // 创建失败，打印错误信息并退出
        perror("fork");
        exit(1);
    }
    if (pid1 > 0)
    {
        // 父进程
        // 创建第二个子进程
        pid2 = fork();
        if (pid2 == -1)
        {
            // 创建失败，打印错误信息并退出
            perror("fork");
            exit(1);
        }
        if (pid2 > 0)
        {
            // 父进程
            // 设置一个一秒后触发的闹钟信号
            alarm(1);
            // 睡眠一秒，等待信号到达
            sleep(1);
            // 杀死两个子进程，发送不同的信号给它们
            kill(pid1, SIG_USER1);
            kill(pid2, SIG_USER2);
            // 等待两个子进程结束，并获取它们的状态
            int status1, status2;
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            // 打印父进程被杀死的信息
            printf("Parent process is killed !!\n");
            // 退出程序
            exit(0);
        }
        else
        {
            // 子进程2
            // 注册信号处理函数
            signal(SIG_USER2, stop);
            // 睡眠两秒，等待父进程发送信号
            sleep(2);
            // 打印子进程被杀死的信息
            printf("Child process 2 is killed by parent !!\n");
            // 退出程序
            exit(0);
        }
    }
    else
    {
        // 子进程1
        // 注册信号处理函数
        signal(SIG_USER1, stop);
        // 睡眠两秒，等待父进程发送信号
        sleep(2);
        // 打印子进程被杀死的信息
        printf("Child process 1 is killed by parent !!\n");
        // 退出程序
        exit(0);
    }
}