// Memory.h
#ifndef _MEMORY_H
#define _MEMORY_H

class CMemory
{

public:
	CMemory();							  // 构造函数
	void initialize(const int nTotal_pf); // 初始化函数
	void FIFO(const int nTotal_pf);
	void LRU(const int nTotal_pf); // LRU算法，参数表示分配的内存页面个数
								   // void NUR(const int nTotal_pf);
private:
	vector<CPage> _vDiscPages;					 // 进程使用的页向量,包含该进程空间内的所有页
	vector<CPageControl> _vMemoryPages;			 // 为进程分配的物理内存页向量
	CPageControl *_pFreepf_head;				 // 空闲物理页头指针 用于LRU算法
	CPageControl *_pBusypf_head, *_pBusypf_tail; // 已使用页面头指针，尾指针，用于FIFO算法
	vector<int> _vMain, _vPage;					 //_vMain表示某进程随机产生的指令序列
												 //_vPage表示待处理指令对应的页号
	int _nDiseffect;							 // 换入页面次数
};

CMemory::CMemory() : _vDiscPages(TOTAL_VP),		// 32
					 _vMemoryPages(TOTAL_VP),	// 32
					 _vMain(TOTAL_INSTRUCTION), // 320
					 _vPage(TOTAL_INSTRUCTION)
{
	int S, i, nRand;

	// 通过随机数产生一个指令序列(实际上是指令的逻辑地址序列)，共320条指令。指令的地址按下述原则生成：
	// A：50%的指令是顺序执行的
	// B：25%的指令要实现向前跳转，均匀分布在前地址部分
	// C：25%的指令要实现向后跳转，均匀分布在后地址部分

	// 函数void srand(unsigned seed)；参数seed是rand()的种子，用来初始化rand()的起始值。
	// 由于每次运行时进程号不同，故可用来作为初始化随机数队列的“种子”
	srand(getpid() * 10);
	// 函数int rand(void)；从srand (seed)中指定的seed开始，返回一个[seed, RAND_MAX（0x7fff）)间的随机整数。
	nRand = rand() % 32767;
	// 计算第一条指令的地址S
	S = (float)319 * nRand / 32767 + 1;
	for (i = 0; i < TOTAL_INSTRUCTION; i += 4) // 产生指令序列
	{
		// 地址S存入_Main[i]
		_vMain[i] = S;
		// 顺序执行S的下一条指令
		_vMain[i + 1] = _vMain[i] + 1;
		// 计算S的一条任意的前地址指令的地址S'属于[0，S+1],并存入_Main[i+2],表示向前跳转
		nRand = rand() % 32767;
		_vMain[i + 2] = (float)_vMain[i] * nRand / 32767;
		// 顺序执行S'下一条指令
		_vMain[i + 3] = _vMain[i + 2] + 1;
		// 计算S'的一条任意的后指令地址S属于[S'+1,319],表示向后跳转
		nRand = rand() % 32767;
		S = (float)nRand * (318 - _vMain[i + 2]) / 32767 + _vMain[i + 2] + 2;
	}
	// 将指令序列变成页地址流
	// 设：页面大小为1K；
	// 用户内存容量4页到32页；
	// 用户虚存容量为32K。
	// 在用户虚存中，按每K存放10条指令排列虚存地址，即320条指令在虚存中的存放方式为：
	// 第 0 条-第 9 条指令为第0页（对应逻辑地址为[0，9]）
	// 第10条-第19条指令为第1页（对应逻辑地址为[10，19]）
	// ………………………………
	// 第310条-第319条指令为第31页（对应逻辑地址为[310，319]）
	// 按以上方式，用户指令可组成32页。
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		_vPage[i] = _vMain[i] / 10;
		_vPage[i] %= 32;
	}
}
void CMemory::initialize(const int nTotal_pf) // 初始化，参数表示分配的内存页面个数
{
	int ix;
	_nDiseffect = 0;
	for (ix = 0; ix < _vDiscPages.size(); ix++)
	{
		_vDiscPages[ix].m_nPageNumber = ix;
		_vDiscPages[ix].m_nPageFaceNumber = INVALID;
		_vDiscPages[ix].m_nCounter = 0;
		_vDiscPages[ix].m_nTime = -1;
	}
	for (ix = 1; ix < nTotal_pf; ix++)
	{
		_vMemoryPages[ix - 1].m_pNext = &_vMemoryPages[ix];
		_vMemoryPages[ix - 1].m_nPageFaceNumber = ix - 1;
	}
	_vMemoryPages[nTotal_pf - 1].m_pNext = NULL;
	_vMemoryPages[nTotal_pf - 1].m_nPageFaceNumber = nTotal_pf - 1;
	_pFreepf_head = &_vMemoryPages[0];
}
void CMemory::FIFO(const int nTotal_pf)
{
	int i;
	CPageControl *p;
	initialize(nTotal_pf);
	_pBusypf_head = _pBusypf_tail = NULL;
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (_vDiscPages[_vPage[i]].m_nPageFaceNumber == INVALID)
		{
			_nDiseffect += 1;
			if (_pFreepf_head == NULL) // no empty pages
			{
				p = _pBusypf_head->m_pNext;
				_vDiscPages[_pBusypf_head->m_nPageNumber].m_nPageFaceNumber = INVALID;
				_pFreepf_head = _pBusypf_head;
				_pFreepf_head->m_pNext = NULL;
				_pBusypf_head = p;
			}
			p = _pFreepf_head->m_pNext;
			_pFreepf_head->m_pNext = NULL;
			_pFreepf_head->m_nPageNumber = _vPage[i];
			_vDiscPages[_vPage[i]].m_nPageFaceNumber = _pFreepf_head->m_nPageFaceNumber;
			if (_pBusypf_tail == NULL)
				_pBusypf_head = _pBusypf_tail = _pFreepf_head;
			else
			{
				_pBusypf_tail->m_pNext = _pFreepf_head;
				_pBusypf_tail = _pFreepf_head;
			}
			_pFreepf_head = p;
		}
	}
	cout << "FIFO: " << 1 - (float)_nDiseffect / 320 << "\t";
}
void CMemory::LRU(const int nTotal_pf) // LRU算法实现，参数表示分配的内存页面个数
{
	int i, j, nMin, minj, nPresentTime(0);
	initialize(nTotal_pf);
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (_vDiscPages[_vPage[i]].m_nPageFaceNumber == INVALID)
		{
			_nDiseffect++;
			if (_pFreepf_head == NULL)
			{
				nMin = 32767;
				for (j = 0; j < TOTAL_VP; j++) // get the subscribe of the least used page
											   // after the recycle iMin is the number of times
											   // used of the least used page while minj is its subscribe
					if (nMin > _vDiscPages[j].m_nTime && _vDiscPages[j].m_nPageFaceNumber != INVALID)
					{
						nMin = _vDiscPages[j].m_nTime;
						minj = j;
					}
				_pFreepf_head = &_vMemoryPages[_vDiscPages[minj].m_nPageFaceNumber];
				_vDiscPages[minj].m_nPageFaceNumber = INVALID;
				_vDiscPages[minj].m_nTime = -1;
				_pFreepf_head->m_pNext = NULL;
			}
			_vDiscPages[_vPage[i]].m_nPageFaceNumber = _pFreepf_head->m_nPageFaceNumber;
			_vDiscPages[_vPage[i]].m_nTime = nPresentTime;
			_pFreepf_head = _pFreepf_head->m_pNext;
		}
		else
			_vDiscPages[_vPage[i]].m_nTime = nPresentTime;
		nPresentTime++;
	}
	cout << "LRU: " << 1 - (float)_nDiseffect / 320;
}
#endif
