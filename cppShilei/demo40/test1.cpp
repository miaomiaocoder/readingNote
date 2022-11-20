#include <iostream>

using namespace std;

/*
多重继承 ：代码的复用   一个派生类有多个基类
class C: public A, public B
{
};

抽象类(有纯虚函数的类) / 虚基类 被虚继承的类称作虚基类
vbptr(virtual base ptr)和vbtable
virtual
1.修饰成员方法是虚函数
2.可以修饰继承方式，是虚继承。被虚继承的类，称作虚基类
*/
class A {
   public:
    virtual void func() { cout << "call A::func" << endl; }

   private:
    int ma;
};
class B : virtual public A {
   public:
    void func() { cout << "call B::func" << endl; }

   private:
    int mb;
};

int main() {
    // 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
    A* p = new B();
    p->func();
    delete p;

    // $ ./test1
    // call B::func
    // free(): invalid pointer
    // Aborted

    return 0;
}