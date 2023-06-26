#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  //函数声明
  int &func_int_r(int, char); //返回值为 int&
  int &&func_int_rr(void);    //返回值为 int&&
  int func_int(double);       //返回值为 int

  const int &fun_cint_r(int, int, int); //返回值为 const int&
  const int &&func_cint_rr(void);       //返回值为 const int&&

  // decltype类型推导
  int n = 100;
  decltype(func_int_r(100, 'A')) a = n; // a 的类型为 int&
  decltype(func_int_rr()) b = 0;        // b 的类型为 int&&
  decltype(func_int(10.5)) c = 0;       // c 的类型为 int

  decltype(fun_cint_r(1, 2, 3)) x = n; // x 的类型为 const int &
  decltype(func_cint_rr()) y = 0;      // y 的类型为 const int&&
  return 0;
}
