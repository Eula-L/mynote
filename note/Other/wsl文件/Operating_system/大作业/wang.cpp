#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100; // 最大分区数量和最大作业数量

int pcs_num; // process_num进程数量
int ptt_num; // partition_num分区数量
struct PTT
{
    int id;     // 分区编号
    int size;   // 分区大小
    int remain; // 剩余大小
};
PTT ptt[N];      // partition 每一块分区的大小
int pcs[N];      // process 每一个作业的大小
int pcs_alcs[N]; // process_allocation 作业的分配情况


// 排序规则：按分区编号排序
bool cmp3(PTT a, PTT b)
{
    return a.id < b.id;
}

void print_ptt()
{ 
    // 输出当前分区大小情况
    PTT backup[N];
    memcpy(backup, ptt, sizeof ptt);        // 备份
    sort(ptt + 1, ptt + ptt_num + 1, cmp3); // 对分区进行排序
    cout << "                      当前分区大小情况                      " << endl;
    cout << "分区序号\t";
    for (int i = 1; i <= ptt_num; i++)
        cout << "分区" << ptt[i].id << '\t';
    cout << endl;
    cout << "分区大小\t";
    for (int i = 1; i <= ptt_num; i++)
        cout << ptt[i].size << '\t';
    cout << endl;
    cout << "剩余大小\t";
    for (int i = 1; i <= ptt_num; i++)
        cout << ptt[i].remain << '\t';
    memcpy(ptt, backup, sizeof ptt); // 恢复
    cout << endl;
}

void print_pcs()
{
    cout << "                      当前作业分配情况                      " << endl;
    cout << "作业名称" << '\t';
    for (int i = 1; i <= pcs_num; i++)
        cout << "作业" << char('A' + i - 1) << "  " << '\t';
    cout << endl;
    cout << "作业分配" << '\t';
    for (int i = 1; i <= pcs_num; i++)
        if (pcs_alcs[i] == 0)
            cout << "未分配 " << '\t';
        else
            cout << "空闲区" << pcs_alcs[i] << '\t';
    cout << endl;
    cout << endl;
}

void print_all()
{
    print_pcs(); // 输出分配情况
    print_ptt(); // 输出分区大小情况
}

bool first_fit()
{ // 首次适应算法
    bool flag = true;
    // 初始化分配情况
    memset(pcs_alcs, 0, sizeof pcs_alcs);
    PTT backup[N];
    memcpy(backup, ptt, sizeof ptt); // 备份
    // 顺序遍历分区，找能放下的直接放
    for (int i = 1; i <= pcs_num; i++)
    {
        int j;
        for (j = 1; j <= ptt_num; j++)
        {
            if (pcs[i] <= ptt[j].remain)
            {                            // 作业小于分区剩余
                pcs_alcs[i] = ptt[j].id; // 分配
                ptt[j].remain -= pcs[i]; // 减剩余
                // print_all();
                printf("\n---------------------分配作业%c------------------------\n", char('A' + i - 1));
                print_pcs(); // 输出分配情况
                print_ptt(); // 输出分区大小情况

                break; // 该作业分配完毕，跳出
            }
        }
        if (j > ptt_num)
            flag = false; // 有一个没有被分配
    }
    printf("\n---------------------分配作业完成------------------------\n");
    print_all();
    memcpy(ptt, backup, sizeof ptt); // 恢复
    return flag;
}

// bool best_fit() {	//最佳适应分配
// 	bool flag = true;
// 	//初始化分配情况
// 	memset(pcs_alcs, 0, sizeof pcs_alcs);
// 	PTT backup[N];
// 	memcpy(backup, ptt, sizeof ptt);	//备份
// 	for(int i = 1; i <= pcs_num; i++) {
// 		sort(ptt + 1, ptt + ptt_num + 1, cmp1);	//对分区进行排序
// 		int j;
// 		for(j = 1; j <= ptt_num; j++) {
// 			if(pcs[i] <= ptt[j].remain) {	//作业小于分区剩余
// 				pcs_alcs[i] = ptt[j].id;	//分配
// 				ptt[j].remain -= pcs[i];	//减剩余
// 				break;	//该作业分配完毕，跳出
// 			}
// 		}
// 		if(j > ptt_num) flag = false;	//有一个没有被分配
// 	}
// 	print_all();
// 	memcpy(ptt, backup, sizeof ptt);	//恢复
// 	return flag;
// }

// bool worst_fit() {	//最差适应分配
// 	bool flag = true;
// 	//初始化分配情况
// 	memset(pcs_alcs, 0, sizeof pcs_alcs);
// 	PTT backup[N];
// 	memcpy(backup, ptt, sizeof ptt);	//备份
// 	for(int i = 1; i <= pcs_num; i++) {
// 		sort(ptt + 1, ptt + ptt_num + 1, cmp2);	//对分区进行排序
// 		int j;
// 		for(j = 1; j <= ptt_num; j++) {
// 			if(pcs[i] <= ptt[j].remain) {	//作业小于分区剩余
// 				pcs_alcs[i] = ptt[j].id;	//分配
// 				ptt[j].remain -= pcs[i];	//减剩余
// 				break;	//该作业分配完毕，跳出
// 			}
// 		}
// 		if(j > ptt_num) flag = false;	//有一个没有被分配
// 	}
// 	print_all();
// 	memcpy(ptt, backup, sizeof ptt);	//恢复
// 	return flag;
// }

int main()
{
    cout << "09刘昊" << endl
         << endl;
    cout << "请输入分区数量" << endl;
    cin >> ptt_num;
    cout << "请输入每一块分区的大小" << endl;
    for (int i = 1; i <= ptt_num; i++)
    {
        ptt[i].id = i;
        cin >> ptt[i].size;
        ptt[i].remain = ptt[i].size;
    }
    cout << "请输入作业数量" << endl;
    cin >> pcs_num;
    cout << "请输入每一个作业的大小" << endl;
    for (int i = 1; i <= pcs_num; i++)
        cin >> pcs[i];
    print_ptt(); // 输出分区大小情况
    print_pcs(); // 输出分配情况
    cout << endl;

    cout << "首次适应算法" << endl;
    cout << endl;
    bool f1 = first_fit();

    return 0;
}
/*
4
16 14 5 30
3
15 16 15
*/
