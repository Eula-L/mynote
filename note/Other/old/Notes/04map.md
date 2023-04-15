
# 1. map的简介
　　map是STL的一个关联容器，它提供一对一的[hash](https://blog.csdn.net/guidao13/article/details/84104526?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165028169216780271584890%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165028169216780271584890&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-84104526.142%5Ev9%5Econtrol,157%5Ev4%5Econtrol&utm_term=hash&spm=1018.2226.3001.4187)
* 第一个可以称为关键字(key)，每个关键字只能在map中出现一次；
* 第二个可称为该关键字的值(value)；
如果说set对应数学中的“集合”，那么map对应的就是“映射”。map是一种key-value型容器，其中key是关键字，起到索引作用，而value就是其对应的值。与set不同的是它支持下标访问。头文件是<map>。

map以模板(泛型)方式实现，可以存储任意类型的数据，包括使用者自定义的数据类型。Map主要用于资料一对一映射(one-to-one)的情況，map內部的实现自建一颗红黑树，这颗树具有对数据自动排序的功能。在map内部所有的数据都是有序的，后边我们会见识到有序的好处。比如一个班级中，每个学生的学号跟他的姓名就存在著一对一映射的关系。


# 2. map的功能

  特点:
	  自动建立key-value的对应，key和value可以是任何你需要的类型，包括自定义类型
	  
	  增加和删除节点对迭代器的影响很小(高效的插入与删除)
	  
	  可以根据key修改value的记录
	  
	  支持下标[]操作
	  
	  快速的查找（同set）

  

# 3. map的使用
　头文件：
```C++
#include<map>;//注意，STL头文件没有扩展名.h
```

map对象是模板类，需要关键字和存储对象两个模板参数：

std:map<int, string> personnel;//这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.

为了使用方便，可以对模板类进行一下类型定义，

typedef map<int,CString> UDT_MAP_INT_CSTRING;

UDT_MAP_INT_CSTRING enumMap;


  

# 4. map的构造函数

  

　　map共提供了6个构造函数，这块涉及到**内存分配器**这些东西，略过不表，在下面我们将接触到一些map的构造方法，这里要说下的就是，我们通常用如下方法构造一个map：

  

```C++

map<int, string> mapStudent;

```

  

# 5. 插入元素

  

　　首先，定义一个map对象

  

```C++

map<int,string> mapStudent;

```

  

　　第一种，使用**insert**函数插入**[pair]()**数据

  

```C++

mapStudent.insert(pair<int, string>(000, "student_zero"));

```

  

　　第二种，使用**insert**函数插入**[value_type]()**数据

  

```C++

mapStudent.insert(map<int, string>::value_type(001, "student_one"));

```

  

　　第三种，用**array**方式插入

  

```C++

mapStudent[123] = "student_first";

mapStudent[456] = "student_second";

```

  

　　以上三种用法，虽然都可以实现数据的插入，但是它们是有区别的，当然了第一种和第二种在效果上是完成一样的，**用insert函数插入数据，**在数据的插入上涉及到**集合的唯一性**这个概念，即当map中有这个关键字时，insert操作是不能在插入数据的，但是用**数组方式**就不同了，它可以 **覆盖以前该关键字对应的值** ，用程序说明如下：

  

```C++

mapStudent.insert(map<int, string>::value_type (001, "student_one"));

mapStudent.insert(map<int, string>::value_type (001, "student_two"));

```

  

　　上面这两条语句执行后，map中001这个关键字对应的值是“student_one”，**第二条语句并没有生效，**那么这就涉及到我们怎么知道insert语句是否插入成功的问题了，可以用pair来获得是否插入成功，程序如下：

  

```C++

// 构造定义，返回一个pair对象

pair<iterator,bool> insert (const value_type& val);

pair<map<int, string>::iterator, bool> Insert_Pair;

Insert_Pair = mapStudent.insert(map<int, string>::value_type (001, "student_one"));

if(!Insert_Pair.second)

    cout << ""Error insert new element" << endl;

```

  

　　我们通过pair的第二个变量来知道是否插入成功，它的第一个变量返回的是一个map的迭代器，如果插入成功的话Insert_Pair.second应该是true的，否则为false。

  

# 6. 查找元素

  

　　当所查找的关键key出现时，它返回数据所在对象的位置，如果沒有，返回iter与end函数的值相同。

  

```C++

//find返回迭代器指向当前查找元素的位置否则返回map::end()位置

iter = mapStudent.find("123");

if(iter != mapStudent.end())

       cout<<"Find, the value is"<<iter->second<<endl;

else

   cout<<"Do not Find"<<endl;

```

  

# 7. 删除与清空元素

  

　　迭代器**删除**

  

```C++

iter = mapStudent.find("123");

mapStudent.erase(iter);

  

```

  

　　关键字**删除**

  

```C++

int n = mapStudent.erase("123"); //如果刪除了会返回1，否则返回0

```

  

　　使用迭代器**清空**

  

```C++

mapStudent.erase(mapStudent.begin(), mapStudent.end());

  

```

  

　　使用关键字**清空**

  

```C++

mapStudent.clear();

```

  

# 8. map的大小

  

```C++

int nSize = mapStudent.size();

```

  

# 9. map的基本操作函数

  

```C++

begin()         返回指向map头部的迭代器

clear(）        删除所有元素

count()         返回指定元素出现的次数, (帮助评论区理解： 因为key值不会重复，所以只能是1 or 0)

empty()         如果map为空则返回true

end()           返回指向map末尾的迭代器

equal_range()   返回特殊条目的迭代器对

erase()         删除一个元素

find()          查找一个元素

get_allocator() 返回map的配置器

insert()        插入元素

key_comp()      返回比较元素key的函数

lower_bound()   返回键值>=给定元素的第一个位置

max_size()      返回可以容纳的最大元素个数

rbegin()        返回一个指向map尾部的逆向迭代器

rend()          返回一个指向map头部的逆向迭代器

size()          返回map中元素的个数

swap()           交换两个map

upper_bound()    返回键值>给定元素的第一个位置

value_comp()     返回比较元素value的函数

(*it)->first     key

(*it)->second    value

```

  

# 10. 案例

  

```C++

#include <bits/stdc++.h>

#include <map>

  

using namespace  std;

int main()

{

  map<char, int> m;

  

  string str = "flkjashfewhklbflacb455";

  

  for (int i = 0; str[i]; i++)

    {

      m[str[i]]++;

    }

  
  

  map<char, int>::iterator it = m.begin();

  
  

  for (it; it != m.end(); it++)

    {

      cout << it->first << " " << it->second << endl;

    }

  

  cout << m.empty() << " " << m.size() << endl;

  m.clear();

  cout << m.empty() << " " << m.size() << endl;

  

}

  

```