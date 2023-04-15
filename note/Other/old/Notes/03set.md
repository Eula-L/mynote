  
# 1. set的简介

　　关于set，必须说明的是set关联式容器。set作为一个容器也是用来存储同一数据类型的数据类型，并且能从一个数据集合中取出数据，在set中每个元素的值都 **唯一** ，而且系统能 **根据元素的值自动进行排序** （默认按键值升序排列）。应该注意的是set中数元素的值不能直接被改变。

  

　　set的含义是集合，它是一个有序的容器，里面的元素都是排序好的支持插入、删除、查找等操作，就像一个集合一样，所有的操作都是严格在log(n)时间内完成，效率非常高。是,set插入的元素不能相同，set默认是自动排序的，**键和值相等且唯一。**元素默认按升序排列。

  

　　访问元素的时间复杂度是：O(log n)

  

# 2. set的功能

  

　　特点：

  

1. set中的元素都是排好序的

2. set集合中没有重复的元素

3. 储存同一类型的数据元素（这点和vector、queue等其他容器相同）

4. 根据元素的值自动排列大小（有序性）

5. 每个元素的值都唯一（没有重复的元素）——>可以用来排序

6. 高效的插入删除操作

7. 无法直接修改元素

8. 不能使用下标法，只能使用迭代器

  

# 3. set的使用
　　头文件
```C++
#include<set>;
```
　　set具有[迭代器](https://so.csdn.net/so/search?q=%E8%BF%AD%E4%BB%A3%E5%99%A8&spm=1001.2101.3001.7020)​`set<int>::iterator i` 定义一个迭代器,名为i `可以把迭代器理解为C语言的指针`
# 4. set的常用函数

```C++

begin()     　　  ,返回set容器第一个元素的迭代器

end() 　　　　     ,返回一个指向当前set末尾元素的下一位置的迭代器.

clear()   　　     ,删除set容器中的所有的元素

empty() 　　　     ,判断set容器是否为空

max_size() 　     ,返回set容器可能包含的元素最大个数

size() 　　　　     ,返回当前set容器中的元素个数

rbegin()　　　　    ,返回的值和end()相同

rend()　　　　      ,返回的值和begin()相同

//

set<int> q;     //以int型为例 默认按键值升序

set<int,greater<int>> p;  //降序排列

int x;

q.insert(x);  //将x插入q中

q.erase(x);    //删除q中的x元素,返回0或1,0表示set中不存在x

q.clear();    //清空q

q.empty();    //判断q是否为空，若是返回1，否则返回0

q.size();    //返回q中元素的个数

q.find(x);    //在q中查找x，返回x的迭代器，若x不存在，则返回指向q尾部的迭代器即 q.end()

q.lower_bound(x); //返回一个迭代器，指向第一个键值不小于x的元素

q.upper_bound(x); //返回一个迭代器，指向第一个键值大于x的元素

  

q.rend();      //返回第一个元素的的前一个元素迭代器

q.begin();      //返回指向q中第一个元素的迭代器

  

q.end();     //返回指向q最后一个元素下一个位置的迭代器

q.rbegin();     //返回最后一个元素

  
  

```

  

# 5. set单元素应用

  

```C++

#include<iostream>

#include<set>

using namespace std;

int main()

{

  set<int> q;   //默认按升序排列

  q.insert(5);

  q.insert(5);

  q.insert(5);

  cout<<"q.size "<<q.size()<<endl;   //输出 1 ,在set插入中相同元素只会存在一个

  q.clear(); //清空set

  cout<<"q.size "<<q.size()<<"\n\n";

  q.insert(4);

  q.insert(4);

  q.insert(3);

  q.insert(3);

  q.insert(2);

  q.insert(1);

  cout<<"lower_bound "<<*q.lower_bound(3)<<endl;  //返回3

  cout<<"upper_bound "<<*q.upper_bound(3)<<"\n\n";  //返回4

  set<int>::iterator i;

  for( i=q.begin();i!=q.end();i++)   //set的遍历

    cout<<*i<<" ";           //输出1 2 3 4，可见自动按键值排序

  cout<<endl;

  q.erase(4);  //删除q中的 4

  for(i=q.begin();i!=q.end();i++)  //再次遍历set 只输出 1 2 3

    cout<<*i<<" ";

  cout<<"\n\n";

  set<int,greater<int>> p;  //降序排列

  p.insert(1);

  p.insert(2);

  p.insert(3);

  p.insert(4);

  p.insert(5);

  for(i=p.begin();i!=p.end();i++)

    cout<<*i<<" ";

  cout<<endl;

  return 0;

}

```

  

　　![](https://secure2.wostatic.cn/static/4AXQnBtDqr6xTP3cVaXrnP/1b3b81f8d1174077a22c078773afdc3a.png)​

  

# 6. set多元素应用（结构体）

  

```C++

#include<iostream>

#include<set>

using namespace std;

struct node{

  int a,b;

  bool operator< (const node W)const

  {

    return a>W.a;  //按a的值升序

  }

}t;

int main()

{

  set<node> q;

  t.a=1;

  t.b=2;

  q.insert(t);

  t.a=4;

  t.b=2;

  q.insert(t);

  t.a=3;

  t.b=5;

  q.insert(t);  

  set<node>::iterator i;

  for(i=q.begin();i!=q.end();i++)

  {

    t=*i;

    cout<<t.a<<" "<<t.b<<endl;

  }

  return 0;

}

```

  

　　‍

  

```C++

//声明

set<int> a;

//常用函数以下设 set<T> a,其中a是T类型的set容器。

a.begin() 返回指向第一个元素的迭代器

a.end() 返回指向超尾的迭代器

a.clear() 清空容器a

a.empty() 判断容器是否为空

a.size() 返回当前容器元素个数

//插入

    a.insert(x) :其中a为set<T>型容器，x为T型变量

    set<int> a={0,1,2,9};

    a.insert(6);

    for(auto it = a.begin();it != a.end();it++) cout << *it;//输出01269

//删除

    a.erase(x)：删除建值为x的元素

    a.erase(first,second)：删除first到second区间内的元素（左闭右开）

    a.erase(iterator):删除迭代器指向的元素

  

```

  

```C++

//案例

#include <bits/stdc++.h>

#include <set>

using namespace std;

int main()

{

  set<int> a;

  for (int i = 10; i > 0; i--)

    {

      a.insert(i);

      a.insert(i);

    }

  a.insert(11);

  set<int>::iterator  it = a.begin();

  for (it ; it != a.end(); it++)

    {

      cout << *it << " ";

    }

  cout << endl;

  cout << a.empty() << " " << a.size() << endl;

  a.clear();

  cout << a.empty() << " " << a.size() << endl;

}

  

```