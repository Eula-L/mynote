
//还是之前的样子合理

#include <iostream>
#include <list>
using namespace std;

// 标志程序进入循环
bool run = 1; // 1一直循环，0结束运行
// 实事先规定的不在切割的剩余分区的大小
int minSize = 0;
// 剩余内存空间总大小，用于判断是否需要紧缩
int residualSize = 0;

// 内存分区结构体
struct memory /*内存分区块*/
{
    int num;    // 分区号
    int size;   // 分区大小
    int start;  // 分区起始地址
    bool state; // 分区状态,0表示未分配，1表示已经分配
};

// 作业结构体
struct job
{
    string name; // 作业名
    int size;    // 作业所需空间
    bool state;  // 作业状态,0表示未分配，1表示已经分配
    int start;   // 作业开始地址
};
// 内存表
// 为了支持回收合并，所以使用list
list<memory> memoryTable;
// 作业表,用于记录当前作业的信息
list<job> jobTable;
//-------------------------------------------
// 函数声明
// 初始化内存表
int creatMemory(int size);
// 创建内存
void allocateMemory();
// 首次适应分配内存
int FF(job newJob);
// 添加作业
int addJob();
//-------------------------------------------

// 初始化内存表
int creatMemory(int size)
{
    // memoryTable[0].num=0;
    // memoryTable[0].size=size;
    // memoryTable[0].start=0;
    // memoryTable[0].state=0;
    // residualSize = size;

    //list<memory>::iterator it = memoryTable.begin();

    // it->num = 1;
    // it->size = size;
    // it->start = 0;
    // it->state = 0;
    //错误，添加元素需要使用push——back

    memory allMemory;
    allMemory.num=1;
    allMemory.size=size;
    allMemory.start=0;
    allMemory.state=0;
    memoryTable.push_back(allMemory);

    return 0;
}

// 创建内存
void allocateMemory()
{
    cout << "请输入内存空间大小" << endl;
    int size = 0;
    cin >> size;
    creatMemory(size);
    cout << "请输入不再切割的最小内存空间大小" << endl;
    cin >> minSize;
}

// 首次适应分配内存
int FF(job newJob)
{
    // 从头开始查询表
    for (list<memory>::iterator it = memoryTable.begin(); it != memoryTable.end(); it++)
    {
        // 内存空间未分配，并且这个空间大于当前所需空间
        //cout<<"开发——进来了"<<endl;
        if ((it->state == 0) || ((it->size) > newJob.size))
        {
            // 判断是否可以分割
            if ((it->size) - (newJob.size) > minSize)
            {
                // 发生分割
                //  新分区
                memory newMemory;
                newMemory.num = it->num + 1;
                newMemory.size = it->size - newJob.size;
                newMemory.start = it->start + newJob.size;
                newMemory.state = 0;
                // 将新分区插入到内存分区表中
                memoryTable.push_back(newMemory);
                // 原分区
                it->size = newJob.size;
                it->state = 1;
                residualSize -= newJob.size;
                cout << "  发生分割！";
            }
            else
            {
                // 不发生分割
                // 分区大小不变，全分配给这个作业
                it->state = 1;
                residualSize -= it->size;
                cout << "未发生分割！";
            }
            cout << "分配内存成功!内存分区号为：" << it->num << endl;
            return 0;
        }
    }
    cout << "分配内存失败!"<< endl;
    return -1;
}

// 添加作业
int addJob()
{
    job addOneJob;
    cout << "作业名：";
    cin >> addOneJob.name;
    cout << endl;
    cout << "作业大小：";
    cin >> addOneJob.size;
    addOneJob.state = 0; // 当前状态是未分配

    // 将这个作业添加到作业表中,当前状态是未分配
    jobTable.push_back(addOneJob);
    // 分配内存
    int res=FF(addOneJob);
    if(res==0)
    {
        cout<<"开发——内存分配成功"<<endl;
    }
    else
    {
        cout<<"开发——内存分配失败"<<endl;
    }
    return 0;
}
// 回收作业

// 用户选择
void inputSelection()
{
    cout << "请选择操作：" << endl;
    cout << "1.添加作业" << endl;
    cout << "2.回收作业" << endl;
    cout << "3.结束运行" << endl;
    cout << ">>";
    int selection;
    cin >> selection;
    // cout<<selection<<endl;
    int retunNum = -1; // 用于接函数的返回值，一次判断作业分配到了那一个阶段
    switch (selection)
    {
    case 1:
        /* 跳转到添加作业 */
        retunNum = addJob();
        if (retunNum == 0)
        {
            cout << "添加作业成功" << endl;
        }
            
        break;
    case 2:
        /* 跳转到回收作业 */
        break;
    case 3:
        /* 应用结束，无序跳转 */
        run = 0;
        break;
    default:
        /* 提示输入错误请重新输入 */
        // TODO:添加一个清屏
        cout << "输入错误，请重新输入" << endl;
        break;
    }
}

int main()
{
    // 1、分配内存
    allocateMemory();
    // 2、选择分配，回收，退出
    while (run)
    {
        inputSelection();
    }

    // 2.1、分配
    // 空间充足

    // 空间不足，小于剩余空间，触发紧缩，大于，弹出分配失败

    // 2.2、回收

    // 2.3、退出
}
