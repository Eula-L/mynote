// 短进程优先调度算法
#include <stdlib.h>
#include <stdio.h>

// 定义一个结构体：PCB

typedef struct
{
	char name[10];
	float arrivetime;
	float servicetime;
	float starttime;
	float finishtime;
	float zztime;
	float dqzztime;
} pcb;

//***输入进程信息，将N个进程的信息写入pcb型数组***
void input(pcb *p, int N)
{
	int i;
	printf("\n");
	printf("请输入进程的名字  到达时间  服务时间:  (例如: a 0 100)\n");

	for (i = 0; i <= N - 1; i++)
	{
		printf("请输入进程%d的信息：", i + 1);
		scanf("%s", &p[i].name);
		scanf("%f", &p[i].arrivetime);
		scanf("%f", &p[i].servicetime);
	}
}

//***优先级排序***
void sort(pcb *p, int N)
{
	/*
	1、对pcb型数组中的元素进行一个简单的排序
	找到优先级最高的进程
	并把其他进程也进行简单排序，方便后续工作
	*/

	// 排序: N次循环,每次找到从i到N-1中优先级最高的进程，放到p[i]
	for (int i = 0; i <= N - 1; i++)
	{
		// 循环比较剩余的变量    //排序后：从0~N-1  arrivetime增加 ， arrivetime相同时， servicetime短的优先
		for (int j = i + 1; j < N; j++)
		{
			if (p[i].arrivetime > p[j].arrivetime || (p[i].arrivetime == p[j].arrivetime && p[i].servicetime > p[j].servicetime))
			{
				// p[j]的优先级高于p[i],因此把p[j]放到p[i]
				pcb temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}

	/*
	2、每个进程运行完成之后，找到当前时刻已经到达的最短进程
	P[0]优先级最高，p[0].finishtime=p[0].arrivetime+p[0].servicetime
	m!=0时：p[m].finishtime=p[m-1].finishtime+p[m].servicetime
	*/

	for (int m = 0; m < N - 1; m++)
	{
		if (m == 0)
			p[m].finishtime = p[m].arrivetime + p[m].servicetime;
		else
			p[m].finishtime = ((p[m - 1].finishtime >= p[m].arrivetime) ? p[m - 1].finishtime : p[m].arrivetime) + p[m].servicetime;

		//(1)找到p[m].finishtime时刻哪些进程已经到达
		int i = 0; // i统计 p[m].finishtime时刻有几个进程已经到达
		// 从下一个进程p[m+1]开始寻找
		for (int n = m + 1; n <= N - 1; n++)
		{
			if (p[n].arrivetime <= p[m].finishtime)
				i++;
			else
				break;

			/*由于在第1步已经对进程按照到达时间进行了排序
			  故：当p[n].arrivetime > p[m].finishtime时，
				  说明p[n]进程和其后面的其他进程都未到达。
			i的值为p[m].finishtime时刻已经到达的进程数目。
		   */
		}

		//(2)找到p[m].finishtime时刻已经到达的最短进程
		float min = p[m + 1].servicetime; // next进程服务时间为p[m+1].servicetime （初值）
		int next = m + 1;				  // next进程为m+1 （初值）
		// p[m+1]至p[m+i]这i个已到达进程中找到最短进程
		for (int k = m + 1; k < m + i; k++) // k为m+1 ~ m+i-1
		{
			// min的初值是p[m+1].servicetime, k+1为m+2 ~m+i
			if (p[k + 1].servicetime < min)
			{
				min = p[k + 1].servicetime;
				next = k + 1;
			}
		}

		//(3)把最短进程放在p[m+1]进程处
		pcb temp;
		temp = p[m + 1];
		p[m + 1] = p[next];
		p[next] = temp;
	}
}

//***运行***
void run(pcb *p, int N)
{
	int k;
	// 计算各进程的开始时间和结束时间
	for (k = 0; k <= N - 1; k++)
	{
		if (k == 0) // 第1个进程
		{
			p[k].starttime = p[k].arrivetime; // 第1个进程到达之后即可执行
			p[k].finishtime = p[k].starttime + p[k].servicetime;
		}
		else
		{
			p[k].starttime = (p[k - 1].finishtime >= p[k].arrivetime) ? p[k - 1].finishtime : p[k].arrivetime;
			p[k].finishtime = p[k].starttime + p[k].servicetime;
		}
	}

	// 计算各进程的周转时间和带权周转时间
	for (k = 0; k <= N - 1; k++)
	{
		p[k].zztime = p[k].finishtime - p[k].arrivetime;
		p[k].dqzztime = p[k].zztime / p[k].servicetime;
	}
}

//***显示***
void Print(pcb *p, int N)
{
	int k;
	printf("调用最短进程优先算法以后进程运行的顺序是: ");
	printf("%s", p[0].name);
	for (k = 1; k < N; k++)
	{
		printf("-->");
		printf("%s", p[k].name);
	}

	printf("\n");
	printf("具体进程调度信息:\n");
	printf("进程名  到达时间  服务时间  开始时间  结束时间  周转时间  带权周转时间\n");
	for (k = 0; k <= N - 1; k++)
	{
		printf("%4s", p[k].name);
		//%m.nf：输出共占m列，其中有n位小数，如数值宽度小于m左端补空格
		printf("%10.3f", p[k].arrivetime);
		printf("%10.3f", p[k].servicetime);
		printf("%10.3f", p[k].starttime);
		printf("%10.3f", p[k].finishtime);
		printf("%10.3f", p[k].zztime);
		printf("%10.3f\n", p[k].dqzztime);
	}
}

//***短进程优先***
void sjff(pcb *p, int N)
{
	sort(p, N);
	run(p, N);
	Print(p, N);
	int k;
	float Attime = 0;  // 平均周转时间
	float AQttime = 0; // 平均带权周转时间
	for (k = 0; k <= N - 1; k++)
	{
		Attime += p[k].zztime;
		AQttime += p[k].dqzztime;
	}
	Attime = Attime / N;
	AQttime = AQttime / N;
	printf("调用短进程优先算法的平均周转时间为:");
	printf("%.3f\n", Attime);
	printf("调用短进程优先算法的平均带权周转时间为:");
	printf("%.3f\n", AQttime);
}

//***主函数***
int main()
{
	// 定义一个pcb型数组a
	pcb a[100];
	int N; // 进程数目
	printf("\n");
	printf("\n");
	printf("<<----------******短进程优先调度算法******---------->>");
	printf("\n");
	printf("输入进程数目:");
	scanf("%d", &N);
	input(a, N);
	sjff(a, N);
	return 0;
}
