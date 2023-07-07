# IPC进程间通信

## 概念

进程信技术简称IPC,可以利用此技木让多个进程相传建消数据，有大量的进程间通信方案

* pipe 有匿名管道
* fifo 命名管道
* Posix 消息队列
* System 消息队列
* Signal 信号
* Socket 套接字
* mmap 文件映射

>进程有虚拟地址空间，进程间通信在虚拟地址的哪一层实现的?
>>绝大多数进程间通信是在内核层完成的， 因为内核层内存共享

## pipe匿名管道

为了便于开发者使用管道可以使用pipe函数创建管道，创建成功后会生成两个文件描述符，分别指向管道的读端fds[0]和写端fds[1]。**匿名管道只能再有亲缘关系的进程之间使用**

### 管道的原理

两个进程公用一个管道，实现通信

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1686717339460.png)

#### 管道的特点

1. 是一种传输介质，可以传输数据
2. 管道传输具有方向性
3. 管道具备存储能力，虽然不能持久存储，只能*暂存*

#### 缺点

匿名管道只能在有亲缘关系的进程间的通信

### 使用管道

#### 创建

```C
pipe(int fds[2]);
```

***注意***：管道创建要在 创建子进程之前完成， 避免子进程创建管道

<br>

#### 使用

```C
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
```

<br>

#### 回收

1. 每个指向管道的描述符都是一个引用计数，如果引用计数为0，系统自动释放管道空间，否则管道一直存在于内核层
2. 管道使用时要确定通信方向，父写子读，子写父读，父子进程将不用的描述符关闭 ***关闭不用的***
3. pipe_fd使用完毕要close 引用计数-1 ***用完要关闭***
4. shutdown可以直接将引用计数清0

>工作方式
>>单工 : 确定通信方向， 非读即写， 不可变更

>>半双工/可调节单工: 非读即写，但是不同时刻可以调节读写

>>双工:可以同时读写

<br>

### 匿名管道使用时的四种特殊情况

这四种情况具有**普遍意义**

1. 管道的读写两端存在但是写端未向管道内写数据，读端读取完管道数据后如果管道为null，再次*读阻塞*
2. 管道读写两端存在，但是读端未读取管道数据，写端写满管道后，再次写阻塞
3. 管道写端关闭，读端读取管道剩余内容后，再次读读到0
4. 管道读端关闭，写端向管道写数据，系统会发送SIGPIPE信号，杀死写端进程，读端关闭的情况下不允许写端访问管道

>在一个C/S模型中，客户端发送了一条请求消息之后客户端异常关闭，服务端回复结果时异常关闭，服务端异常关闭原因？
>>(SIGPIPE信号)send(sockfd , buffer, size , MSG NOSIGNAL)


# mmap文件映射

## 功能

是一种内存映射文件的技术，它允许将文件映射到进程的虚拟内存空间，使得文件的内容可以像访问内存一样被读取和写入。

## 使用

### 头文件

```c
#include <sys/mman.h>
```

### 函数原型、参数、返回值

```c
void * ptr = mmap(NULL , size , PROT READIPROT WRITE , int how , int fd , 0);
```

### 参数

![mmap%E5%8F%82%E6%95%B0.drawio.png](https://liuhao-oss.oss-cn-beijing.aliyuncs.com/mmap%E5%8F%82%E6%95%B0.drawio.png)

#### 映射方式
共享映射 MAP_SHARED，共享映射有 ***Sync同步机制***
私有映射 MAP_PRIVATE

### 原理

多进程间利用 MAP_SHARED的Sync同步机制keyi可以实现共享映射实现进程通信

![1688305464094.png](https://liuhao-oss.oss-cn-beijing.aliyuncs.com/1688305464094.png)


### 返回值

成功返回映射内存地址ptr
失败返回MAP_FAILED关键字

## 回收

```c
munmap(ptr，size); //释放映射内存
```

