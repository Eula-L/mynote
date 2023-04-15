

# 06list

  

# 1.list的介绍

  

　　STL链表是序列性容器的模板类，它将其元素保持在线性排列中，链式结构，并允许在序列中的任何位  

置进行有效的插入和删除。

  

## 链表

  

　　优点：

  

1. 与向量(vector)相比, 它允许快速的插入和删除。

2. 时间复杂度O(1)

3. 动态分配内存，不会造成内存的浪费和溢出

  

　　缺点：

  

1. 遍历慢，

2. 随机访问却比较慢，

3. 占用空间大,

4. 查找的效率为O()

  

　　List是stl实现的双向且循环的链表。

  

　　迭代器，只支持前移和后移，属于双向迭代器。

  

　　**性质：Lise插入和删除操作不会令原有的list迭代器失效，这在vector中是不成立的。**

  

# 2. list的构造函数

  

```C++

list<T> lst;//list采用模板类实现，对象的默认构造形式

list(beg,end);//构造函数将[beg,end]区间中的元素给本身

list (n,elem);//构造函数将n个elem拷贝给本身

list(const list &lst);//拷贝构造函数

  

```

  

```C++

#include<iostream>

using namespace std;

#include<list>

//list函数构造函数

void printList(const list<int>&L)

{

    for(list<int>::const_iterator it = L.begin();it!=L.end();it++)

    {

        cout<<*it<<" ";

    }

}

void test01()

{

    //创建list函数

    list<int>L1;//默认函数

    //添加数据

    L1.push_back(10);

    L1.push_back(20);

    L1.push_back(30);

    L1.push_back(40);

    L1.push_back(50);

    printList(L1);

}

int main ()

{

    test01();

    system("pause");

    return 0;

}

```

  

# 3.list的赋值和交换

  

```C++

assign(beg,end);//将[beg,end]区间的数据赋值给本身

assign(n,elem);//将n个elem拷贝赋值给本身

list& operator = (const list &lst);//重载符号操作符

swap(lst);//将lst与本身的元素互换

```

  

```C++

#include<iostream>

using namespace std;

#include<list>

//list函数构造函数

void printList(const list<int>&L)

{

    for(list<int>::const_iterator it = L.begin();it!=L.end();it++)

    {

        cout<<*it<<" ";

    }

    cout<<endl;

}

  

void test01()

{

    //创建list函数

    list<int>L1;//默认函数

  

    //添加数据

    L1.push_back(10);

    L1.push_back(20);

    L1.push_back(30);

    L1.push_back(40);

    L1.push_back(50);

    printList(L1);

    list<int>L2;

    L2=L1;//operator= 赋值

    printList(L2);

  

    list<int>L3;

    L3.assign(L2.begin(),L2.end());

    printList(L3);

  

    list<int>L4;

    L4.assign(10,100);

    printList(L4);

  

}

  

int main ()

{

    test01();

    system("pause");

    return 0;

}

```

  

　　begin()返回的是第一个元素的指针（可以理解为是指针），但是end()返回的不是最后一个元素的指针而是最后一个元素下一个位置的指针。仅仅用作标记结尾的作用，是无效节点

  

```cpp

//cout << *lst.end() << " ";//运行会出错

cout << *--lst.end() << endl;

```

  

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/8d98764588e79cb5cd5b6c1643c687e.png)​

  

## 方法

  

　　front() 获取头节点元素

  

　　back() 获取尾节点元素

  

　　size()  获取长度

  

　　empty()  判空

  

　　clear()