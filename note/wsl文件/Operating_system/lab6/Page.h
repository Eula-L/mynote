// Page.h
#ifndef _PAGE_H
#define _PAGE_H

class CPage // 进程使用的页面
{
public:
	int m_nPageNumber,	   // 页号
		m_nPageFaceNumber, // 对应的物理内存页号，初始为INVALID
		m_nCounter,		   // 计数
		m_nTime;		   // 时间信息
};
#endif
