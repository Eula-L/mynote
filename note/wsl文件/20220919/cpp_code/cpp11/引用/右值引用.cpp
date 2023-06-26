#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
	// 右值引用只能引用右值
	int &&r1 = 10;

	int a = 10;
	// int&& r2 = a;//error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’

	// 右值引用可以引用move之后的左值
	int &&r3 = move(a);
	return 0;
}
