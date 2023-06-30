#include <stdio.h>

#define MAX_SIZE 1000 // 内存总大小
#define MIN_SIZE 10   // 最小分区大小

// 定义分区结构体
typedef struct
{
    int start;   // 分区起始地址
    int size;    // 分区大小
    int is_free; // 分区是否空闲
} Partition;

Partition memory[MAX_SIZE / MIN_SIZE]; // 内存分区数组
int partition_count = 0;               // 分区数量

// 初始化内存分区
void initialize_memory()
{
    int i;
    for (i = 0; i < MAX_SIZE / MIN_SIZE; i++)
    {
        memory[i].start = i * MIN_SIZE;
        memory[i].size = MIN_SIZE;
        memory[i].is_free = 1;
    }
    partition_count = MAX_SIZE / MIN_SIZE;

}

// 分配内存
int allocate_memory(int size)
{
    int i;
    for (i = 0; i < partition_count; i++)
    {
        if (memory[i].is_free && memory[i].size >= size)
        {
            int remaining_size = memory[i].size - size;
            if (remaining_size >= MIN_SIZE)
            {
                // 分裂分区
                memory[i].size = size;
                memory[i].is_free = 0;
                int j;
                for (j = partition_count; j > i + 1; j--)
                {
                    memory[j] = memory[j - 1];
                }
                memory[i + 1].start = memory[i].start + size;
                memory[i + 1].size = remaining_size;
                memory[i + 1].is_free = 1;
                partition_count++;
            }
            else
            {
                // 不分裂分区
                memory[i].is_free = 0;
            }
            return memory[i].start;
        }
    }
    return -1; // 分配失败
}

// 释放内存
void free_memory(int start)
{
    int i;
    for (i = 0; i < partition_count; i++)
    {
        if (memory[i].start == start)
        {
            memory[i].is_free = 1;
            // 合并相邻空闲分区
            if (i > 0 && memory[i - 1].is_free)
            {
                memory[i - 1].size += memory[i].size;
                int j;
                for (j = i; j < partition_count - 1; j++)
                {
                    memory[j] = memory[j + 1];
                }
                partition_count--;
                i--;
            }
            if (i < partition_count - 1 && memory[i + 1].is_free)
            {
                memory[i].size += memory[i + 1].size;
                int j;
                for (j = i + 1; j < partition_count - 1; j++)
                {
                    memory[j] = memory[j + 1];
                }
                partition_count--;
            }
            break;
        }
    }
}

// 打印内存分区信息
void print_memory()
{
    int i;
    for (i = 0; i < partition_count; i++)
    {
        printf("Partition %d: start=%d, size=%d, is_free=%d\n", i, memory[i].start, memory[i].size, memory[i].is_free);
    }
}

int main()
{
    initialize_memory();
    int p1 = allocate_memory(50);
    int p2 = allocate_memory(30);
    int p3 = allocate_memory(20);
    int p4 = allocate_memory(80);
    print_memory();
    free_memory(p2);
    free_memory(p4);
    print_memory();
    return 0;
}