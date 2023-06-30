#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;

#define INVALID -1
const int TOTAL_INSTRUCTION(320); // 总共使用页面次数320次
const int TOTAL_VP(32);			  // 内存分配的页面数32个

#include "Page.h"
#include "PageControl.h"
#include "Memory.h"

int main()
{
	int i;
	CMemory a;
	for (i = 4; i <= 32; i++)
	{
		a.FIFO(i);
		a.LRU(i);
		// a.NUR(i);
		// a.OPT(i);
		cout << "\n";
	}
	return 0;
}
