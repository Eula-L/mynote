#include <iostream>
#include <map>
using namespace std;

// 定义进程结构体
struct Process {
    int processId;
    int size;
};

// 定义页表项结构体
struct PageTableEntry {
    int frameNumber;
    bool valid;
};

// 定义全局变量
const int PAGE_SIZE = 4;  // 每页大小
const int MEMORY_SIZE = 16;  // 内存大小

// 定义页表
map<int, PageTableEntry> pageTable;

// 定义内存
int memory[MEMORY_SIZE];

// 分配内存空间
int allocateMemory(int processId, int size) {
    int numPages = (size + PAGE_SIZE - 1) / PAGE_SIZE;  // 计算所需页数

    // 遍历内存查找连续的空闲页框
    int startFrame = -1;
    int count = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            if (count == 0) {
                startFrame = i;
            }
            count++;
            if (count == numPages) {
                break;
            }
        } else {
            count = 0;
        }
    }

    // 如果找到连续的空闲页框，则分配内存
    if (count == numPages) {
        for (int i = startFrame; i < startFrame + numPages; i++) {
            memory[i] = processId;
            pageTable[i].frameNumber = i;
            pageTable[i].valid = true;
        }
        return startFrame;
    }

    // 如果没有足够的连续空闲页框，则返回-1表示分配失败
    return -1;
}

// 回收内存空间
void deallocateMemory(int processId) {
    // 遍历页表，找到对应进程的页框并回收
    for (auto& entry : pageTable) {
        if (entry.second.valid && memory[entry.second.frameNumber] == processId) {
            memory[entry.second.frameNumber] = 0;
            entry.second.valid = false;
        }
    }
}

// 地址转换
int translateAddress(int processId, int logicalAddress) {
    int pageNumber = logicalAddress / PAGE_SIZE;
    int offset = logicalAddress % PAGE_SIZE;

    // 查找页表项
    if (pageTable.find(pageNumber) != pageTable.end() && pageTable[pageNumber].valid && memory[pageTable[pageNumber].frameNumber] == processId) {
        int physicalAddress = pageTable[pageNumber].frameNumber * PAGE_SIZE + offset;
        return physicalAddress;
    }

    // 如果页表项不存在或无效，则返回-1表示地址转换失败
    return -1;
}

int main() {
    int choice;
    int processId, size, logicalAddress;
    int physicalAddress;

    while (true) {
        cout << "1. 分配内存空间" << endl;
        cout << "2. 回收内存空间" << endl;
        cout << "3. 地址转换" << endl;
        cout << "4. 退出程序" << endl;
        cout << "请选择操作: ";
        cin >> choice;
        int frameNumber;
        switch (choice) {
            case 1:
                cout << "请输入进程ID和大小: ";
                cin >> processId >> size;
                frameNumber = allocateMemory(processId, size);
                if (frameNumber != -1) {
                    cout << "已成功分配内存，起始页框号为: " << frameNumber << endl;
                } else {
                    cout << "分配内存失败，没有足够的空闲页框" << endl;
                }
                break;
            case 2:
                cout << "请输入要回收的进程ID: ";
                cin >> processId;
                deallocateMemory(processId);
                cout << "已成功回收内存" << endl;
                break;
            case 3:
                cout << "请输入进程ID和逻辑地址: ";
                cin >> processId >> logicalAddress;
                physicalAddress = translateAddress(processId, logicalAddress);
                if (physicalAddress != -1) {
                    cout << "物理地址为: " << physicalAddress << endl;
                } else {
                    cout << "地址转换失败，无效的页表项或无效的逻辑地址" << endl;
                }
                break;
            case 4:
                cout << "程序已退出" << endl;
                return 0;
            default:
                cout << "无效的选择，请重新输入" << endl;
                break;
        }
    }

    return 0;
}