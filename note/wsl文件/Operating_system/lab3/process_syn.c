#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 // 缓冲区大小

int buffer[BUFFER_SIZE]; // 缓冲区
int in = 0;              // 生产者向缓冲区中添加元素的位置
int out = 0;             // 消费者从缓冲区中取出元素的位置

sem_t empty;           // 空缓冲区数量的信号量
sem_t full;            // 满缓冲区数量的信号量
pthread_mutex_t mutex; // 互斥锁

void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100;        // 生产一个随机数
        sem_wait(&empty);           // 等待空缓冲区
        pthread_mutex_lock(&mutex); // 加锁
        buffer[in] = item;          // 将元素添加到缓冲区
        printf("生产者添加元素 %d 到缓冲区的位置 %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;  // 更新位置
        pthread_mutex_unlock(&mutex); // 解锁
        sem_post(&full);              // 增加满缓冲区数量
        sleep(rand() % 3);            // 随机休眠
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);            // 等待满缓冲区
        pthread_mutex_lock(&mutex); // 加锁
        item = buffer[out];         // 从缓冲区中取出元素
        printf("消费者取出元素 %d 从缓冲区的位置 %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // 更新位置
        pthread_mutex_unlock(&mutex);  // 解锁
        sem_post(&empty);              // 增加空缓冲区数量
        sleep(rand() % 3);             // 随机休眠
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid_producer, tid_consumer;
    srand(time(NULL));                                   // 初始化随机数种子
    sem_init(&empty, 0, BUFFER_SIZE);                    // 初始化空缓冲区数量为 BUFFER_SIZE
    sem_init(&full, 0, 0);                               // 初始化满缓冲区数量为 0
    pthread_mutex_init(&mutex, NULL);                    // 初始化互斥锁
    pthread_create(&tid_producer, NULL, producer, NULL); // 创建生产者线程
    pthread_create(&tid_consumer, NULL, consumer, NULL); // 创建消费者线程
    pthread_join(tid_producer, NULL);                    // 等待生产者线程结束
    pthread_join(tid_consumer, NULL);                    // 等待消费者线程结束
    sem_destroy(&empty);                                 // 销毁空缓冲区信号量
    sem_destroy(&full);                                  // 销毁满缓冲区信号量
    pthread_mutex_destroy(&mutex);                       // 销毁互斥锁
    return 0;
}
