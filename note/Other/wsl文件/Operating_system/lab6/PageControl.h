// PageControl.h

#ifndef _PAGECONTROL_H
#define _PAGECONTROL_H
class CPageControl // 分配给进程的物理内存页面
{
public:
	int m_nPageNumber;			 // m_nPageNumber表示物理内存页号（帧号）
	int m_nPageFaceNumber;		 // m_nPageFaceNumber表示物理内存的页号
	class CPageControl *m_pNext; // 指示下一个页面
};
#endif
