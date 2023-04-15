

# 1. stack的简介

  

　　stack翻译为 **栈** 。

  

1. **后进先出** , **先进后出**

2. 不允许遍历

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755835493.png)
  

# 2. stack的功能

  

　　**特点：**

  

　　由于栈是一种有序列表，故可以使用数组模拟。

  

# 3. stack的使用

  

　　头文件：

  

```C++

#include<stack>;//注意，STL头文件没有扩展名.h

  

```

  

　　map对象是模板类，需要关键字和存储对象两个模板参数：

  

```C++

stack<typename> name;//这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.

```

  

# 4. stack容器内元素的访问

  

　　由于栈(stack)本身就是一种后进先出的数据结构，在STL的 stack中只能通过top()来访问栈顶元素

  

```C++

#include<cstdio>

#include<stack>

using namespace std;

int main(){

  stack<int> st;

  for(int i=1;i<=5;i++){

    st.push(i);    //push(i)将i压入栈

  }

  printf("%d\n",st.top());   //top()取栈顶元素

  return 0;

}

```

  

# 5. stack常用函数实例解析

  

1. push()  

    push(x)将x入栈，时间复杂度为O(1)，实例见“ stack容器内元素的访问”。

2. top()  

    top()获得栈顶元素，时间复杂度为O(1)，实例见“ stack容器内元素的访问”。

3. pop()  

    pop()用以弹出栈顶元素，时间复杂度为O(1)。

  

```C++

#include<cstdio>

#include<stack>

using namespace std;

int main(){

  stack<int> st;

  for(int i=1;i<=5;i++){

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

  }

  for(int i=1;i<=3;i++){

    st.pop();    //pop()将栈顶元素出栈，即将5 4 3 依次出栈

  }

  printf("%d\n",st.top());   //top()取栈顶元素

  return 0;

}

```

  

　　运行结果：

  ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755882989.png)
  

4. empty()  

    empty()可以检测stack是否为空，返回true为空，返回false为非空，时间复杂度为O(1)。

  

　　程序代码：

  

```C++

#include<cstdio>

#include<stack>

using namespace std;

int main(){

  stack<int> st;

  printf("%d\n",st.empty()); //true=1;false=0

  for(int i=1;i<=5;i++){

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

  }

  printf("%d\n",st.empty()); //true=1;false=0

  return 0;

}

```

  

　　运行结果：

  ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755918123.png)
  

5. size()  

    size()返回stack内元素的个数，时间复杂度为O(1)。

  

　　程序代码：

  

```C++

#include<cstdio>

#include<stack>

using namespace std;

int main(){

  stack<int> st;

  for(int i=1;i<=5;i++){

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

  }

  printf("%d\n",st.size());

  return 0;

}

```

  

　　运行结果：

  
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755931421.png)
  

　　注意：  

在使用pop()和top()函数之前必须先使用empty()函数判断栈是否为空。