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
