#include <iostream>
using namespace std;
class CStepFather
{
public:
    int m_a;
    CStepFather()
    {
        m_a = 10;
    }
    CStepFather(int a)
    {
        m_a = a;
    }
};

class CSon
{
public:
    CStepFather m_stepFa; // 包含另一个类的对象
    int m_son;

public:
    CSon() /*：m_stepFa() */
    {      // 当包含另一个类的对象，编译器会自动调用无参的构造进行初始化
        m_son = 20;
    }
    CSon(int a) : m_stepFa(a)
    { // 如果想调用带参数的构造函数进行初始化，需要手动显式指定
        m_son = 20;
    }
    CSon(int a, int b) : m_stepFa(a)
    {
        // 如果另一个类中没有无参的构造函数，必须显式的指定带参数的构造函数，如果什么也不指定，会报错
        m_son = 20;
    }
};

int main()
{
    CSon son;
    cout << son.m_son << "  " << son.m_stepFa.m_a << endl;
    CSon son2(100); // 匹配的是CSon和CStepFather的带参数的构造函数
    cout << son2.m_son << "   " << son2.m_stepFa.m_a << endl;
    return 0;
}