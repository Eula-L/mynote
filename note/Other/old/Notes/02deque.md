

# 1. deque的简介
	deque(double end queue)容器为一个给定类型的元素进行线性处理，像向量一样，它能够：

  一、**优点**：

1. **快速地随机访问任一个元素** ，即支持[ ]以及at()，但是性能没有vector好。

2. **高效地插入和删除容器的尾部元素** ，但性能不及list。

3. **高效插入和删除容器的头部元素** ，因此也叫做双端队列。

4. 可以在需要的时候改变自身大小，完成了标准的C++数据结构中队列的所有功能。在vector中那样“因为旧空间不足而重新匹配一块更大的空间，然后复制元素，在释放旧的空间”这种事情在deque中不会发生。也因此，deque没有必要提供所谓的空间预留（reserved）功能。

5. deque可以包含更多的元素，其max_size可能更大，因为不止使用一块内存。

  二、  **缺点** ：

  

1. 在中间插入元素则会比较费时。

2. 迭代器不是普通指针，是特殊的智能指针，它需要在不同的块中跳转。

3. deque的元素存取和迭代器操作会稍微慢一些，因为deque的内部结构多了一个间接过程，，效率不如vector。对deque进行的排序操作，为了最高效率，可将deque先完整复制到一个vector身上，将vector排序后（利用STL的sort算法），再复制回deque。

4. deque不支持对容量和内存分配时机的控制。

5. 在除了首尾两端的其他地方插入和删除元素，都将会导致指向deque元素的任何pointers、references、iterators失效。不过，deque的内存重分配优于vector，因为其内部结构显示不需要复制所有元素。

6. deque不提供容量操作：capacity()和reverse()，但是vector可以。

  三、 原理

  

　　![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/image.png)​

  

# 2. 使用

  

```C++

#include<deque>  // 头文件

deque<type> deq;  // 声明一个元素类型为type的双端队列que

deque<type> deq(size);  // 声明一个类型为type、含有size个默认值初始化元素的的双端队列que

deque<type> deq(size, value);  // 声明一个元素类型为type、含有size个value元素的双端队列que

deque<type> deq(mydeque);  // deq是mydeque的一个副本

deque<type> deq(first, last);  // 使用迭代器first、last范围内的元素初始化deq

  

```

  

```C++

deq[ ]：用来访问双向队列中单个的元素。

deq.front()：返回第一个元素的引用。

deq.back()：返回最后一个元素的引用。

deq.push_front(x)：把元素x插入到双向队列的头部。

deq.pop_front()：弹出双向队列的第一个元素。

deq.push_back(x)：把元素x插入到双向队列的尾部。

deq.pop_back()：弹出双向队列的最后一个元素。

  

```

  

```C++

//3.遍历

    //下标法

    int length = vec1.size();

    for(int i=0; i<length; i++)

    {

        cout<<vec1[i];

    }

    cout<<endl<<endl;

    //迭代器法

    vector<int> :: iterator iter = vec1.begin();

    for( ; iter != vec1.end(); iter++)

    {

        cout<<*iter;

    }

  

```

  

# 3. 案例

  

```C++

#include<iostream>

#include<stdio.h>

#include<deque>

using namespace std;

int main(void)

{

  int i;

  int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

  deque<int> q;

  for (i = 0; i <= 9; i++)

  {

    if (i % 2 == 0)

      q.push_front(a[i]);

    else

      q.push_back(a[i]);

  }                                  /*此时队列里的内容是: {8,6,4,2,0,1,3,5,7,9}*/

  q.pop_front();

  printf("%d\n", q.front());    /*清除第一个元素后输出第一个(6)*/

  q.pop_back();

  printf("%d\n", q.back());     /*清除最后一个元素后输出最后一个(7)*/

  deque<int>::iterator it;

  for (it = q.begin(); it != q.end(); it++) {

    cout << *it << '\t';

  }

  cout << endl;

  system("pause");

  return 0;

}

```