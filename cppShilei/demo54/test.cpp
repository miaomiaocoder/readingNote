#include <iostream>

using std::cout;
using std::endl;

class Test {
   public:
    // Test()  Test(20)
    Test(int data = 10) : ma(data) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& t) : ma(t.ma) { cout << "Test(const Test&)" << endl; }
    void operator=(const Test& t) {
        cout << "operator=" << endl;
        ma = t.ma;
    }
    int getData() const { return ma; }

   private:
    int ma;
};
// 不能返回局部的或者临时对象的指针或引用
/*
1.函数参数传递过程中，对象优先按引用传递，不要按值传递
2.函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象
3.接收返回值是对象的函数调用的时候，优先按初始化的方式接收，不要按赋值的方式接收
*/
Test GetObject(Test& t) {
    int val = t.getData();
    /*Test tmp(val);
    return tmp;*/
    // 返回临时对象
    return Test(val);
}
int main() {
    Test t1;
    Test t2 = GetObject(t1);
    // t2 = GetObject(t1);
    return 0;
}