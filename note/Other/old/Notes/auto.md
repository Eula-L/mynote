# 定义
C++11 赋予 auto 关键字新的含义，使用它来做自动类型推导。也就是说，使用了 auto 关键字以后，编译器会在编译期间自动推导出变量的类型，这样我们就不用手动指明变量的数据类型了。
auto 关键字基本的使用语法如下：

`auto name = value;`
# 使用方法

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
[[g++编译c++11]]
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
# auto应用
## 定义stl迭代器
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
## 用于泛型编程
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
# auto的限制
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