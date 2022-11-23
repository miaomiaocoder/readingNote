#include <iostream>

using namespace std;

class Test {
   public:
    Test(int a = 10) : ma(a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& t) : ma(t.ma) { cout << "Test(const Test&)" << endl; }
    Test& operator=(const Test& t) {
        cout << "operator=" << endl;
        ma = t.ma;
        return *this;
    }

   private:
    int ma;
};
int main() {
    Test t1;
    Test t2(t1);
    Test t3 = t1;
    // Test(20) 显示生成临时对象  生存周期：所在的语句
    /*
    C++编译器对于对象构造的优化：用临时对象生成新对象的时候，临时对象
    就不产生了，直接构造新对象就可以了
    */
    Test t4 = Test(20);  // Test t4(20);没有区别的！
    cout << "--------------" << endl;

    // t4.operator=(t2)
    t4 = t2;
    // t4.operator=(const Test &t)
    // 显式生成临时对象
    t4 = Test(30);
    t4 = (Test)30;  // int->Test(int)

    cout << "--------------" << endl;

    // 隐式生成临时对象
    t4 = 30;  // Test(30) int->Test(int) -> 正确
    // char*->Test(char*) ->错误

    cout << "--------------" << endl;
    // p指向的是一个已经析构的临时对象
    // Test* p = &Test(40); // error C2102: “&”要求左值

    const Test& ref = Test(50);
    cout << "--------------" << endl;

    return 0;
}