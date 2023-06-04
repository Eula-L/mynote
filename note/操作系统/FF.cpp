#include <iostream>
#include <list>
using namespace std;

//标志程序进入循环
bool run=1;//1一直循环，0结束运行

// 内存分区结构体
struct memory
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

// 初始化内存表
int creatMemory(int size)
{
    // memoryTable[0].num=0;
    // memoryTable[0].size=size;
    // memoryTable[0].start=0;
    // memoryTable[0].state=0;
    list<memory>::iterator it = memoryTable.begin();
    it->num = 1;
    it->size = size;
    it->start = 0;
    it->state = 0;
    return 0;
}

//创建内存
void allocateMemory()
{
    cout<<"请输入内存空间大小"<<endl;
    int size=0;
    cin>>size;
    creatMemory(size);
}

//添加作业
void addJob()
{
    job addOneJob;
    cout<<"作业名：";
    cin>>addOneJob.name;
    cout<<endl;
    cout<<"作业大小：";
    cin>>addOneJob.size;
    addOneJob.state=0;

    //将这个作业添加到作业表中
    jobTable.push_back(addOneJob);
    cout<<"OK"<<endl;
    
}
//回收作业

//用户选择
void inputSelection()
{
    cout<<"请选择操作："<<endl;
    cout<<"1.添加作业"<<endl;
    cout<<"2.回收作业"<<endl;
    cout<<"3.结束运行"<<endl;
    cout<<">>";
    int selection;
    cin>> selection;
    // cout<<selection<<endl;
    switch (selection)
    {
    case 1:
        /* 跳转到添加作业 */
        addJob();
        break;
    case 2:
        /* 跳转到回收作业 */
        break;
    case 3:
        /* 应用结束，无序跳转 */
        run=0;
        break;
    default:
        /* 提示输入错误请重新输入 */
        //TODO:添加一个清屏
        cout<<"输入错误，请重新输入"<<endl;
        break;
    }
}



int main()
{
    // 1、分配内存
    allocateMemory();
    // 2、选择分配，回收，退出
    while(run)
    {
        inputSelection();
    }
    
    // 2.1、分配
    // 空间充足

    // 空间不足，小于剩余空间，触发紧缩，大于，弹出分配失败

    // 2.2、回收

    // 2.3、退出
}