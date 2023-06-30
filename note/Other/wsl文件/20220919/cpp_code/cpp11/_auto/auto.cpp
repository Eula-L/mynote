#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int x = 0;
  auto b = x;    // b的类型自动推导为int
  auto c = &x;   // c的类型自动推导为int*
  auto d = 12.3; // d的类型自动double
  // 连续定义多个变量
  int n = 20;
  auto *p = &n, m = 99;
  //先看前面的第一个子表达式，&n 的类型是 int*，编译
  //器会根据 auto *p 推导出 auto 为 int。后面的 m 变
  //量自然也为 int 类型，所以把 99 赋值给它也是正确的。
   
  //组合使用
  auto *p1 = &x; // p1 为 int *，auto 推导为 int
  auto p2 = &x;  // p2 为 int*，auto 推导为 int*
  auto &r1 = x;  // r1 为 int&，auto 推导为 int
  auto r2 = r1;  // r2 为  int，auto 推导为 int
  cout<<n<<endl;
  return 0;
}
