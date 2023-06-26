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
	cout<<"hello "<<endl;
    return 0;
}
