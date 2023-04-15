
# 01vector

```C++

swap(arr[1],arr[2]);//交换

reverse(arr.begin(),arr.end());//反转

sort(arr.begin(),arr.end());//排序，并返回一个新的数组end的指针  

int newlenght = unique(arr.begin(),arr.end())-arr.begin();//unique去重

for(int i=0;i<newlenght;i++)

{

  cout<<arr[i]<<endl;

}

//二分查找->排好序的数组

int n = lower_bound(arr.begin(),arr.begin()+length,8)-arr.begin();//查找8返回下标 （lower_bound是返回第一次出现的指针位置） （upper_bound是返回第一次出现的指针位置 ）

  

```

  

# 1. vector的简介

  

　　vector是一段连续的内存地址，基于数组实现，管理器可以动态改变对象长度，在 vector:容器中有以下几个关于大小的函数:

  

1. size():返回容器的大小

2. max_size():返回容器扩展极限的最大存储的元素数量

3. empty():判断容器是否为空

4. capacity():返回容器当前能够容纳的元素数量

  

# 2. 使用

  

```C++

//1.初始化

vocter<int> vec1;

vocter<int> vec2(10);//10个值为0的元素

vocter<int> vec3(10,4);//10个值为4的元素

  

```

  

```C++

//2.常用操作方法

    vec1.push_back(100); //尾部添加元素

    int size = vec1.size(); //元素个数

    bool isEmpty = vec1.empty(); //判断是否为空

    cout<<vec1[0]<<endl; //取得第一个元素

    vec1.insert(vec1.end(), 5, 3); //从vec1.back位置插入5个值为3的元素

    vec1.pop_back(); //删除末尾元素

    vec1.erase(vec1.begin(), vec1.begin() + 2); //删除vec1[0]-vec1[2]之间的元素，不包括vec1[2]，其他元素前移

    vec1.erase(vec1.begin()+i);//删除第i个元素，其他元素前移

    cout<<(vec1 == vec2) ? true : false; //判断是否相等==、!=、>=、<=

    vector<int> :: iterator iter = vec1.begin(); //获取迭代器首地址

    vec1.clear(); //清空元素,其他元素前移

```

  

　　<div contenteditable="false" spellcheck="false"></div>

  

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

  
  

  //vector<int>v1;

  //vector<int>v2(10);

  //vector<int>v3(10,1);

  vector<int>v(10, 1);

  for (int i = 0; i < v.size(); i++) {

    v[i] = i+1;

  }

  cout << endl;

  v.pop_back();

  for (int i = 0; i < v.size(); i++) {

    cout << v[i] << " ";

  }

  cout << endl;

  v.erase(v.begin(), v.begin() + 2);

  for (int i = 0; i < v.size(); i++) {

    cout << v[i] << " ";

  }

  vector<int>v2;

  for (int i = 0; i < v2.size(); i++) {

    v2[i] = i + 1;

  }

  vector<int>v3;

  for (int i = 0; i < v3.size(); i++) {

    v3[i] = i + 1;

  }

  cout << endl;

  if (v3 == v2) {

    cout << "相同" << endl;

  }

  else {

    cout << "不相同" << endl;

  }

  v.clear();

  cout << v.size();

```

  

# 3. 案例

  

```C++

// 案例

#include<bits/stdc++.h>

#include<vector>

using namespace std;

int main()

{

  vector<int> vec1;

  for(int i=0;i<10;i++)

  {

    vec1.push_back(i);

   }  

   cout<<vec1[3]<<endl;

   vector<int>::iterator it = vec1.begin();

   for(it;it!=vec1.end();it++)

   {

     cout<<*it;

   }

   vec1.pop_back();

   cout<<endl<<vec1.size();

   cout<<endl<<vec1.empty();

   vec1.clear();

   cout<<endl;

   cout<<vec1.size();

   cout<<endl<<vec1.empty()<<endl;

   cout<<vec1[3]<<endl;

}

```

  

　　‍