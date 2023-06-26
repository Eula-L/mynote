#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  int a = 0;
  decltype(a) b = 1;      // b 被推导成了 int
  decltype(10.8) x = 5.5; // x 被推导成了 double
  decltype(x + 100) y;    // y 被推导成了 double
  return 0;
}
