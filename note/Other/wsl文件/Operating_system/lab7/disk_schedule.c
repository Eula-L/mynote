#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_DIASKNUMBER 200			 // 定义磁盘的最大磁道数
#define TRUE 1						 // 定义真值
#define FALSE 0						 // 定义假值
int disk[MAX_DIASKNUMBER + 1] = {0}; // 存放进程请求磁盘I/O请求时的磁道号,且数字0不做磁道号
int disk_currentnumber = 100;		 // 当前访问的磁盘号，假设当前磁道号为100
int choice = 1;						 // 决定扫描方向（默认为1），1-向增加方向；2-向减小方向
typedef struct Disk_struct			 // 磁盘数据结构
{
	int disk_nextnumber;	   // 下一个访问的磁盘号
	int disk_distence;		   // 计算移动距离
	int total_distence;		   // 总的移动距离
	int count;				   // 计算输入了几个磁道号
	float average_seek_length; // 计算平均寻道长度
} DISK;
int COMPARE(const void *a, const void *b) // 比较函数，为qsort算法提供比较函数
{
	return *(int *)a - *(int *)b;
}
void SCANF() // 输入算法
{
	int i = 1;		 // 用作给disk数组的下标
	char over = 'Y'; // 用作结束输入标志
	while (TRUE)
	{
		if (over == 'N')
		{
			break; // 结束
		}
		else
		{
			printf("请输入被访问的第%d个磁道号：", i);
			int e = 0;		 // 用于接收输入的磁道号，并防止输入为字符出现的错误
			scanf("%d", &e); // 输入进程调用的磁道号
			int c = 0;
			while ((c = getchar()) != '\n')
				;  //---也要清空缓冲区防止输入多个字符导致循环多次
			if (e) //----输入字符时为报错，通过用一个变量接收再赋值解决
			{
				disk[i] = (int)e;
				i++;
			}
			else
			{
				printf("你输入了0或者未按要求输入！请重新输入！\n");
				continue;
			}
		}
		while (TRUE)
		{
			printf("是否继续输入？请选择：（是-Y/y；否-N/n）："); // 选择是否继续输入
			scanf("%c", &over, 1);								  // 因为编译器的不同，1表示只读取1个输入字符
			int c = 0;
			while ((c = getchar()) != '\n')
				;							//---也要清空缓冲区防止输入多个字符导致循环多次
			if (over == 'y' || over == 'n') // 将小写输入转化为大写
			{
				over = toupper(over);
			}
			if (over == 'Y' || over == 'N')
			{
				break;
			}
			else
			{
				printf("请按要求输入！\n"); //----控制错误输入
				continue;
			}
		}
	}
}
void CHOOSE()
{
	printf("请输入磁道扫描方向（默认为I/i）：（I/i-向磁道号增加方向；D/d-向磁道号减小方向）\n");
	char choose = NULL; // 控制选择从什么方向开始
	while (TRUE)
	{
		if (choose == 'I' || choose == 'D')
		{
			break;
		}
		scanf("%c", &choose, 1);
		int c = 0;
		while ((c = getchar()) != '\n')
			; //---也要清空缓冲区防止输入多个字符导致循环多次
		while (TRUE)
		{
			if (choose == 'i' || choose == 'd')
			{
				choose = toupper(choose);
			}
			if (choose == 'D')
			{
				choice = 0;
				break;
			}
			else if (choose == 'I') // 全局变量choice以默认为1
			{
				break;
			}
			else
			{
				printf("请按要求输入！\n");
				break;
			}
		}
	}
}
void SEARCH(int *m, int *p) // 寻找第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
{
	for (int j = 0; j <= MAX_DIASKNUMBER; j++)
	{
		if (!disk[j]) // 求排序后的第一个磁道号在数组中的位置
		{
			(*m)++;
		}
		if (disk[j] == disk_currentnumber) // 求最初的磁头所在的磁道号在数组中的位置
		{
			(*p) = j;
		}
	}
}
void FCFS()
{
	printf("FCFS算法：\n");
	DISK disks = {0, 0, 0, 0, 0};				  // 定义并初始化
	for (int k = 0; k < MAX_DIASKNUMBER + 1; k++) // 初始化disk数组
	{
		disk[k] = 0;
	}
	disk_currentnumber = 100; // 当前访问的磁盘号，假设当前磁道号为100
	SCANF();				  // 输入进程提出请求的磁道号
	//--FCFS核心算法
	int i = 1; // 用作disk数组的下标
	for (i = 1; disk[i] != 0; i++)
	{
		disks.disk_nextnumber = disk[i];
		printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
		printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
		disks.disk_distence = abs(disk_currentnumber - disk[i]); // 有可能相减为负数，用abs化为正数
		printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
		disks.total_distence += disks.disk_distence;
		printf("总移动距离：%18d\n", disks.total_distence);
		disk_currentnumber = disk[i];
	}
	//--FCFS核心算法
	disks.count = --i;													   // 计算输入了几个磁道号
	disks.average_seek_length = (float)disks.total_distence / disks.count; // 求平均寻道长度，为避免丢失精度使用强制类型转换为float型
	printf("平均寻道长度为：%15.2f\n", disks.average_seek_length);		   // 输出保留小数点后2位小数
}
void SSTF()
{
	printf("SSTF算法：\n");
	DISK disks = {0, 0, 0, 0, 0};				  // 定义并初始化
	for (int k = 0; k < MAX_DIASKNUMBER + 1; k++) // 初始化disk数组
	{
		disk[k] = 0;
	}
	disk_currentnumber = 100;									// 当前访问的磁盘号，假设当前磁道号为100
	SCANF();													// 输入进程提出请求的磁道号
	disk[0] = disk_currentnumber;								// 把disk[0]存储为最初的磁头所在的磁道号，为后续排序和求访问的磁道和当前磁头所在的磁道距离提供方便
	qsort(disk, MAX_DIASKNUMBER + 1, sizeof(disk[0]), COMPARE); // 排序
	int m = 0, p = 0;											// m，p分别用作求第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
	SEARCH(&m, &p);												// 搜索m，p
	disks.count = MAX_DIASKNUMBER - m;							// 计算共输入了多少个磁道号
	//--SSTF核心算法
	while (TRUE)
	{
		if (m == 200)
		{
			break;
		}
		if (disk[p - 1] != 0 && ((disk[p] - disk[p - 1]) < (disk[p + 1] - disk[p]))) // 判断从当前磁道的哪头开始
		{
			disks.disk_nextnumber = disk[p - 1];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[p - 1]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[p - 1];
			disk[p] = 0;
			qsort(disk, MAX_DIASKNUMBER + 1, sizeof(disk[0]), COMPARE); // 排序
			m = 0, p = 0;												// m，p分别用作求第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
			SEARCH(&m, &p);												// 搜索m，p
		}
		else
		{
			disks.disk_nextnumber = disk[p + 1];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[p + 1]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[p + 1];
			disk[p] = 0;
			qsort(disk, MAX_DIASKNUMBER + 1, sizeof(disk[0]), COMPARE); // 排序
			m = 0, p = 0;												// m，p分别用作求第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
			SEARCH(&m, &p);												// 搜索m，p
		}
	}
	//--SSTF核心算法
	disks.average_seek_length = (float)disks.total_distence / disks.count; // 为避免丢失精度，使用强制类型转换为float型
	printf("平均寻道长度为：%15.2f\n", disks.average_seek_length);		   // 输出保留小数点后2位小数
}
void SCAN()
{
	printf("SCAN算法：\n");
	DISK disks = {0, 0, 0, 0, 0};				  // 定义并初始化
	for (int k = 0; k < MAX_DIASKNUMBER + 1; k++) // 初始化disk数组
	{
		disk[k] = 0;
	}
	disk_currentnumber = 100; // 当前访问的磁盘号，假设当前磁道号为100
	CHOOSE();
	SCANF();
	disk[0] = disk_currentnumber;
	qsort(disk, MAX_DIASKNUMBER + 1, sizeof(disk[0]), COMPARE);
	int m = 0, p = 0;				   // m，p分别用作求第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
	SEARCH(&m, &p);					   // 搜索m，p
	disks.count = MAX_DIASKNUMBER - m; // 计算共输入了多少个磁道号
	//--SCAN核心算法
	if (choice)
	{
		for (int j = p + 1; j <= MAX_DIASKNUMBER; j++)
		{

			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
		for (int j = p - 1; disk[j] != 0; j--)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n",
				   disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n",
				   disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n",
				   disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
	}
	else
	{
		for (int j = p - 1; disk[j] != 0; j--)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n",
				   disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
		for (int j = p + 1; j <= MAX_DIASKNUMBER; j++)
		{

			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n",
				   disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
	}
	//--SCAN核心算法
	disks.average_seek_length = (float)disks.total_distence / disks.count; // 为避免丢失精度，使用强制类型转换为float型
	printf("平均寻道长度为：%15.2f\n", disks.average_seek_length);		   // 输出保留小数点后2位小数
}
void CSCAN()
{
	printf("CSCAN算法：\n");
	DISK disks = {0, 0, 0, 0, 0};				  // 定义并初始化
	for (int k = 0; k < MAX_DIASKNUMBER + 1; k++) // 初始化disk数组
	{
		disk[k] = 0;
	}
	disk_currentnumber = 100; // 当前访问的磁盘号，假设当前磁道号为100
	CHOOSE();
	SCANF();
	disk[0] = disk_currentnumber;
	qsort(disk, MAX_DIASKNUMBER + 1, sizeof(disk[0]), COMPARE);
	int m = 0, p = 0;				   // m，p分别用作求第一个磁道号在数组中的位置和求最初的磁头所在的磁道号在数组中的位置
	SEARCH(&m, &p);					   // 搜索m，p
	disks.count = MAX_DIASKNUMBER - m; // 计算共输入了多少个磁道号
	//--CSCAN核心算法
	if (choice)
	{
		for (int j = p + 1; j <= MAX_DIASKNUMBER; j++)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
		for (int j = m; disk[j] != disk[p]; j++)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
	}
	else
	{
		for (int j = p - 1; disk[j] != 0; j--)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
		for (int j = MAX_DIASKNUMBER; disk[j] != disk[p]; j--)
		{
			disks.disk_nextnumber = disk[j];
			printf("当前磁头所在磁道：%12d\n", disk_currentnumber);
			printf("被访问的下一个磁道号：%8d\n", disks.disk_nextnumber);
			disks.disk_distence = abs(disk_currentnumber - disk[j]); // 有可能相减为负数，用abs化为正数
			printf("移动距离（磁道数）：%10d\n", disks.disk_distence);
			disks.total_distence += disks.disk_distence;
			printf("总移动距离：%18d\n", disks.total_distence);
			disk_currentnumber = disk[j];
		}
	}
	//--CSCAN核心算法
	disks.average_seek_length = (float)disks.total_distence / disks.count; // 为避免丢失精度，使用强制类型转换为float型
	printf("平均寻道长度为：%15.2f\n", disks.average_seek_length);		   // 输出保留小数点后2位小数
}
int main()
{
	int flag = 0; // flag作为判定标志
	while (TRUE)
	{
		if (!flag) // 第一次选择
		{
			printf("请选择退出或希望使用的磁盘调度算法：（0-退出；1-FCFS；2-SSTF；3-SCAN；4-CSCAN）\n");
			int choose = -1;	  // 用choose来选择相应的算法
			scanf("%d", &choose); //-----若输入字符会无限循环，清空缓冲区解决
			int c = 0;			  // 用于接收缓冲区内容
			while ((c = getchar()) != '\n' && c != EOF)
				;			//----清空缓冲区以后输入字符才可以不无限循环
			switch (choose) // 根据选择调用算法
			{
			case 0:
				system("pause");
				return 0;
				break;
			case 1:
				FCFS();
				flag = 1;
				break;
			case 2:
				SSTF();
				flag = 1;
				break;
			case 3:
				SCAN();
				flag = 1;
				break;
			case 4:
				CSCAN();
				flag = 1;
				break;
			default:
				printf("请按要求输入！\n");
				break;
			}
		}
		else // 后续选择
		{
			printf("退出或者继续调用磁盘调度算法？请选择：（0-退出；1-FCFS；2-SSTF；3-SCAN；4-CSCAN）\n");
			int choose = -1; // 用choose来选择相应的算法
			scanf("%d", &choose);
			int c = 0; // 用于接收缓冲区内容
			while ((c = getchar()) != '\n' && c != EOF)
				;			//----清空缓冲区以后输入字符才可以不无限循环
			switch (choose) // 根据选择调用算法
			{
			case 0:
				system("pause");
				return 0;
				break;
			case 1:
				FCFS();
				break;
			case 2:
				SSTF();
				break;
			case 3:
				SCAN();
				break;
			case 4:
				CSCAN();
				break;
			default:
				printf("请按要求输入！\n");
				break;
			}
		}
	}
}
