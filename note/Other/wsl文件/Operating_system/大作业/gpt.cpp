#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int memory[MAX_SIZE]; // 存储空间数组
int size[MAX_SIZE]; // 存储空间大小数组
int used[MAX_SIZE]; // 存储空间使用状态数组

// 初始化存储空间
void init_memory() {
    for (int i = 0; i < MAX_SIZE; i++) {
        memory[i] = 0;
        size[i] = 0;
        used[i] = 0;
    }
}

// 显示存储空间状态
void show_memory() {
    printf("Memory Status:\n");
    printf("Address\tSize\tUsed\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d\t%d\t%d\n", i, size[i], used[i]);
    }
}

// 首次适应算法分配内存
int allocate_memory(int process_size) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (used[i] == 0 && size[i] >= process_size) {
            // 找到第一个可用的空间
            int remainder = size[i] - process_size;
            if (remainder > 0) {
                // 分配后剩余的空间
                size[i] = process_size;
                size[i + process_size] = remainder;
                used[i] = 1;
                return i;
            } else {
                // 分配整个空间
                size[i] = process_size;
                used[i] = 1;
                return i;
            }
        }
    }
    // 没有可用的空间
    return -1;
}

// 回收内存
void free_memory(int address) {
    used[address] = 0;
    // 检查前后是否有空闲空间，有则合并
    if (address > 0 && used[address - 1] == 0) {
        size[address - 1] += size[address];
        size[address] = 0;
        used[address] = 0;
        address--;
    }
    if (address < MAX_SIZE - 1 && used[address + size[address]] == 0) {
        size[address] += size[address + size[address]];
        size[address + size[address]] = 0;
        used[address + size[address]] = 0;
    }
}

int main() {
    init_memory();
    int choice, process_size, address;
    do {
        printf("\n1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Show Memory Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter process size: ");
                scanf("%d", &process_size);
                address = allocate_memory(process_size);
                if (address == -1) {
                    printf("Memory allocation failed.\n");
                } else {
                    printf("Memory allocated at address %d.\n", address);
                }
                break;
            case 2:
                printf("Enter address to free: ");
                scanf("%d", &address);
                free_memory(address);
                printf("Memory freed.\n");
                break;
            case 3:
                show_memory();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
    return 0;
}