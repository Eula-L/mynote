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

// 添加一个打印当前内存图的功能
void printMemoryTable();
// 添加一个打印当前作业图的功能
void printJobTable();

// 首次适应分配内存
int FF(job newJob);
// 添加作业
int addJob();

// 更新内存空间序号
int updateNumber();
// 合并
int merge(list<memory> &myList, list<memory>::iterator it);

// 紧缩
int retrench();

// 回收
int recycle();

//-------------------------------------------

// 初始化内存表
int creatMemory(int size)
{
    // memoryTable[0].num=0;
    // memoryTable[0].size=size;
    // memoryTable[0].start=0;
    // memoryTable[0].state=0;
    // residualSize = size;

    // list<memory>::iterator it = memoryTable.begin();

    // it->num = 1;
    // it->size = size;
    // it->start = 0;
    // it->state = 0;
    // 错误，添加元素需要使用push_back
    residualSize = size;
    memory allMemory;
    allMemory.num = 1;
    allMemory.size = size;
    allMemory.start = 0;
    allMemory.state = 0;
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
    int res_pos = -1; // 返回值，默认为分配失败
    // 在这里判断是否请求的内存是否小于总剩余
    if (newJob.size <= residualSize)
    {
        // 所需的小于剩余的全部的，那么一定可以成功
        //  从头开始查询表
        for (list<memory>::iterator it = memoryTable.begin(); it != memoryTable.end(); it++)
        {
            // 内存空间未分配，并且这个空间大于当前所需空间
            // cout<<"开发——进来了"<<endl;
            if ((it->state == 0) && ((it->size) >= newJob.size)) // 注意判断逻辑，“并且”
            {
                // 判断是否可以分割
                if ((it->size) - (newJob.size) >= minSize)
                {
                    // 发生分割
                    //  新分区
                    memory newMemory;
                    newMemory.num = it->num + 1;
                    newMemory.size = it->size - newJob.size;
                    newMemory.start = it->start + newJob.size;
                    newMemory.state = 0;

                    // 错误
                    // 将新分区插入到内存分区表中
                    // memoryTable.push_back(newMemory);
                    // 插入当前位置的下一个位置
                    auto newp = it;
                    newp++;
                    memoryTable.insert(newp, newMemory);

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
                res_pos = it->start; // 原分区的起始位置就是该作业分配的空间的起始位置
                //cout << "开发——更新res_pos" << endl;
                cout << "分配内存成功!内存分区号为：" << it->num << endl;
                return res_pos;
            }
        }
        // 遍历之后，仍然没成功。
        // TODO:触发紧缩
        retrench();
        FF(newJob);
    }
    else
    {
        cout << "空间不足，分配内存失败!" << endl;
        return -1;
    }
    return -1;
}

// 添加一个打印当前内存图的功能
void printMemoryTable()
{
    cout << "---------当前内存分布图---------" << endl;
    cout << "--------------------------------" << endl;
    cout << "|内存号"
         << "  "
         << "大小"
         << "  "
         << "起始位置"
         << "    "
         << "状态|" << endl;
    cout << "--------------------------------" << endl;
    for (list<memory>::iterator it = memoryTable.begin(); it != memoryTable.end(); it++)
    {
        // cout << it->num << "  " << it->size << "  " << it->start << "  " << it->state << endl;
        printf("|%5d%5d%10d", it->num, it->size, it->start);
        if (it->state == 0)
        {
            cout << "    未分配|" << endl;
        }
        else
        {
            cout << "    已分配|" << endl;
        }
        cout << "--------------------------------" << endl;
    }
}

// 添加一个打印当前作业图的功能
void printJobTable()
{
    cout << "---------当前作业分布图---------" << endl;
    cout << "--------------------------------" << endl;
    cout << "|作业名"
         << "  "
         << "大小"
         << "  "
         << "起始位置"
         << "    "
         << "状态|" << endl;
    cout << "--------------------------------" << endl;
    for (list<job>::iterator it = jobTable.begin(); it != jobTable.end(); it++)
    {
        cout << "|";
        cout.width(6);
        cout << it->name;
        printf(" %4d%9d", it->size, it->start);
        if (it->state == 0)
        {
            cout << "    未分配|" << endl;
        }
        else
        {
            cout << "    已分配|" << endl;
        }
        cout << "--------------------------------" << endl;
    }
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
    addOneJob.start = -1;

    // 将这个作业添加到作业表中,当前状态是未分配
    jobTable.push_back(addOneJob);
    // 分配内存,返回值是改作业被分配的起始位置

    int res_pos = FF(addOneJob);
    if (res_pos >= 0)
    {
        //cout << "开发——内存分配成功" << endl;
        list<job>::iterator pos = jobTable.end();
        pos--;
        pos->start = res_pos;
        pos->state = 1;
    }
    else
    {
        //cout << "开发——内存分配失败" << endl;
    }

    updateNumber();

    printMemoryTable();
    printJobTable();

    return 0;
}

// 更新内存空间序号
int updateNumber()
{
    int num = 1;
    for (list<memory>::iterator it = memoryTable.begin(); it != memoryTable.end(); it++)
    {
        it->num = num;
        num++;
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
        recycle();
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
// 合并
int merge(list<memory> &myList, list<memory>::iterator it)
{

    if (it != myList.begin()) // 不是第一个
    {
        auto before = it;
        before--;
        if (distance(it,myList.end())!=1) // 不是最后一个
        {
            //it != myList.end()--
            auto after = it;
            after++;
            if (before->state == 0)
            {

                if (after->state == 0)
                {
                    before->size += it->size + after->size;
                    // 删除元素
                    it = myList.erase(it);
                    after = myList.erase(after);
                }
                else
                {
                    before->size += it->size;
                    // 删除元素
                    it = myList.erase(it);
                }
            }
            else
            {
                if (after->state == 0)
                {
                    it->size += after->size;
                    // 删除元素
                    after = myList.erase(after);
                }
                else
                {
                    // 不合并
                }
            }
        }
    }
    else // 是第一个
    {
        if (distance(it,myList.end())!=1) // 不是最后一个
        {
            auto after = it;
            after++;
            if (after->state == 0)
            {
                it->size += after->size;
                // 删除元素
                after = myList.erase(after);
            }
        }
        else // 也是最后一个，就一个
        {
            //不合并
        }
    }
    updateNumber();
    return 0;
}

// 紧缩(可以优化)
int retrench()
{
    list<memory>::iterator find_full = memoryTable.begin(); // 找已经占用的
    list<memory>::iterator find_null = memoryTable.begin(); // 找未占用的
    while (1)
    {
        if (find_full->state != 1 || find_full->num <= find_null->size)
        {
            find_full++;
        }
        if (find_null->state != 0)
        {
            find_null++;
        }
        if (find_full->state == 1 && find_null->state == 0 && find_full->size > find_null->size)
        {
            // 交换信息，不能调用swap，因为数据需要修改
            int temp = find_full->size;
            find_full->size = find_null->size;
            find_null->size = temp;

            find_full->start = find_null->start + find_null->size;

            find_full->state = 0;
            find_null->size = 1;

            // TOODO 调用合并
            // 合并
            merge(memoryTable, find_full);
        }
    }
}

// 回收
int recycle()
{
    // 打印当前作业分布
    printJobTable();
    cout << "请输入要回收的作业" << endl;
    string rec_name; // 要回收的作业名
    int rec_start = -1;
    cin >> rec_name;

    for (list<job>::iterator it = jobTable.begin(); it != jobTable.end(); it++)
    {
        if (it->name == rec_name)
        {
            rec_start = it->start;
            it->start = -1;
            it->state = 0; // 将作业设置为未分配
            residualSize += it->size;
        }
    }
    for (list<memory>::iterator it = memoryTable.begin(); it != memoryTable.end(); it++)
    {
        if (it->start == rec_start)
        {
            // 找到要回收的空间
            it->state = 0; // 将空间设置为未分配
            // 调用合并
            merge(memoryTable, it);
            break;
        }
    }
    cout << "回收完成" << endl;
    cout << endl;
    cout << "当前内存分布" << endl;
    printMemoryTable();
    cout << "当前作业分布" << endl;
    printJobTable();
    return 0;
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