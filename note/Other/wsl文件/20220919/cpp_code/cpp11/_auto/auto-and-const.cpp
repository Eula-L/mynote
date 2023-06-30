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
