decltype 是 [C++](http://c.biancheng.net/cplus/)11 新增的一个关键字，它和 [[auto]] 的功能一样，都用来在**编译时期进行自动类型推导**。

decltype 是“declare type”的缩写，译为“声明类型”。

既然已经有了 auto 关键字，为什么还需要 decltype 关键字呢？因为 auto 并不适用于所有的自动类型推导场景，在某些特殊情况下 auto 用起来非常不方便，甚至压根无法使用，所以 decltype 关键字也被引入到 C++11 中。
# 与auto的区别
auto 和 decltype 关键字都可以自动推导出变量的类型，但它们的用法是有区别的：
```cpp
auto varname = value;  
decltype(exp) varname = value;
```
其中，varname 表示变量名，value 表示赋给变量的值，exp 表示一个表达式。

auto 根据`=`右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟`=`右边的 value 没有关系。
## auto 要求变量必须初始化，而 decltype 不要求。
这很容易理解，auto 是根据变量的初始值来推导出变量类型的，如果不初始化，变量的类型也就无法推导了。decltype 可以写成下面的形式：
`decltype(exp) varname;`

# 注意事项
原则上讲，exp 就是一个普通的表达式，它可以是任意复杂的形式，但是我们必须要保证 exp 的结果是有类型的，不能是 void；
例如，当 exp 调用一个返回值类型为 void 的函数时，exp 的结果也是 void 类型，此时就会导致**编译错误**。
# decltype推导规则
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

# decltype的应用
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