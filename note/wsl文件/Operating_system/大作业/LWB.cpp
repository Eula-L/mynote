#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 10

// 分区结构体
typedef struct
{
    int start;
    int end;
    int size;
    int allocated;
} Partition;

Partition partitions[MAX_PARTITIONS];
int numPartitions = 0;

// 初始化分区
void initializePartitions()
{
    int i;
    for (i = 0; i < MAX_PARTITIONS; i++)
    {
        partitions[i].start = -1;
        partitions[i].end = -1;
        partitions[i].size = 0;
        partitions[i].allocated = 0;
    }
}

// 显示存储空间状态
void displayStatus()
{
    int i;
    printf("Partition\tStart\tEnd\tSize\tAllocated\n");
    for (i = 0; i < numPartitions; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t%s\n", i + 1, partitions[i].start, partitions[i].end,
               partitions[i].size, partitions[i].allocated ? "Yes" : "No");
    }
}

// 分配内存
void allocateMemory(int processSize)
{
    int i;
    for (i = 0; i < numPartitions; i++)
    {
        if (!partitions[i].allocated && partitions[i].size >= processSize)
        {
            partitions[i].allocated = 1;
            printf("Process of size %d allocated to Partition %d\n", processSize, i + 1);
            return;
        }
    }
    printf("No suitable partition found for process of size %d\n", processSize);
}

// 回收内存
void deallocateMemory(int partitionIndex)
{
    if (partitionIndex >= 0 && partitionIndex < numPartitions)
    {
        if (partitions[partitionIndex].allocated)
        {
            partitions[partitionIndex].allocated = 0;
            printf("Partition %d deallocated\n", partitionIndex + 1);
        }
        else
        {
            printf("Partition %d is already deallocated\n", partitionIndex + 1);
        }
    }
    else
    {
        printf("Invalid partition index\n");
    }
}

// 紧凑技术
void compactMemory()
{
    int i, j, k;
    int totalSize = 0;
    int numAllocated = 0;

    // 计算已分配分区的总大小
    for (i = 0; i < numPartitions; i++)
    {
        if (partitions[i].allocated)
        {
            totalSize += partitions[i].size;
            numAllocated++;
        }
    }

    // 移动已分配分区到连续的位置
    if (numAllocated > 0)
    {
        int currentPosition = 0;
        for (i = 0; i < numPartitions; i++)
        {
            if (partitions[i].allocated)
            {
                partitions[i].start = currentPosition;
                partitions[i].end = currentPosition + partitions[i].size - 1;
                currentPosition += partitions[i].size;
            }
        }
    }

    // 重置未分配分区
    for (j = i; j < numPartitions; j++)
    {
        partitions[j].start = -1;
        partitions[j].end = -1;
        partitions[j].size = 0;
        partitions[j].allocated = 0;
    }

    printf("Memory compacted\n");
}

int main()
{
    int choice, processSize, partitionIndex;

    initializePartitions();

    do
    {
        printf("\nMemory Management Menu:\n");
        printf("1. Display Memory Status\n");
        printf("2. Allocate Memory\n");
        printf("3. Deallocate Memory\n");
        printf("4. Compact Memory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Press any key to display memory status...\n");
            getchar(); // 消耗换行符
            getchar(); // 等待用户按下任意键
            displayStatus();
            break;
        case 2:
            printf("Enter process size: ");
            scanf("%d", &processSize);
            allocateMemory(processSize);
            break;
        case 3:
            printf("Enter partition index to deallocate: ");
            scanf("%d", &partitionIndex);
            deallocateMemory(partitionIndex - 1);
            break;
        case 4:
            compactMemory();
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 5);

    return 0;
}