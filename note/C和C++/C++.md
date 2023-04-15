2020/04/09重构
# **01面向对象**
## 基本概念
面向对象程序设计（Object-Oriented Programming，OOP）是一种新的程序设计范型。程序设计范型是指设计程序的规范、模型和风格，它是一类程序设计语言的基础。
### 面向过程
面向过程程序设计范型是使用较广泛的面向过程性语言，其主要特征是：程序由过程定义和过程调用组成（简单地说，过程就是程序执行某项操作的一段代码，函数就是最常用的过程）。
面向对象程序的基本元素是对象，面向对象程序的主要结构特点是：第一，程序一般由类的定义和类的使用两部分组成；第二，程序中的一切操作都是通过向对象发送消息来实现的，对象接收到消息后，启动有关方法完成相应的操作。a

### 面向过程和面向对象比较
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662108869979.png)
  ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662108808933.png)

### 基本特征
（抽象）、封装、继承、多态。

### 类的构成
类中内容包括数据（数据成员）和函数（成员函数）
![[类的组成部分.png]]
按照访问权限划分：公有、保护、私有
```cpp
class 类名{
    public：
        公有数据成员;
        公有成员函数;
    protected:
        保护数据成员;
        保护成员函数;
    private:
        私有数据成员;
        私有成员函数;
};
```
### 注意
1. 类名一般 **大写C** 开头
2. 类成员属性一般以  **m_ + 数据类型 + 变量名** ，一般是私有的
3. 类成员函数一般是公有的,作为公共接口，可以在对类内私有数据做修改时，进行限制，避免随意修改
4. 定义一个对象（类的实例化）,这时才会为对应的这个类开辟空间
5. 类声明中的关键字private、protected、public可以任意顺序出现。
6. 若私有部分处于类的第一部分时，关键字private可以省略。这样，如果一个类体中没有一个访问权限关键字，则其中的数据成员和成员函数都默认为私有的。
7. 不能在类声明中给数据成员赋初值。
```cpp
#include<iostream>
#include<string>
using namespace std;

class CPeople{//类名一般大写C开头
public:
	string m_strName;//类成员属性一般以 m_ + 数据类型 + 变量名
	bool m_bSex;
	int m_nAge;

	void run() {
		cout << m_strName << "在跑步" << endl;
	}
};


int main()
{
	CPeople peo;//定义一个对象（类的实例化）,这时才会为CPeople这个类开辟空间
	peo.m_strName = "小明";
	cout << peo.m_strName << endl;


	return 0;
}
```
### 访问修饰符
访问修饰符(3种)：描述了类中的成员的适用范围，即访问控制（访问权限） 
1. pub1ic:修饰的成员在类内、类外只要能定义对象的地方都可以使用
2. protected:修饰的成员在类内和继承中的子类中可以使用
3. private:修饰的成员只能在类内去使用。
```cpp
class CPeople{//类名一般大写C开头

public:
	string m_strName;//类成员属性一般以 m_ + 数据类型 + 变量名
protected:
	bool m_bSex;
private:
	int m_nAge;
public:
	void run() {
		cout << m_strName << "在跑步" << endl;
	}
	//---公共接口------
	/*
	公共接口存在的意义，可以在对类内私有数据做修改时，进行限制，避免随意修改
	*/
	int GetAge()
	{
		return m_nAge;
	}
	void SetAge(int num)
	{
		if (num >= 0 && num <= 200)
		{
			m_nAge = num;
		}
	}
};

int main()
{
	CPeople peo;//定义一个对象（类的实例化）,这时才会为CPeople这个类开辟空间
	peo.m_strName = "小明";
	cout << peo.m_strName << endl;
	peo.SetAge(20);
	cout << peo.GetAge() << endl;

	return 0;
}
```
### 构造函数
构造函数：
通常在定义变量时要初始化，在定义类对象时，成员属性并没有得到初始化。C++类提供了一种特殊的函数‐构造函数。
构造函数：其作用是用来初始化类成员属性。空类中存在一个默认的无参数的构造，函数名为当前类名，无返回值。
```cpp
class CTest
{
	//CTest(){ } //默认无参构造
};
```
构造函数并不需要我们手动调用，在定义对象的时候会自动调用，这个默认的无参构造是编译器给提供的，函数体代码为空，所以在定义对象时虽然调用了，但并没有这正给成员初始化。
所以需要手动重构构造函数。一个类中的构造函数允许存在多个，他们是函数重载的关系，重构的构造函数可以指定参数来符合我们需要的初始化过程。
注意：只要重构了任何的构造函数，编译器将不会再提供那个默认的无参构造了。
定义多个对象可能会执行不同的构造，这就要看在定义对象时如何指定参
数了，会根据参数的类
型、数量自动匹配对应的构造，但一个对象最终只能执行其中一个构造。
### 析构函数
析构函数：与构造函数相对应的析构函数，其作用是用来回收在类中申请的额外的空间。空类中存在一个默认的析构函数，函数名为~类名，无返回值，无参数。
```cpp
class CTest\
{
//~CTest(){ } //默认析构
};
```
析构函数在对象的声明周期结束的时候，自动调用，编译器提供的默认析构函数函数体代码也为空，我们可以手动重构，一旦重构，编译器就不会再提供那个默认析构了，与构造不同的是析构函

数只允许存在一个。
## 对象
对象是类的实例化
### 对象的种类
1. 局部对象：在函数内（包含参数）定义的栈区，局部对象在**函数调用完毕**或**遇到}**时生命周期结束，内存空间自动被系统回收
2. new的对象：使用关字 new 在堆区的对象，直到执行delete操作时生命周期结束，内存才会被释放。
3. 全局对象：生命周期比较早，在程序运行时会先调用构造函数初始化全局对象，然后再执行main函数，直到程序退出前，要回收全局对象内存，调用其析构。
4. 静态全局对象：他的声明周期与全局对象是一样，都是伴随着程序的运行开始，直到程序退出。如果存在多个对象那么哪个对象写在前面先被定义，则先执行其构造，最后在退出时执行析构与构造的顺序相反。局部对象亦是如此。**静态全局对象与全局对象的区别不在于生命周期，而是在于作用域。** 静态全局对象作用于所属源文件里，不能作用到其它源文件文件里，即被static关键字修饰过的对象具有文件作用域。这样即使两个不同的源文件都定义了相同名字的静态全局对象，它们也是不同的变量。而全局对象则在所有源文件中共享。
5. 静态局部对象：是定义在某个函数中的对象，但它并不是程序已创建就被初始化，而是第一次执行该函数定义对象时被初始化，以后再调用该函数并不会创建新的对象，此对象只会存在一份。如果函数一直没有被执行，那么该静态局部对象也不会被初始化。与静态全局对象对象相比，静态局部对象 创建的晚些，但都是在程序退出前被回收，这也就意味着我们可以在函数外使用静态局部对象，前提是此对象已经被创建了。
6. 临时对象（匿名对象）：临时对象（匿名对象）的生命周期，只存在于当前代码的这一行，遇到;结束，通常用于函数中的 对象的返回。
![[对象的种类.png]]
## 类所占空间
空类占据1个字节，占位作业，标识当前对象真实存在内存空间中，区别于其他对象
有成员属性后，按照属性所占空间分配。
### 类和对象组成部分的所属
	成员属性         -->  对象-->类不实例化成对象的话，就不存在成员属性
	成员函数         -->  类
	静态成员属性      -->  类
	静态成员函数      -->  类
## 成员属性和成员函数
1. 一般的成员属性：属于对象，会占用对象的内存空间，定义对象的时候，定义多个对象会存在多份成员属性
2. 成员函数：属于类的，占用的是应用程序的空间，[[编译期]]存在，一个类只有一份，与是否定义对象无关，多个对象共享函数
```cpp
#include<iostream>
using namespace std;

class CTest {
public:
	int m_a;
	CTest() {
	}
	void show() {
		cout << "shuow" << endl;
	}
	void showA() {
		cout << "shuow" << " "<<m_a << endl;
	}
};

int main()
{
	cout << sizeof(CTest) << endl;//空类 1个字节（占位标识符），有成员属性后，按照属性所占空间分配
    
	CTest* p = nullptr;
	//cout << p->m_a << endl;类不具体化成对象时，类中的成员属性并不存在，所以会报错
	p->show() ;//类中的成员函数，存在，并且在 具体化对象后 也不占用对象的空间
	//p->showA();//函数中用到了属性，所以也会出错

	return 0;
}
```

## this指针
1. 类中的**非静态成员函数**会有一个隐藏的参数（在第一个位置），为this指针，类型是**类名* const this** ，这才是实际上该函数的第一个参数
2. this指针的**作用**：**连接当前调用该函数的对象和函数**，在函数中使用其他成员都是使用this调用的
    **起桥梁作用，在类中可以无感知的使用类成员（成员属性、成员函数）**
3. 编译器会默认为我们添加this指针
![[this指针示意图.png]]
```cpp
#include<iostream>
using namespace std;

class CTest {
public:
	int m_a;
	CTest() {

	}
	void show() {
		cout << "shuow" << endl;
	}

	void showA(/*CTest * const this */) {
		cout << "shuow" << " "<<m_a << endl;//等效下面一行，编译器自动添加了 this
		//cout << "shuow" << " "<<this->m_a << endl;
		show();//等效于
		//this->show();
	}
};

int main()
{
	cout << sizeof(CTest) << endl;//空类 1个字节（占位标识符），有成员属性后，按照属性所占空间分分配
    
	CTest* p = nullptr;
	//cout << p->m_a << endl;类不具体化成对象时，类中的成员属性并不存在
	p->show() ;//类中的成员函数，存在，并且不占用对象的空间
	//p->showA();//函数中用到了属性，所以也会出错

	return 0;
}
```
## 静态成员(static)
### 静态成员的初始化
类中的静态成员初始化，需要写在类外，格式 **类型 类名:: 变量名 = 初始化值** 
注意：

1. 去掉static 
2. 分文件编写的时候，写在.cpp中
```cpp
#include<iostream>
using namespace std;

/*
静态成员属性：属于类，，不包含在对象的内存空间中，编译期存在，与对象存在与否无关
*/
class CTest {
public:
	static int m_a;//静态成员属性
	int m_b;
	CTest() {
		m_a = 10;//赋值，不是初始化
		m_b = 20;//初始化
		cout << m_a << endl;
	}
    static void fun(){/*没有隐藏的指针this，就不能使用普通成员属性和成员函数*/
		cout << "static void fun()" << endl;
	}
};
/*
类中的静态成员初始化，需要写在类外，格式  类型 类名:: 变量名 = 初始化值  注意：去掉static
分文件编写的时候，写在.cpp中
*/
int CTest::m_a = 30;//初始化

/*
静态成员的使用，可以通过对象也可以不通过对象
*/
int main()
{
	CTest tst1;
	cout << tst1.m_a << endl;
	cout<<CTest::m_a;	//在没有对象的情况下，类名作用域直接使用
	CTest tst2;
	cout << &tst1.m_a << " " << &tst2.m_a << endl;

	//通过对象去修改静态成员属性，对其他对象是可见的（使用的是修改之后的值）
	tst1.m_a = 100;
	cout << tst2.m_a << endl;

}
```
### 静态成员属性
1. 特点
属于类的，不包含在对象的内存空间中，编译期存在，与对象存在与否无关，一个类中只有一份，多个对象共享
2. 初始化
需要写在类外进行初始化，格式类型  **类名::变量名=初始化值**，注意：去掉关键字static
3. 调用
可以通过对象去使用，也可以不通过对象类名作用域直接使用
### 静态成员函数
	特点
		属于类的，在编译期存在，一个类只有一份，多个对象共享这一份函数
	和普通成员函数的区别
		1. 本质区别
			静态成员函数没有隐藏的this指针，就不能使用普通成员属性和成员函数，只能使用静态的成员。
		2. 调用
			**静态成员函数是否通过对象都可以调用**，普通的成员函数必须通过对象去调用

## 常量(const)
当类中有const类型的变量时，在定义的时候必须要初始化，而这个初始化操作是在 **初始化参数列表** 中完成的，而构造函数的函数体代码中进行的操作严格来说是赋值，先执行初始化列表，在执行构造函数体中的代码。对于普通的变量来说也可在初始化参数列表中初始化。
写法：在构造函数的参数列表后加上一个冒号 : 后面是初始化的成员，用圆括号 ()的形式指定初始化值，多个成员用 逗号,分割。
```cpp
class CTest{ 
	int m_a;
	const int m_b; //常量 
	char m_c; //初始化参数列表 
	CTest(int b):m_a(10),m_b(b),m_c('c')
	{
		 m_a = 20; //赋值，允许 
		 //m_b = 30; //赋值，不允许 
	} 
};
```
### 注意
1. 初始化顺序为成员在**类中定义的顺序**，而不是写在初始化参数列表中的顺序。 
2. 常量的特性
	定义就必须初始化，一旦初始化后就不能再去修改其值（通过正常手段）。
### 常量指针、指针常量、常量指针常量
```cpp
//我自己的例子
#include<iostream>
using namespace std;
int main()
{
	int m_a = 10;
	const int m_b = 20;

	//常量指针,通过指针 值不课改，可改指向
	const int* p1 = &m_a;//或者 int congst * p1 =&m_a;
	//*p1 = 30;非法操作
	p1 = &m_b;

	//指针常量， 通过指针 值可改，指向不可改
	int* const p2 = &m_a;//初始化必须赋值
	*p2 = 40;
	//p2 = &m_b;非法操作


	//常量指针常量,不能修改指向，！不能通过！指针改值
	const int* const p3 =& m_a;
	//*p3=100;
	//p = &m_b;
	m_a = 100;//合法

}
```

```cpp
//科林的例子
int a=100; 
int b =200;
const int *p1=&a; //等同于 int const *p2=&a; 指明了 *p1 是不允许修改的，即 * p1=200; // 操作是非法的 
p1 = &b; //是合法的 

int * const p2=&a; //说明了 p2 的指向不能修改 
//p2 =&b; //是非法的 
*p2 =300; //是合法的

const int c =100;
const int *const p3=&c; //指明了当前的指针指向不能修改，且指向的具体的空间的内容
```
### 表格区分
![[用表格去区分常量指针、指针常量、常量指针常量.png]]
### 指针安全级别问题
```cpp
const int*p3=&ma;//安全级别升级的操作

int* const p4 = &mb; // &mb = const int*, 指针的安全级别是降级操作，不允许

*p4=60;
```
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662108934482.png)
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662108948399.png)
## 常函数
1. 定义：类中的成员函数参数列表后面有const修饰时，称之为常函数。
2. 作用：其主要作用是为了能够保 护类中的成员变量
3. 特性：不能修改类中的非静态成员，因为const修饰this指针变为 **const 类* const this**，也就是不能执行 this‐>变量=val 操作，但是仍然可以查看成员变量。对于静态成员属性不但能查看，也能对其修改，因为静态成员可不通过this 去使用。 
4. 注意：在常函数中可以查看普通的变量、常量、静态变量等，也可以调用其他常函数，但是却不能使用普通的成员函数，因为其this指针的类型并不相同，CTest* const this = const CTest* const this 这将是一个非法的操作。
```cpp
#include<iostream>
using namespace std;

class CTest {
public:
	int m_a;
	const int m_b;
	static int m_c;

	CTest():m_a(10), m_b(20) {
	}
	void show(/*CTest const this */) {
		this->m_a = 40;
		fun();
		//或者this->fun();
		
		/*相当于
		CTest tst;
		CTest* const pthis2 =& tst;
		const CTest* const pthisl = pthis2; // 指针的安全级别升级操作，允许的
		*/
	}
	
	/*
	区别：this指针类型不同，对于常函数来说有双重const修饰，在常函数中不能修改类中的非静态成员属性，
	常含数不能调用普通函数，但是可以调用静态函数
	*/


	/*常函数，在参数列表后面加const, const修饰了* this, 意味着this指针指向的对象里的成员属性不能修改*/
    
	/*const */void fun(/*const CTest*const this *//*const int a*/)const {
		cout << m_a << " " << m_b << endl;
		// ma = 30;//即使是变量也不能在常函数中修改
		//mb=40:
		//this->m_a=20;不可修改
		this->m_a;
		this->m_b;

		m_c = 50;//可以修改静态成员，因为静态成员可以不用this调用

		//this->show();
		//show();
		
		/*相当于
		CTest tst;
		const CTest*const pthisl =&tst;
		CTest*const pthis2 pthis1://指针的安全级别降级操作，不允许
		*/
	}
};
int CTest::m_c = 30;

int main()
{
	//int m_a = 10;
	//const int m_b = 20;

	//const int*p3=&ma;//安全级别升级的操作
	// int* const p4 = &mb; // &mb = const int*, 指针的安全级别是降级操作，不允许
	//*p4=60;

	
	return 0;
}
```

### 特点
1. 常函数，在参数列表后面加const, const修饰了* this, 变成了 const CTest*const this  意味着this指针指向的对象里的成员属性不能修改，即使是变量也不能在常函数中修改。
2. 与普通函数的区别：this指针类型不同，对于常函数来说有双重const修饰，在常函数中不能修改类中的非静态成员属性，常含数不能调用普通函数，但是可以调用静态函数（因为静态成员可以不用this调用）
3. 分文件编写时候，定义时，const不能省略

## 内联(inline)
## 空间换时间
内联函数C++为了提高程序的运行速度所做的一项改进，普通函数和内联函数主要区别不在于编写 方式，而在于C++编译器如何将他们组合到程序中的。编译器将使用相应的函数代码替换到内联函 数的调用处，所以程序无需跳转到另一个位置执行函数体代码，所以会比普通的函数稍快，代价是 需要占用更多的内存，空间换时间的做法。
执行函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中， 然后才能执行函数体中的代码，代码执行完毕后还要将之前压入栈中的数据都出栈。这个过程中涉及到空间和时间的开销问题，如果函数体的中代码比较多，逻辑也比较复杂，那么执行函数体占用 大部分时间，而函数调用、释放空间过程花费的时间占比很小可以忽略；如果函数体的中代码非常 少，逻辑也非常简单，那么相比于函数体代码的执行时间 函数调用机制所花费的时间就不能忽略 了。
```cpp
int add(int a,int b)
{ 
	return a+b;
} 
int c = add(1,2);
```
所以为了消除函数调用的时间开销，C++提供一种提高效率的方法 inline函数，上例中的add函数 可以变为内联函数，如下 ，内联函数在编译时将函数调用处用函数体替换（类似于宏）。
```cpp
inline int add(int a,int b)
{ 
	return a+b;
} 
int c = add(1,2); //替换后：int c = 1+2;
```
### 注意
1. inline是一种空间换时间的做法，内联在一定程度上能提高函数的执行效率，这并不意味着所有 函数都要成为内联函数，如果函数调用的开销时间远小于函数体代码执行的时间，那么效率提 高的并不多，如果该函数被大量调用时，每一处调用都会复制一份函数体代码，那么将占用更 多的内存会增加，得不偿失。所以一般函数体代码比较长，函数体内出现循环（for、while）， switch等不应为内联函数。 
2. 并非我们加上 inline关键字， 编译器就一定会把它当做内联函数进行替换。定义 inline 函数只 是程序员对编译器提出的一个建议，而不是强制性的，编译器有自己的判断能力，它会根据具 的情况决定是否把它认为是内联函数。编译器不会把递归函数视为内联函数的。 3. 类、结构中在的类内部声明并定义的函数默认为内联函数，如果类中只给出声明，在类外定义 的函数，那么默认不是内联函数，除非我们手动加上 inline 关键字。
3. 3. 类、结构中在的**类内部声明并定义的函数默认为内联函数**，如果类中只给出声明，在类外定义 的函数，那么默认不是内联函数，除非我们手动加上 inline 关键字。
```cpp
class CTest
{
	public: int show(){ //默认内联 
		int a = 1;
		return a; 
	} 
}; 
int main()
{ 
	CTest tst;
	tst.show(); //内联替换 
	return 0 ; 
}
```


# **02继承**
## 类之间的关系
## 类之间的横向关系
#### 组合（复合）
是一种"is a part of"的关系，部分与整体，包含与被包含。组合是一个类中包含另一个类对象。相比聚合，组合是一种强所属关系，组合关系的两个对象往往具有相同的生命周期，被组合的对象是在组合对象创建的同时或者创建之后创建，在组合对象销毁之前销毁。一般来说被组合对象不能脱离组合对象独立存在，整体不存在，部分一定不存在。
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/%E7%BB%84%E5%90%88.png)
 举例：人与手、人与头之间的关系，人需要包含头和手，头、手是人的一部分且不能脱离人独立而存在。 在C+语法中，通常在组合类中包含被组合类对象来实现组合关系：
 ```cpp
class CHand{};
class CPeople{
	CHand m hand;//组合（复合）关系
}
 ```
#### 依赖
是一种"use a"的关系。一个对象的某种行为依赖于另一个类对象，被依赖的对象视为完成某个功能的工具，并不持有对他的引用，只有在完成某个功能的时候才会用到，而且是必不可少的。依赖之间是没有生命周期约束关系的。
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/image-20220826170956737.png)
 举例：人要完成编程这件事，那么需要用到电脑，电脑作为一个工具，其他的时候不需要，电脑也不可能作为人的属性而存在（非组合关系），人必须依赖于电脑才能完成编程这件事。 C++语法中，代码的表现形式为多种，通常将被依赖的对象作为另一类方法的参数的形式实现两个类之间的依赖关系。
 ```cpp
class CComputer{};
class CPeople{
	void Code(CComputer *pc)//或：CComputer &pc,
};
 ```
#### 关联
是一种"has a"的关系。关联不是从属关系，而是平等关系，可以拥有对方，但不可占有对方。完成某个功能与被关联的对象有关，但是可有可无。被关联的对象与关联的对象无生命周期约束关系，被关联对象的生命周期由谁创建就由谁来维护。只要二者同意，可以随时解除关系或是进行关联，被关联的对象还可以再被别的对象关联，所以关联是可以共享的。
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/image-20220826171034226.png)
 举例：人和朋友的关系，人要完成玩游戏这个功能，没有朋友可以自己玩游戏，如果交到朋友了就可以和朋友一起玩游戏。 C++语法中，通常在关联的类中定义被关联类对象的指针形式实现两个类之间的关联关系。
 ```cpp
class CFriend{};
class CPeople{
	CFriend*m pFriend;//关联关系
}
 ```
#### 聚合
它是一种"owns a"的关系。多个被聚合的对象聚集起来形成一个大的整体，聚合的目的是为了统一进行管理同类型的对象，聚合是一种弱所属关系，被聚合的对象还可以再被别的对象关联，所以被聚合对象是可以共享的。虽然是共享的，聚合代表的是一种更亲密的关系，相当于强版本的关联。
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/image-20220826171052974.png)
 举例：一堆人组成一个家庭，进行统一管理完成敲代码工作。 C++语法中，通常在聚合类中定义被聚合对象指针的数组、链表等容器。
 ```cpp
class CPeople{};
class CFamily{
	CPeople*m_pFamily [10];
}
 ```

```cpp
#include<iostream>
using namespace std;


class CHand {
public:
	void move() {
		cout << "我的手在移动" << endl;
	}
};
class CComputer {
public:
	void compile() {
		cout << "电脑正在编译代码   生成可执行程序" << endl;
	}
};

class CFriend {
public:
	void play() {
		cout << "我的朋友正在玩耍" << endl;
	}
};


class CPeople {
public:
	CHand m_hand;
	CFriend* m_pFri;
public:
	void clap() {
		m_hand.move();
		cout << "手掌撞击   发出掌声" << endl;
	}
	void code(CComputer* pCom) {
		if (pCom) {
			m_hand.move();
			cout << "敲出一行行代码...." << endl;
			pCom->compile();
		}
		else {
			cout << "我无法完成敲代码的功能" << endl;
		}
	}
	void palyWangZhe() {
		if (m_pFri) {//有朋友
			cout << "找朋友组队.." << endl;
			m_pFri->play();
			cout << "我和我的朋友一起打王者，victory" << endl;
		}
		else {//没朋友
			cout << "我和自己打王者，victory" << endl;
		}
	}
};


class CFamily {
public:
	CPeople* m_arrPro[10];
	CFamily() {
		for (CPeople*& peo : m_arrPro) {
			peo = nullptr;
		}
		m_arrPro[0] = new CPeople;
		m_arrPro[1] = new CPeople;
		m_arrPro[2] = new CPeople;
	}
	~CFamily() {
		for (CPeople*& peo : m_arrPro) {
			if (peo) {
				delete peo;
				peo = nullptr;
			}
		}
	}
public:
	void AllPeopleCode(CComputer* pCom) {
		for (CPeople* peo : m_arrPro) {
			if (peo) {
				peo->code(pCom);
			}
		}
	}
};



int main()
{
	{
		//组合
		CPeople peo;
		peo.clap();
		cout << endl;
	}

	{
		//依赖
		CComputer* pCom = new CComputer;
		CPeople peo;
		peo.code(pCom);

		delete pCom;//回收电脑
		pCom = nullptr;


		peo.code(pCom);//此时没有电脑
	}

	{
		//关联
		CPeople peo;
		peo.palyWangZhe();

		CFriend* pFri = new CFriend;
		peo.m_pFri = pFri;//结交朋友
		peo.palyWangZhe();

		peo.m_pFri = nullptr;//和朋友绝交
		peo.palyWangZhe();

		delete pFri;
		pFri = nullptr;


	}

	{
		//聚合
		CComputer comp;
		CFamily fam;
		fam.AllPeopleCode(&comp);
	}

	return 0;
}
```
### 当一个类包含另一个类的对象
1. 编译器会默认调用，被包含的对象的默认构造函数
2. 如果需要调用带参数的构造，需要显示指定
3. 如果被包含的类中没有无参的构造函数，必须显式的指定带参数的构造函数，如果什么也不指定，会因为编译器默认无参构造，但是被包含类没有无参构造而报错。
```cpp
#include <iostream>
using namespace std;
class CStepFather {
public:
	int m_a;
	CStepFather() {
		m_a = 10;
	}
	CStepFather(int a) {
		m_a = a;
	}
};

class CSon {
public:
	CStepFather m_stepFa;//包含另一个类的对象
	int m_son;
public:
	CSon() /*：m_stepFa() */ { // 当包含另一个类的对象，编译器会自动调用无参的构造进行初始化
		m_son = 20;
	}
	CSon(int a) :m_stepFa(a) {//如果想调用带参数的构造函数进行初始化，需要手动显式指定
		m_son = 20;
	}
	CSon(int a, int b) :m_stepFa(a) {
		// 如果另一个类中没有无参的构造函数，必须显式的指定带参数的构造函数，如果什么也不指定，会报错
		m_son = 20;
	
	}
};

int main() {
	CSon son;
	cout << son.m_son <<"  "<<son.m_stepFa.m_a << endl;
	CSon son2(100);//匹配的是CSon和CStepFather的带参数的构造函数
	cout << son2.m_son <<"   "<<son2.m_stepFa.m_a << endl;
	return 0;
}
```
## 类的继承
## 类之间的纵向关系
### 定义
被继承的类叫做基类（父类），继承的类叫派生类（子类），**在派生类类名后面加 : 继承方式** ，基类子类包含且可以使用父类的成员.
```cpp
class CFather{}; 
class CSon:public CFather{};
```
```cpp
#include <iostream>
using namespace std;
//继承：子类包含且可以使用父类的成员
class CFather {
public:
	int m_a;
	int m_money;
	CFather() {
		m_money = 100;
	}
};

class CSon :public CFather {
public:
	int m_b;
	int m_money;
	CSon() {
		m_a = 10;
		m_b = 20;//子类可以直接使用父类的成员
		m_money = 200;
	}
	void show() {
		cout << m_a << " " << m_b << endl;
		cout << CSon::m_money << endl;//当子类成员和父类成员同名时，在成员前面加上作用域得以区分，默认是子类
		cout << CFather::m_money << endl;
	}
};

int main()
{
	CSon p1;
	p1.show();
	cout << endl;
	cout << p1.m_money << endl;
	cout << p1.CSon::m_money << endl;
	cout << p1.CFather::m_money << endl;//显示指定
	return 0;
}
```
### 继承的原理
子类继承父类，相当于将父类的成员包含到自己的类里，所以定义子类对象所占用的空间大小除了 子类自身的成员还包括父类的成员。
成员在内存空间分布为：
1. 先父类成员、后子类成员，
2. 每个类中的成员分布与在类中定义的顺序一致。
![[继承的原理.png]]
### 继承的优点
我们可以将类中的一些功能相近、相似的共同的方法，抽离出来放到单独的一个类 中，并让其继承这个类，那么抽离出来的类就是父类，将来其他类在增加公共的方法时，我只需要 在父类添加一份即可。
**提高了代码的复用性、扩展性。**

### 当子类和父类成员同名时/隐藏
当子类成员和父类成员同名时，默认是子类，在成员前面加上作用域得以区分。
子类中出现和父类中同名的函数，会隐藏父类中的函数。这种关系叫隐藏。若想使用父类中的函数，可以加上类名作用域。
### 继承的方法
public 、protected、private, 和 访问修饰符共同决定了父类中的成员在子类中的使用范围，所表现属性 及 访问控制
默认继承方式：private 私有继承
|继承方式 |父类中的属性| 子类中的属性 |
|-----------|--------------|-----------------|
|public |public |public
|| protected| protected|
||private| 不可访问| 
|protected |public| protected|
||protected| protected|
||private| 不可访问|
|private| public| private |
||protected| private|
||private| 不可访问|
### 继承中构造和析构的顺序
### 构造顺序
真父类->假父类->子类
#### 构造顺序说明
在子类创建对象的时候，执行子类的构造函数（注意这里并不是直接先执行父类的 构造函数），但要先执行子类的构造的初始化列表，在初始化列表中会默认调用父类的无参构造初 始化父类成员，如果父类只有带参数的构造，那么需要在子类的初始化参数列表显示的指定父类的 初始化。这有点像之前说的组合关系形式。
### 析构顺序
和构造的顺序相反，先析构在回收对象
析构子类->回收子类---->析构假父类->回收假父类---->析构父类->回收父类
#### 析构顺序说明
子类对象的生命周期结束后，因为是子类所以自动调用子类析构，当析构执行完 了，才会回收对象分配的空间，当然这个空间包含创建的父类的成员，那么回收父类成员前，自动 调用父类的析构。如果是new出来的子类对象，同理。
### 父类指针指向子类对象
对于函数重载而言，我们调用的时候，可以根据参数类型、参数个数，编译器自动区分该具体调用 哪个函数。同样如果在一个类中存在两个同名函数（参数列表不同），那么也可以根据调用者传递 的参数自动的区分执行哪个函数，因为也是一个函数重载的关系。
那对于父类和子类中，如果有同名的函数但是参数列表不同，则不能够自动区分，因为他们之间的 关系并不是函数重载的关系，作用域不同，必须使用 **类名::** 去区分到底该调用哪个函数。子类中和父类同名的函数，称之为 **隐藏** 。
在继承关系下，允许父类的指针指向子类的对象，但是反过来却不行。
### 优点
1. 父类的指针可以统一多个类的类型
2. 提高代码的复用性、扩展性。
```cpp
#include<iostream>
using namespace std;

void show(int a) {
	cout <<"show(int a)" << a << endl;
}

void show(char a) {
	cout << "show(char a)" << a << endl;
}

class A {
public:
	void show(/*  A * const this   */int a, int b) {  //和子类中同名的成员的关系可以称之为：隐藏
		cout << "A::show(int a, int b) " << a << "    " << b << endl;
	}
};

class AA:public A {
public:
	void show(int a) {
		cout << "AA::show(int a)" << a << endl;
	}
	//也是函数重载
	void show(char a) {
		cout << "AA::show(char a)" << a << endl;
	}
};


int main() {
	show(10);   //可以根据实参自动匹配对应的重载函数
	show('a');

	/*AA aa;
	aa.show(10);
	aa.show('b');*/
	
	//aa.show(10,20);    //想去匹配父类的函数，但无法自动匹配，不是函数重载，因为不在一个作用域下
	 
	
	//-----------------------------------
	
	//AA aa;
	//aa.show(10, 20);  //子类的同名的函数注释掉，可以匹配父类的函数了

	AA aa;
	aa.A::show(10,20);   //显式指定父类的show函数

	A* pthis = &aa;  //继承下，父类的指针不通过强转可以直接指向子类对象
	return 0;
}
```
### 类成员函数指针
首先，使用函数指针的优点-->[[通过函数指针调用]]
### 类成员函数和普通成员函数的区别
1. 作用域。类成员函数标识了所属的类，必须通过对象调用（虽然可以是空指针对 象，但必须得有）。
2. 类成员函数编译器会默认加上一个隐藏的参数，即this指针。 所以定义类成员函数的指针与普通的函数指针肯定会有所区别： C++ 提供了三种运算符  ::* 、.* 、‐>. 、用于定义的使用类成员函数指针。
```cpp
void (CTest::*p_fun)() = &CTest::show; //定义类成员函数指针并初始化，注 意： & 必须加上， 
typedef void (CTest::*P_FUN)(); //使用typedef 进行优化 
P_FUN p_fun2 = &CTest::show;
(tst.*p_fun2)(); //普通对象通过指针调用类成员函数 
(pTst ‐>* p_fun2)(); //指针对象通过指针调用类成员函数
```

```cpp
#include<iostream>
using namespace std;
void show() {
	cout << "show" << endl;
}
class  CTest {
public:
	void show(/* CTest const this */) {
		cout << "CTest::show" << endl;
		cout << "this" << endl;
	}

};
/*
区别：
1.作用域不同。
2.非静态类成员函数有隐藏的this指针，全局的函数没有
*/

int main() {

	CTest tst;
	tst.show();

	//void (*p_fun)() = &tst.show;//这是一个错误的写法
	//void (*p_fun)() = &CTest::show;//无法从“void(CTest ::*)(void)” 转换为 “void(*)(void)”
	// 类成员函数指针，C ++ 中提供的一个整体操作  ::* ，用来定义类成员函数指针
	
	void (CTest :: * p_fun)() = &CTest::show;
	(tst .* p_fun)();///.*、->* c++中提供的一个整体操作，通过对象调用类成员函数指针指向的类成员函数


	CTest* pTst = new CTest;
	(pTst->*p_fun)();

	cout << pTst << endl;


	return 0;


}
```
### [[可以使用类成员函数指针模拟实现多态]]
## 调用函数的三种方法
1. 通过函数名直接调用
2. [[通过函数指针调用]]
3. [[使用typedef对函数指针进行优化]]在调用

# **03多态**
## 定义：
相同的行为方式可能导致不同的行为结果，即产生了多种形态行为，即多态，同一行语句展 现了多种不同的表现形态
多态的本质：
定义父类的指针可以指向任何继承于该类的子类的对象，且父类的指针具有子类对象的行为，多种子类表现为多种形态由父类的指针进行统一，那么这个父类 额指针就具有了多种形态
## 多态发生的条件
1. 存在继承关系
2. 父类指针指向子类对象，通过该指针调用虚函数（或者引用形式，如 CFather& fa = son; //引用形式的多态 本质还是父类指针指向子类对象）
3. 父类中存在[[虚函数和虚函数列表]]，子类[[重写]]虚函数
## 多态的底层原理
## 重要
虚函数列表是属于类的，而不是属于某个对象的，但是__vfptr 是属于对象。每个类都会有对应的 虚函数列表（前提是有虚函数），由于子类继承父类，那么也会继承父类的虚函数列表，编译器会 检查子类是否有重写父类的虚函数，如果有，那么在子类的虚函数列表中会替换掉父类的虚函数地 址，我们称之为覆盖，指向了子类中的虚函数。如果子类没有重写的父类虚函数，依然会保留在子 类的虚函数列表中，如果子类有自己的虚函数，那么会顺序添加到虚函数列表中，这个过程在编译 阶段就完成了。 多态的前提条件是父类的指针指向子类对象，那么虚函数指针在子类中被初始化指向子类的虚函数 列表，也就是说new的哪个子类对象，_ vfptr就指向了哪个子类的虚函数列表。
## 重要 
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/%E7%BB%A7%E6%89%BF%E4%B8%8B%E5%A4%9A%E6%80%81%E5%AE%9E%E7%8E%B0%E7%9A%84%E5%8E%9F%E7%90%86.png)
### 子类的虚函数列表
继承多态下，子类的虚函数列表：
1. 子类不但继承父类的成员，也会继承父类的虚函数列表。
2. 会检查子类中是否有重写的父类的虚函数，如果有就原位置替换，称之为覆盖，如果没有父类的虚函数得以保留。
3. 子类中独有的虚函数，按照顺序依次在虚函数列表的后面添加。
## 实现多态
```cpp
class CFather
{ 
public: 
	virtual void show()
	{ //虚函数 
		cout<<"CFather::show"<<endl;
	}
};
class CSon:public CFather
{ //继承
public:
	virtual void show()
	{
		//重写了父类的虚函数，即使不加 virtual 也会认为是虚函数
		cout<<"CSon::show"<<endl;
	}
CFather *pFa = new CSon; //父类的指针指向子类对象 
pFa‐>show(); //调用的是子类的函数
```
### 较为复杂一点的实现多态
```cpp
#include<iostream>
using namespace std;


class CFather {
public:
	virtual void fun1() {
		cout << "CFather::fun1()" << endl;
	}
	virtual void fun2() {
		cout << "CFather::fun2()" << endl;
	}
};

class CSon :public CFather{
public:
	virtual void fun1() {
		cout << "CSon::fun1()" << endl;
	}
	virtual void fun3() {
		cout << "CSon::fun3()" << endl;
	}
};
class CSon2 :public CFather {
public:
	virtual void fun1() {
		cout << "CSon2::fun1()" << endl;
	}
};

/*继承多态下
*虚函数指针指向哪个类的虚函数列表，取决于定义哪个类的对象（new哪个子类）
*/

int main() {
	CFather* pFa1 = new CFather;//虚函数指针指向 父类CFather 的虚函数列表

	CFather* pFa2 = new CSon;//虚函数指针指向 子类CSon 的虚函数列表
	CFather* pFa3 = new CSon2;//虚函数指针指向 子类CSon2 的虚函数列表
	

	CSon son;
	/*
	[0]:CSon::fun1
	[1]:CFather:fun2
	*/
	pFa2->fun1();
	pFa2->fun2();
	((CSon*)pFa2)->fun3();

	return 0;
}
```
## 虚析构
在多态下，父类的指针指向子类的对象，最后在回收空间的时候，却是按照父类的指针类型delete 的，所以只调用了父类的析构，子类的析构并没有执行，这样的话就有可能导致内存泄漏。
### 解决办法：
用虚析构来解决，即把父类的析构函数变为虚析构函数，这样的话，再去按照父类的指针 delete时，调用析构会发生多态行为，从而真正调用的是子类的析构，最后回收对象内存空间时， 再调用父类的析构。
```cpp
class CFather
{ 
	virtual ~CFather()
	{ //虚析构 
	}
};
class CSon:public CFather
{ 
	virtual ~CSon()
	{//虚析构 
	} 
};
```
使用多态时，父类的析构，一定是虚析构；子类加不加virtual都可。

## 纯虚函数
在多态下，有时抽象出来的父类的虚函数，并不知道如何实现，只有继承的子类才可能知道具体的 实现，可以把父类的虚函数变为纯虚函数。
### 纯虚函数的特点：
1. 当前类不必实现，而子类必须要实现纯虚函数
2. 包含纯虚函数的类，不能实例化，又叫 抽象类
3. 抽象类的派生类，又称具体类，具体类必须实现抽象类的所有纯虚函数
### 抽象类和具体类
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/%E6%8A%BD%E8%B1%A1%E7%B1%BB%E5%92%8C%E5%85%B7%E4%BD%93%E7%B1%BB.png)
```cpp
#include <iostream>
using namespace std;

class CFather//包含纯虚函数的类，不能实例化，又叫 抽象类
{
public:
    virtual void fun() = 0;//纯虚函数，子类必须重写。只在父类声明，不需实现
    
    virtual void fun1()
    {
        cout << "Father::fun()2" << endl;
    }
};

class CSon : public CFather//抽象类的派生类，又称 具体类
{
public:
    virtual void fun()
    {
        cout << "CSon::fun()" << endl;
    }
    virtual void fun1()
    {

        cout << "Son::Pfun()1" << endl;
    }
};



int main()
{

    CFather* pFa = new CSon;
    pFa->fun();

    //CFather fa;//包含纯虚函数的类不能实例化，叫抽象类
    
    return 0;
}
```
## 多态缺点
1. 效率：调用虚函数效率低。
2. 空间：虚函数指针占用空间，多个对象会有多个虚函数指针，虚函数列表会随若继承的层级递增虚表大小只增不减。
3. 安全：类中的私有的函数，不能为虚函数，否则会有安全隐忠。



# **04程序生成过程**
1. 预处理期：
	源代码文件 main.cpp -> main.i 预处理后的文件
	1. include 头文件的展开 
	2. 删除注释
	3. define 宏的替换
	4. ifndef ,ifdef ,\#else,\#elif,\#if, \#endif...等预处理指令
2. 编译期：
狭义：将预处理后的文件进一步处理，生成汇编文件，包含汇编代码， main.i -> main.asm(汇编文件)对代码进行 语法分析、语义分析、词法分析 和 优化。
广义：将源代码文件交由编译器，编译、生成，最终生成可执行文件的过程。用来区分运行期。
3. 汇编期：
将上一步生成的汇编文件，按照汇编代码一条一条生成目标机器指令，main.asm->main.obj(目标机器文件(二进制文件))
4. 链接期：
通过链接器将多个目标文件（.obj）和库文件 链接整合到一起，生成可执行程序（.exe（二进制文件））
5. 运行期期：
将可执行文件交由操作系统运行，直到程序退出的过程。
![[程序生成过程.png]]
## 注意
1. 类： 编译期的概念，包括 访问修饰符 和 作用域
2. 对象（类的一个实例化）:运行期的概念，包括指针，引用等
3. 宏是编译期（广）
4. 变量开数组、数组过大都是编译期（广）
5. 数组越界是运行期
6. 访问修饰符是编译期的限制，多态是运行期多态，所以限制不住，能调用


```cpp
#include<iostream>
using namespace std;

class CFather {
public:
	virtual void fun() {
		cout << "CFather::fun" << endl;
	}
};


char arr[20] = { 0 };

class CSon:public CFather {
private:  //编译期的限制，多态是运行期多态，所以限制不住，能调用
	virtual void fun() {
		cout << "CSon::fun" << endl;
	}
private:
	void fun2() {
		cout << "CSon::fun2" << endl;
	}

public:
	static void GetFun2() {
		printf("%p  %d\n",&CSon::fun2, &CSon::fun2);

		sprintf_s(arr,"%d", &CSon::fun2);
		cout << arr << endl;
	}
};

union AA {
	int a;
	void (*p_fun)();
}aa;


int main() {

	/*const bool a = true;   //优化的例子
	if (a) {
		cout << "aa" << endl;
	}*/

//
//	//编译期确定
//#if __cplusplus
//#define A   10
//#else 
//#define A   20
//#endif //__cplusplus
//
//	int a = A;
//	cout << a << endl;
//
//
//	//运行期确定
//	int b = 0;
//	cin >> b;
//	if (b == 10) {
//		cout << "bbb" << endl;
//	}
//	else {
//		cout << "aaa" << endl;
//	}
//
//	//-------------------------------------
//	//编译期错误
//	//int len = 10;   //error C2131: 表达式的计算结果不是常数
    //int arr[len] = { 0 };
//	//const int len = 9999999999999;
//	//int arr[len] = { 0 };  //error C2148: 数组的总大小不得超过 0x7fffffff 字节
//
//	//运行期错误
//	//int l = 9999999999999;
//	int l = 9;
//	int * p = new int[l];
//	//p[20] = 0;  //数组越界，运行期错误
//
//	cout << "//---------------------------" << endl;
//	CFather* pFa = new CSon;
//	pFa->fun();   //CSon::fun


	//----------------------------
	CSon::GetFun2();

	aa.a = atoi(arr);   //将十进制字符串转成数字
	cout << aa.a << endl;
	(*aa.p_fun)();

	return 0;
}
```


# **05头文件-源文件-宏**
## 头文件和源文件
## 区别
头文件（.h文件）:将声明的变量、类型、函数、宏、类的定义
源文件：将变量初始化、函数的实现放于源文件中
这样方便于我们去管理、规划，更重要的是避免了重定义的问题。
两者的区别：
默认情况下 ，头文件不参与编译，而每个源文件自上而下独立编译。

静态常量成员一定要在源文件中进行初始化。
常函数数在头文件中声明，在源文件中实现除了要加类名:: ，要保留const关键字。

静态函数在头文件中声明，在源文件中实现除了要加类名:: ，要去掉static 关键字。
虚函数数在头文件中声明，在源文件中实现除了要加类名:: ，要去掉virtual关键字。
纯虚函数不需要实现
### 头文件重复包含问题
### 问题现象：
如下图头文件，BB.h和CC.h都包含的AA.h，main函数有都包含了BB.h和CC.h，就会出现AA.重复包含的问题
 ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662109123858.png)
 解决方案1：
 在AA.h第一行加一句\#pragma once
  \# pragma once: 直接和编译器沟通，告诉编译器当前的头文件在其他源文件中，只包含一次， 直接和编译器沟通 效率高，代码编译的速度快，不需要考虑宏重名的问题
 解决方案2：
 基于宏的逻辑判断，编译的速度慢，有一定的概率，宏的名字会重复，导致程序错误。

```cpp
#ifndef   __宏__   //判断当前宏是否定义，如果没定义的话,就定义宏#define
#define   __宏__

	...我的代码...

#endif  //__宏
```
## 宏
宏起到替换作用，一般写法 ：
`#define N 10`
一个标识符被宏定义后，在用到宏 N的地方替换为10，宏替换发生在编译前。
宏是可以传参数的，在宏名字后面加 ﴾PARAM﴿ ，参数的作用也是一个替换。
```cpp
 #define N(PARAM) int a = PARAM;
```
一般情况下，宏替换当前这一行的内容，但是如果要替换多行内容，需要用到 \ 这个字符，用来连接当前行和下一行，一般最后一行不加\\，\\ 后面不能有任何字符，包括空格、tab、注释等。
```cpp
#define RANGE()\
for(int i=0;i<NUM;i++){\
cout<<i<<" ";\
}
```
使用宏替换需要注意，宏及参数并不会像函数参数一样自动计算，也不做表达式求解。宏替换就是文字的替换。
```cpp
#define N 2+3
int a = N*2; //2+3*2 = 8 不是 10
#define N(A,B) A*B
int c = N(1+2,3); //1+2*3 = 7 并不是9
```
可以通过使用()控制运算先后顺序
```cpp
#define N (2+3)
int a = N*2; //(2+3)*2 = 10
#define N(A,B) (A)*(B)
int c = N(1+2,3); //(1+2)*3 = 9
```
### 优点
1. 使用宏可以替换在程序中经常使用的常量或表达式，在后期程序维护时，不用对整个程序进行修改，只需要维护、修改一份宏定义的内容即可。
2. 宏在一定程度上可以代替简单的函数，这样就省去了调用函数的各种开销，提高程序的运行效率。
### 宏的其他用法
1. \# 用于将宏参数转为字符串，相当于加上双引号。`#define HH(A) #A`
2. \# @ 用于将宏参数转为字符，相当于上单引号。`#define JJ(A) #@A`
3. \#\# 用于拼接，常用语宏参数与其他内容的拼接。`#define KK() int a##b=10`
4. [[取消定义宏 ]] \#undef

# **06重载操作符**
## 概念
C++ 提供的运算符，通常只支持对于基本数据类型和标准库中提供的类进行操作，对于自定义类型如果想通过操作符实现对应的操作，需要自定义重载的操作符并实现具体的功能。
重载操作符（也称为重载运算符）：本质上是一个比较特殊的函数，函数名operator后接要重载的操作符， 参数要根据操作符的使用规则来，与使用时的类型、顺序、数量要保持一致。 一般要有返回类型，为了和后续的操作符继续去操作。 告诉编译器当遇到这个操作符时，应当调用该函数来实现一个操作符的功能，是对原来的操作的功能的扩展
## 类内重载操作符
在类内重载，作为类成员函数，需要用对象调用，使用场景需要根据函数的参数一致（包括类型和顺序），注意在类内重载的操作符函数有隐藏的this指针作为第一个参数。在使用是要注意重载操作符的参数类型和顺序，可以直接使用操作符，也可以显示通过对象调用重载的操作符
```cpp
class CTest{
private:
	int m_a;
public:
	CTest()
	{
		m_a = 10;
	}
	int operator+(int a)
	{
		return m_a+a;
	}
};

int main()
{
	CTest tst;
	int a = tst+20;
	int b = tst.operator+(20);
	//int c = 20+tst; //非法
return 0;
}
```
对于单目运算符++，有左++ 和 右++ 两种，为了区分右++，我们需要额外指定一个int类型的参数，这个参数只是用来区分，并无实际意义。
```cpp
int operator++(); //左++
int operator++(int a); //右++
```

## 类外重载操作符
类外：作为全局的重载操作符函数，没有隐藏的ths指针参数，会比类内的重载操作符函数多一个参数，且参数的顺序不是固定的，可以进行调整， 注意是否与类内的重载操作符函数产生歧义。
```cpp
class CTest{
public:	
	int m_a;
	CTest()
	{
		m_a = 10;
	}
	int operator+(int a)
	{
		return this->m_a+a;
	}
};

int operator+(int a,CTest &tst)
{
	return tst.m_a+a;
}

int main()
{
	CTest tst;
	tst+10; //匹配类内重载函数
	10+tst; //匹配类外重载函数
return 0;
}

class CTest
{
public:
	int m_a;
	CTest()
	{
		m_a = 10;
	}
	int operator+(int a)
	{
		return this->m_a+a;
	}
};

int operator+(CTest &tst,int a)
{
return tst.m_a+a;
}

int main()
{
	CTest tst;
	tst+10; //error C2593: “operator +”不明确
return 0;
}
```
### 注意
1. 重载操作符函数不能改变操作符的使用规则，原来几个操作数，重载之后还是几个
2. 重载操作符函数不能有默认值
3. 重载操作符不能改变操作符的优先级和结合性
4. =、[]、 ()、 -> 操作符只能在类内重载这个不允许在类外重载 int operator=(int a, CTest& tst) { }
5. 长度运算符sizeof 、条件运算符?、:、 成员选择符.、作用域选择符 \:\: 不能重载
6. 对应同一个重载操作符函数参数不同，可能就代表不同的函数，例如 *可能是乘法、间接引用，
7. 必须制定一个结构体、类等自定义的类型
8. 不允许对运算符重定义原本就有的功能，运算符重载是增加功能而不是重写原来的功能
9. 当与类内产生歧义，解决方法1：注释掉一个；解决方法2：加作用域运算符
## 类对象类型转换函数
上面重载等号操作符 operator=，能让其他的类型赋值到当前类对象中，但是如果反过来写则会报错，类型不匹配，因为operator=只能在类内重载。此时可以重载某个类型，这样定义该类对象就可以像这个类型一样去使用。
函数格式为：
```cpp
operator type()
{
	return type_value; // 类型要和type 一致。
}
```
函数在写法上无参数，无返回值，但函数体中应该有return，且return 的变量类型要和重载的类型一致。例：
```cpp
operator int()
{
	int a=10;
	return a;
}
```
下面两种都是错误写法：
```cpp
int operator int() //error C2549: 用户定义的转换不能指定返回类型
operator int(int a) //error C2835: 用户定义的转换“CTest::operator int”不接受形参
```
## 如果同时存在重载操作符 和重载类型，那么优先匹配重载的操作符
```cpp
int a = tst+10;      //operator+
a = 10+tst;          //operator int
a = tst;             //operator int
```
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1662206882158.png)

当然也可以显示的调用 类型转换函数
```cpp
int a = tst.operator int()+10; //operator int
```



# **07拷贝构造**
## 转换构造函数
一个类中构造函数可以重载，允许多个存在。
如果重载的构造函数只有一个参数且非当前类对象时，可以称之为转换构造函数，其可以将其他类型转自动换为当前类类型，这个过程为隐式类型转换。

```cpp
class CTest
{
public:
	int m_a;
	CTest(int a)
	{
		m_a = a;
	}
};

CTest tst(10); //调用带参数的构造

CTest tst2 = 20; //合法操作 将int类型转换为CTest类型

tst2 = 30; //合法操作 发生隐式类型转换
```

注意：如果是多个参数且无默认值时，则不能自动隐式类型转换。如果想要避免隐式类型转换，在构造函数前加上 关键字：explicit。
## 拷贝构造函数
拷贝构造函数是众多构造函数中的一种，参数比较特殊是当前类对象的引用，它也是编译器默认给提供的，在空类中它与默认的无参构造并存，当我们手动重构拷贝构造函数时，编译器就不会提供默认的拷贝构造了，当然也不会存在默认的无参构造了。
当用一个类对象给类的另一个对象初始化时，会调用拷贝构造函数
```cpp
class CTest
{
CTest();
CTest(const CTest &tst);
};

CTest tst1; //调用无参构造

CTest tst2(tst1); //调用拷贝构造
```
默认拷贝构造函数与默认无参构造不同，其函数体代码不为空，操作为 参数中对象成员依次给this对象成员进行初始化。

默认拷贝构造函数是一个浅拷贝，当类中存在指针成员且指向了一个具体的空间，拷贝构造函数只是将两个指针里存储的地址进行一个值传递，并不会处理指针指向的空间。这样就导致了多个对象里的指针指向了同一个空间，那么会导致以下两个问题：

1. 当其中一个对象通过指针修改其指向空间的值，那么其他对象再使用就是修改之后的值了，这样的情况多数不是我们预期的。
2. 如果是new出来的空间，那么对导致多个对象回收同一块内存空间，引起非法操作错误。

解决办法： **深拷贝**，它并不是一个固定的写法，而是一个解决的办法：即在拷贝构造时，如果参数对象中的指针成员指向了一个内存空间，那么在重构拷贝构造时，需要为当前this对象中指针成员额外开辟新的内存空间，并初始化对应的值。
在某些情况下，可以使用指针或引用可以避免对象的值传递，也避免了浅拷贝问题。
## 默认operator=（赋值）函数
空类中编译器也会默认提供一个operator=函数，参数和 返回值 为当前类对象的引用，如果我们手动重构了编译器也就没必要为我们提供了。
当用一个类对象给类的另一个对象赋值时，会调用默认的operator=函数。
```cpp
class CTest
{
	CTest & operator =(const CTest &tst);
};

CTest tst1;

CTest tst2;

tst2 = tst1; //operator =
```
默认的operator=函数的函数体代码不为空，参数中对象成员依次给this对象成员进行赋值。他同拷贝构造函数一样,编译器默认生成的也是一个浅拷贝，解决方法深拷贝。
## 总结
空类中存在的默认的函数4个：
	默认无参数构造
	默认的拷贝构造
	默认的operator=
	默认析构函数

# **09STL** ![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1665396238708.png)

STL (Standard Template Library),即标准模板库，是一个高效的C++程序库。

STL是 ANSI/ISOC++标准函数库的一个子集，它提供了大量可扩展的类模板，包含了诸多在计算机科学领域里所常用的基本数据结构和基本算法。对于其中的数据结构，用户可能需要反复的编写一些类似的的代码，只是为了适应不同数据的类型变化而在细节上有所出入。如果能够将这些经典的数据结构，采用类型参数的形式，设计为通用的类模板和函数模板的形式，允许用户重复利用已有的数据结构构造自己特定类型下的、符合实际需要的数据结构无疑将简化程序开发，提高软件的开发效率，这就是STL编程的基本设计思想。


C++ STL 之所以得到广泛的赞誉，也被很多人使用，不只是提供了像vector,string,list等方便的容器，更重要的是STL封装了许多复杂的数据结构算法和大量常用数据结构操作。vector封装数组，list封装了链表，map和set封装了二叉树等，在封装这些数据结构的时候，STL按照程序员的使用习惯，以成员函数方式提供的常用操作，如：插入、排序、删除、查找等。让用户在STL使用过程中，并不会感到陌生。

C++ STL中标准关联容器set, multiset, map, multimap内部采用的就是一种非常高效的平衡检索二叉树：红黑树，也称为RB树(Red-Black Tree)。RB树的统计性能要好于一般平衡二叉树，所以被STL选择作为了关联容器的内部结构。

## 容器



分为两大类



1、序列性容器



元素保特了在容器中的原始的位置，允许指定元素的插入位置，每个元素都有固定的位置，位置取决于插入的时间和地点，06list 、 01vector 、 02deque



2、 关联性容器



元素的位置取决于容器的特定排序规则，和元素的值有关， 04map、03set、hash-map

在STL程序设计中， 容器 ( container)就是通用的数据结构。容器用来承载不同类型的数据对象，就如同现实生活中，人们使用容器用来装载各种物品样，但C++中的容器述存在一定的“数据加工能力”，它如同一个对数据对象进行加工的模具，可以把不同类型的数据放到这个模具中进行加工处理，形成具有一定共同特性的数据结构。例如将int型、char型或者 float型放到队列容器中，就分别生成int队列、char型队列或者foat型队列，它们都是队列，具有队列的基本特性，但是具体数据类型是不一样的STL容器主要包括向量( vector)、列表(list)、队列(deque)、集合( set)和映射( map)等。STL用模板实现了这些最常用的数据结构，并以算法的形式提供了对这些容器类的基本操作STL中的所有容器都是类模板，是一个已经建立完成的抽象的数据结构，因此可以使用这些容器来存储任何类型的数据，甚至是自己定义的类，而无需自己再定义数据结构。例如利用 deque容器，就很容易建立一个队列。​
​









## vector

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

  

### 1. vector的简介

  

　　vector是一段连续的内存地址，基于数组实现，管理器可以动态改变对象长度，在 vector:容器中有以下几个关于大小的函数:

  

1. size():返回容器的大小

2. max_size():返回容器扩展极限的最大存储的元素数量

3. empty():判断容器是否为空

4. capacity():返回容器当前能够容纳的元素数量

  

### 2. 使用

  

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

  

### 3. 案例

  

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



## deque

### 1. deque的简介
	deque(double end queue)容器为一个给定类型的元素进行线性处理，像向量一样，它能够：

  一、**优点**：

1. **快速地随机访问任一个元素** ，即支持[ ]以及at()，但是性能没有vector好。

2. **高效地插入和删除容器的尾部元素** ，但性能不及list。

3. **高效插入和删除容器的头部元素** ，因此也叫做双端队列。

4. 可以在需要的时候改变自身大小，完成了标准的C++数据结构中队列的所有功能。在vector中那样“因为旧空间不足而重新匹配一块更大的空间，然后复制元素，在释放旧的空间”这种事情在deque中不会发生。也因此，deque没有必要提供所谓的空间预留（reserved）功能。

5. deque可以包含更多的元素，其max_size可能更大，因为不止使用一块内存。

  二、  **缺点** ：

  

1. 在中间插入元素则会比较费时。

2. 迭代器不是普通指针，是特殊的智能指针，它需要在不同的块中跳转。

3. deque的元素存取和迭代器操作会稍微慢一些，因为deque的内部结构多了一个间接过程，，效率不如vector。对deque进行的排序操作，为了最高效率，可将deque先完整复制到一个vector身上，将vector排序后（利用STL的sort算法），再复制回deque。

4. deque不支持对容量和内存分配时机的控制。

5. 在除了首尾两端的其他地方插入和删除元素，都将会导致指向deque元素的任何pointers、references、iterators失效。不过，deque的内存重分配优于vector，因为其内部结构显示不需要复制所有元素。

6. deque不提供容量操作：capacity()和reverse()，但是vector可以。

  三、 原理

  

　　![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/image.png)

  

### 2. 使用

  

```C++

#include<deque>  // 头文件

deque<type> deq;  // 声明一个元素类型为type的双端队列que

deque<type> deq(size);  // 声明一个类型为type、含有size个默认值初始化元素的的双端队列que

deque<type> deq(size, value);  // 声明一个元素类型为type、含有size个value元素的双端队列que

deque<type> deq(mydeque);  // deq是mydeque的一个副本

deque<type> deq(first, last);  // 使用迭代器first、last范围内的元素初始化deq

  

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

  

### 3. 案例

  

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

  }                                  /*此时队列里的内容是: {8,6,4,2,0,1,3,5,7,9}*/

  q.pop_front();

  printf("%d\n", q.front());    /*清除第一个元素后输出第一个(6)*/

  q.pop_back();

  printf("%d\n", q.back());     /*清除最后一个元素后输出最后一个(7)*/

  deque<int>::iterator it;

  for (it = q.begin(); it != q.end(); it++) {

    cout << *it << '\t';

  }

  cout << endl;

  system("pause");

  return 0;

}

```



## set


### 1. set的简介

　　关于set，必须说明的是set关联式容器。set作为一个容器也是用来存储同一数据类型的数据类型，并且能从一个数据集合中取出数据，在set中每个元素的值都 **唯一** ，而且系统能 **根据元素的值自动进行排序** （默认按键值升序排列）。应该注意的是set中数元素的值不能直接被改变。

  

　　set的含义是集合，它是一个有序的容器，里面的元素都是排序好的支持插入、删除、查找等操作，就像一个集合一样，所有的操作都是严格在log(n)时间内完成，效率非常高。是,set插入的元素不能相同，set默认是自动排序的，**键和值相等且唯一。**元素默认按升序排列。

  

　　访问元素的时间复杂度是：O(log n)

  

### 2. set的功能

  

　　特点：

  

1. set中的元素都是排好序的

2. set集合中没有重复的元素

3. 储存同一类型的数据元素（这点和vector、queue等其他容器相同）

4. 根据元素的值自动排列大小（有序性）

5. 每个元素的值都唯一（没有重复的元素）——>可以用来排序

6. 高效的插入删除操作

7. 无法直接修改元素

8. 不能使用下标法，只能使用迭代器

  

### 3. set的使用
　　头文件
```C++
#include<set>;
```
　　set具有[迭代器](https://so.csdn.net/so/search?q=%E8%BF%AD%E4%BB%A3%E5%99%A8&spm=1001.2101.3001.7020)`set<int>::iterator i` 定义一个迭代器,名为i `可以把迭代器理解为C语言的指针`
### 4. set的常用函数

```C++

begin()     　　  ,返回set容器第一个元素的迭代器

end() 　　　　     ,返回一个指向当前set末尾元素的下一位置的迭代器.

clear()   　　     ,删除set容器中的所有的元素

empty() 　　　     ,判断set容器是否为空

max_size() 　     ,返回set容器可能包含的元素最大个数

size() 　　　　     ,返回当前set容器中的元素个数

rbegin()　　　　    ,返回的值和end()相同

rend()　　　　      ,返回的值和begin()相同

//

set<int> q;     //以int型为例 默认按键值升序

set<int,greater<int>> p;  //降序排列

int x;

q.insert(x);  //将x插入q中

q.erase(x);    //删除q中的x元素,返回0或1,0表示set中不存在x

q.clear();    //清空q

q.empty();    //判断q是否为空，若是返回1，否则返回0

q.size();    //返回q中元素的个数

q.find(x);    //在q中查找x，返回x的迭代器，若x不存在，则返回指向q尾部的迭代器即 q.end()

q.lower_bound(x); //返回一个迭代器，指向第一个键值不小于x的元素

q.upper_bound(x); //返回一个迭代器，指向第一个键值大于x的元素

  

q.rend();      //返回第一个元素的的前一个元素迭代器

q.begin();      //返回指向q中第一个元素的迭代器

  

q.end();     //返回指向q最后一个元素下一个位置的迭代器

q.rbegin();     //返回最后一个元素

  
  

```

  

### 5. set单元素应用

  

```C++

#include<iostream>

#include<set>

using namespace std;

int main()

{

  set<int> q;   //默认按升序排列

  q.insert(5);

  q.insert(5);

  q.insert(5);

  cout<<"q.size "<<q.size()<<endl;   //输出 1 ,在set插入中相同元素只会存在一个

  q.clear(); //清空set

  cout<<"q.size "<<q.size()<<"\n\n";

  q.insert(4);

  q.insert(4);

  q.insert(3);

  q.insert(3);

  q.insert(2);

  q.insert(1);

  cout<<"lower_bound "<<*q.lower_bound(3)<<endl;  //返回3

  cout<<"upper_bound "<<*q.upper_bound(3)<<"\n\n";  //返回4

  set<int>::iterator i;

  for( i=q.begin();i!=q.end();i++)   //set的遍历

    cout<<*i<<" ";           //输出1 2 3 4，可见自动按键值排序

  cout<<endl;

  q.erase(4);  //删除q中的 4

  for(i=q.begin();i!=q.end();i++)  //再次遍历set 只输出 1 2 3

    cout<<*i<<" ";

  cout<<"\n\n";

  set<int,greater<int>> p;  //降序排列

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

  

  

### 6. set多元素应用（结构体）

  

```C++

#include<iostream>

#include<set>

using namespace std;

struct node{

  int a,b;

  bool operator< (const node W)const

  {

    return a>W.a;  //按a的值升序

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

  set<int>::iterator  it = a.begin();

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



## map

### 1. map的简介
　　map是STL的一个关联容器，它提供一对一的[hash](https://blog.csdn.net/guidao13/article/details/84104526?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165028169216780271584890%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165028169216780271584890&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-84104526.142%5Ev9%5Econtrol,157%5Ev4%5Econtrol&utm_term=hash&spm=1018.2226.3001.4187)
* 第一个可以称为关键字(key)，每个关键字只能在map中出现一次；
* 第二个可称为该关键字的值(value)；
如果说set对应数学中的“集合”，那么map对应的就是“映射”。map是一种key-value型容器，其中key是关键字，起到索引作用，而value就是其对应的值。与set不同的是它支持下标访问。头文件是<map>。

map以模板(泛型)方式实现，可以存储任意类型的数据，包括使用者自定义的数据类型。Map主要用于资料一对一映射(one-to-one)的情況，map內部的实现自建一颗红黑树，这颗树具有对数据自动排序的功能。在map内部所有的数据都是有序的，后边我们会见识到有序的好处。比如一个班级中，每个学生的学号跟他的姓名就存在著一对一映射的关系。


### 2. map的功能

  特点:
	  自动建立key-value的对应，key和value可以是任何你需要的类型，包括自定义类型
	  
	  增加和删除节点对迭代器的影响很小(高效的插入与删除)
	  
	  可以根据key修改value的记录
	  
	  支持下标[]操作
	  
	  快速的查找（同set）

  


### 3. map的使用
　头文件：
```C++
#include<map>;//注意，STL头文件没有扩展名.h
```

map对象是模板类，需要关键字和存储对象两个模板参数：

std:map<int, string> personnel;//这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.

为了使用方便，可以对模板类进行一下类型定义，

typedef map<int,CString> UDT_MAP_INT_CSTRING;

UDT_MAP_INT_CSTRING enumMap;




### 4. map的构造函数

  

　　map共提供了6个构造函数，这块涉及到**内存分配器**这些东西，略过不表，在下面我们将接触到一些map的构造方法，这里要说下的就是，我们通常用如下方法构造一个map：

  

```C++

map<int, string> mapStudent;

```

  

### 5. 插入元素

  

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

  

### 6. 查找元素

  

　　当所查找的关键key出现时，它返回数据所在对象的位置，如果沒有，返回iter与end函数的值相同。

  

```C++

//find返回迭代器指向当前查找元素的位置否则返回map::end()位置

iter = mapStudent.find("123");

if(iter != mapStudent.end())

       cout<<"Find, the value is"<<iter->second<<endl;

else

   cout<<"Do not Find"<<endl;

```

  

### 7. 删除与清空元素

  

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

  

### 8. map的大小

  

```C++

int nSize = mapStudent.size();

```

  

### 9. map的基本操作函数

  

```C++

begin()         返回指向map头部的迭代器

clear(）        删除所有元素

count()         返回指定元素出现的次数, (帮助评论区理解： 因为key值不会重复，所以只能是1 or 0)

empty()         如果map为空则返回true

end()           返回指向map末尾的迭代器

equal_range()   返回特殊条目的迭代器对

erase()         删除一个元素

find()          查找一个元素

get_allocator() 返回map的配置器

insert()        插入元素

key_comp()      返回比较元素key的函数

lower_bound()   返回键值>=给定元素的第一个位置

max_size()      返回可以容纳的最大元素个数

rbegin()        返回一个指向map尾部的逆向迭代器

rend()          返回一个指向map头部的逆向迭代器

size()          返回map中元素的个数

swap()           交换两个map

upper_bound()    返回键值>给定元素的第一个位置

value_comp()     返回比较元素value的函数

(*it)->first     key

(*it)->second    value

```

  

### 10. 案例

  

```C++

#include <bits/stdc++.h>

#include <map>

  

using namespace  std;

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

## stack

### 1. stack的简介

  

　　stack翻译为 **栈** 。

  

1. **后进先出** , **先进后出**

2. 不允许遍历

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755835493.png)


### 2. stack的功能

  

　　**特点：**

  

　　由于栈是一种有序列表，故可以使用数组模拟。

  

### 3. stack的使用

  

　　头文件：

  

```C++

#include<stack>;//注意，STL头文件没有扩展名.h

  

```

  

　　map对象是模板类，需要关键字和存储对象两个模板参数：

  

```C++

stack<typename> name;//这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.

```

  

### 4. stack容器内元素的访问

  

　　由于栈(stack)本身就是一种后进先出的数据结构，在STL的 stack中只能通过top()来访问栈顶元素

  

```C++

#include<cstdio>

#include<stack>

using namespace std;

int main(){

  stack<int> st;

  for(int i=1;i<=5;i++){

    st.push(i);    //push(i)将i压入栈

  }

  printf("%d\n",st.top());   //top()取栈顶元素

  return 0;

}

```

  

### 5. stack常用函数实例解析

  

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

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

  }

  for(int i=1;i<=3;i++){

    st.pop();    //pop()将栈顶元素出栈，即将5 4 3 依次出栈

  }

  printf("%d\n",st.top());   //top()取栈顶元素

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

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

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

    st.push(i);    //push(i)将i压入栈 ,1 2 3 4 5 依次入栈

  }

  printf("%d\n",st.size());

  return 0;

}

```

  

　　运行结果：


![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1672755931421.png)


　　注意：  

在使用pop()和top()函数之前必须先使用empty()函数判断栈是否为空。



## list



### 1.list的介绍

  

　　STL链表是序列性容器的模板类，它将其元素保持在线性排列中，链式结构，并允许在序列中的任何位  

置进行有效的插入和删除。

  

#### 链表

  

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

  

### 2. list的构造函数

  

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

  

### 3.list的赋值和交换

  

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

  

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/8d98764588e79cb5cd5b6c1643c687e.png)

  

#### 方法

  

　　front() 获取头节点元素

  

　　back() 获取尾节点元素

  

　　size()  获取长度

  

　　empty()  判空

  

　　clear()


# C++11
## auto

### 定义
C++11 赋予 auto 关键字新的含义，使用它来做自动类型推导。也就是说，使用了 auto 关键字以后，编译器会在编译期间自动推导出变量的类型，这样我们就不用手动指明变量的数据类型了。
auto 关键字基本的使用语法如下：

`auto name = value;`
### 使用方法

单独使用
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int x = 0;     //
  auto b = x;    // b的类型自动推导为int
  auto c = &x;   // c的类型自动推导为int*
  auto d = 12.3; // d的类型自动double
  return 0;
}
```
`g++ -std=c++11 auto.cpp -o auto.out`
组合使用

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int x = 0;   
  //组合使用
  auto *p1 = &x; // p1 为 int *，auto 推导为 int
  auto p2 = &x;  // p2 为 int*，auto 推导为 int*
  auto &r1 = x;  // r1 为 int&，auto 推导为 int
  auto r2 = r1;  // r2 为  int，auto 推导为 int
  return 0;
}
```

auto 和const使用
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  int x = 0;
  const auto n = x;     // n 为 const int ，auto 被推导为 int
  auto f = n;           // f 为 const int，auto 被推导为 int（const 属性被抛弃）
  const auto &r1 = x;   // r1 为 const int& 类型，auto 被推导为 int
  auto &r2 = r1;        // r1 为 const int& 类型，auto 被推导为 const int 类型
  return 0;
}
```
auto 与 const 结合的用法：
-   当类型不为引用时，auto 的推导结果将不保留表达式的 const 属性；
-   当类型为引用时，auto 的推导结果将保留表达式的 const 属性。
### auto应用
#### 定义stl迭代器
```cpp
#include <vector>
using namespace std;

int main(){
    vector< vector<int> > v;
    vector< vector<int> >::iterator i = v.begin();
    return 0;
}
```

```cpp
#include <vector>
using namespace std;

int main(){
    vector< vector<int> > v;
    auto i = v.begin();  //使用 auto 代替具体的类型
    return 0;
}
```
#### 用于泛型编程
```cpp
#include <iostream>
using namespace std;

class A{
public:
    static int get(void){
        return 100;
    }
};

class B{
public:
    static const char* get(void){
        return "http://c.biancheng.net/cplus/";
    }
};

template <typename T>
void func(void){
    auto val = T::get();
    cout << val << endl;
}

int main(void){
    func<A>();
    func<B>();

    return 0;
}
```
### auto的限制
	1) 使用 auto 的时候必须对变量进行初始化
	2) auto 不能在函数的参数中使用。这个应该很容易理解，我们在定义函数的时候只是对参数进行了声明，指明了参数的类型，但并没有给它赋值，只有在实际调用函数的时候才会给参数赋值；而 auto 要求必须对变量进行初始化，所以这是矛盾的。
	3) auto 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中。
	4) auto 关键字不能定义数组
	5) auto 不能作用于模板参数，请看下面的例子：

```cpp
template <typename T>
class A{
    //TODO:
};

int  main(){
    A<int> C1;
    A<auto> C2 = C1;  //错误
    return 0;
}
```

## decltype

decltype 是 [C++](http://c.biancheng.net/cplus/)11 新增的一个关键字，它和 [[auto]] 的功能一样，都用来在**编译时期进行自动类型推导**。

decltype 是“declare type”的缩写，译为“声明类型”。

既然已经有了 auto 关键字，为什么还需要 decltype 关键字呢？因为 auto 并不适用于所有的自动类型推导场景，在某些特殊情况下 auto 用起来非常不方便，甚至压根无法使用，所以 decltype 关键字也被引入到 C++11 中。
### 与auto的区别
auto 和 decltype 关键字都可以自动推导出变量的类型，但它们的用法是有区别的：
```cpp
auto varname = value;  
decltype(exp) varname = value;
```
其中，varname 表示变量名，value 表示赋给变量的值，exp 表示一个表达式。

auto 根据`=`右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟`=`右边的 value 没有关系。
### auto 要求变量必须初始化，而 decltype 不要求。
这很容易理解，auto 是根据变量的初始值来推导出变量类型的，如果不初始化，变量的类型也就无法推导了。decltype 可以写成下面的形式：
`decltype(exp) varname;`

### 注意事项
原则上讲，exp 就是一个普通的表达式，它可以是任意复杂的形式，但是我们必须要保证 exp 的结果是有类型的，不能是 void；
例如，当 exp 调用一个返回值类型为 void 的函数时，exp 的结果也是 void 类型，此时就会导致**编译错误**。
### decltype推导规则
	1.  如果 exp 是一个不被括号`( )`包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，那么decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况。
	2.  如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致。需要注意的是，exp 中调用函数时需要带上括号和参数，但这仅仅是形式，并不会真的去执行函数代码。
	4.  如果 exp 是一个左值，或者被括号`( )`包围，那么 decltype(exp) 的类型就是 exp 的引用；假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。


[[左值和右值]]

```cpp
using namespace std;

class Base{
public:
    int x;
};

int main(){
    const Base obj;

    //带有括号的表达式
    decltype(obj.x) a = 0;  //obj.x 为类的成员访问表达式，符合推导规则一，a 的类型为 int
    decltype((obj.x)) b = a;  //obj.x 带有括号，符合推导规则三，b 的类型为 int&。

    //加法表达式
    int n = 0, m = 0;
    decltype(n + m) c = 0;  //n+m 得到一个右值，符合推导规则一，所以推导结果为 int
    decltype(n = n + m) d = c;  //n=n+m 得到一个左值，符号推导规则三，所以推导结果为 int&

    return 0;
}
```

### decltype的应用
auto 的语法格式比 decltype 简单，所以在一般的类型推导中，使用 auto 比使用 decltype 更加方便
auto 只能用于类的静态成员，不能用于类的非静态成员（普通成员），如果我们想推导非静态成员的类型，这个时候就必须使用 decltype 了。
```cpp
#include <vector>
using namespace std;

template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }

private:
    typename T::iterator m_it;  //注意这里
};

int main()
{
    const vector<int> v;
    Base<const vector<int>> obj;
    obj.func(v);

    return 0;
}
```

单独看 Base 类中 m_it 成员的定义，很难看出会有什么错误，但在使用 Base 类的时候，如果传入一个 const 类型的容器，编译器马上就会弹出一大堆错误信息。原因就在于，`T::iterator`并不能包括所有的迭代器类型，当 T 是一个 const 容器时，应当使用 const_iterator。

要想解决这个问题，在之前的 C++98/03 版本下只能想办法把 const 类型的容器用模板特化单独处理，增加了不少工作量，看起来也非常晦涩。但是有了 C++11 的 decltype 关键字，就可以直接这样写：
```cpp
template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }

private:
    decltype(T().begin()) m_it;  //注意这里
};
```

## {}初始化

在C++98中，标准允许使用花括号{}对数组或者结构体元素进行统一的列表初始值设定。C++11扩大了用大括号括起的列表(初始化列表)的使用范围，使其可用于所有的内置类型和用户自定义的类型，使用初始化列表时，可添加等号(=)，也可不添加。

```cpp
int main()
{
	int x1 = 1;
    //我们知道有不加等号这种写法即可，自己写的时候最好还是要加上
	int x2{ 2 };
	int array1[]{ 1, 2, 3, 4, 5 };
	int array2[5]{ 0 };
	// C++11中列表初始化也可以适用于new表达式中
	int* pa = new int[4]{ 0 };
	return 0;
}

```
同时也可以用来初始化对象：
```cpp
class Date
{
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int year, int month, int day)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2022, 1, 1); // old style
	// C++11支持的列表初始化，这里会调用构造函数初始化
	Date d2{ 2022, 1, 2 };
	Date d3 = { 2022, 1, 3 };
	return 0;
}
```

## 右值引用和移动语义

### 概念

传统的C++语法中就有引用的语法，而C++11中新增了的右值引用语法特性，所以从现在开始我们  
之前学习的引用就叫做[左值](https://so.csdn.net/so/search?q=%E5%B7%A6%E5%80%BC&spm=1001.2101.3001.7020)引用。无论左值引用还是右值引用，都是给对象取别名。
**什么是左值？什么是右值？**

左值可以取地址，可以出现在等号左边，可以改变值的大小（const类型除外）。
右值不可以被取地址，不可以出现在等号左边，只能出现在等号右边，不可以改变值的大小。右值一般有两种，一种是纯右值，一种是将亡值（函数返回的临时变量）。
### 左值引用和右值引用比较
#### 右值
左值引用总结：

-   左值引用一般情况下只能引用左值，不能引用右值。
-   但是const左值引用既可以引用左值也可以引用右值。
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  //左值引用只能引用左值
  int a = 10;
  int &ra1 = a; // ra1 为a的别名

  // int& ra2 =10;//cannot bind non-const lvalue reference of type ‘int&’ to an
  // rvalue of type ‘int’ 不能将左值引用和右值绑定

  // const左值引用既可以引用左值，也可以引用右值
  const int &ra3 = a;
  const int &ra4 = 10;
  return 0;
}
```
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1674703917662.png)
### 右值
 右值引用总结：

-   右值引用只能右值，不能引用左值。
-   但是右值引用可以move以后的左值。move是一个函数，可以将左值转化为右值。
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
	//右值引用只能引用右值
	int&& r1 =10;

	int a=10;
	//int&& r2 = a;//error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’

	//右值引用可以引用move之后的左值
	int&& r3 =move(a);
	return 0;
}
```

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/1674705877160.png)
需要注意的是，右值虽然不能被取地址，但右值被取别名后会存储到特定的位置，这个特定位置的地址是可以被取地址的。也就是说字面量10为右值不能被取地址，但是右值引用取别名为r1后，r1的地址是可以取到的，并且r1的值是可以被修改的，如果不想rr1被修改，可以用const int&& r1 去引用。当然右值引用的实际用处并不在此，只需要了解即可。
# 动态库和静态库
动态库和静态库

## 为什么使用库

团队之间的协作，只提供给函数接口，提供库，隐藏了函数的实现路逻辑
注意：静态和动态磁盘中都存很多份，没区别。
## 静态库和动态库优缺点
### 静态库：
链接期把库放入内存
优点：
	快
缺点：
1. 每个调用的应用程序都会拷贝一份静态库，占内存
2. 一旦库修改，（库在可执行文件里）需要整体重新编译
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115185243.png)
### 动态库：
链接期只放入库的索引
缺点：
	慢
优点：
1. 多个应用程序调用同一个动态库，同时运行时，不需要重复拷贝，只需要一份
2. 更新步数简单，库修改时，用户只需要重新下载库

## 实际操作
### 静态库
#### 创建一个自己的静态库
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115194635.png)

![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115194714.png)
#### 使用静态库
在测试项目中
1. 建立文件夹，include和lib把头文件和库文件拷贝到当前项目中
		![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115194934.png)
		![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115195036.png)
		![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115195141.png)
2.  添加依赖的头文件
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115195202.png)
3. 导入依赖库
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115195224.png)
4. 成功调用运行
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115195322.png)
### 动态库
#### 创建一个自己的动态库
动态库中的函数需要声明导出，这个函数才会出现在索引里。
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202649.png)
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202700.png)
#### 使用动态库
1、把头文件和库文件(.lib)拷贝到当前项目中
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202823.png)
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202913.png)
2、添加依赖的头文件
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202936.png)
3、导入依赖库
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115202952.png)
4、生成.exe
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115203113.png)
5、将动态库生成的.dll文件放入和exe同一目录
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115203228.png)
6、调用运行
![](https://liuhao-aliyun-oss.oss-cn-beijing.aliyuncs.com/Pasted%20image%2020221115203444.png)

后续对动态库的函数实现进行更改，只需要将测试项目中的dll文件更新就可以了，而不用重新编译项目文件