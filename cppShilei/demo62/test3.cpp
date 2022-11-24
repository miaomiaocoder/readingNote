#include <iostream>
#include <memory>
using namespace std;

// 定义对象的时候，用强智能指针；引用对象的地方，使用弱智能指针

class B;  // 前置声明类B
class A {
   public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    void testA() { cout << "非常好用的方法！" << endl; }
    weak_ptr<B> _ptrb;  // 指向B对象的智能指针
};
class B {
   public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
    void func() {
        // _ptra->testA();
        shared_ptr<A> ps = _ptra.lock();  // 提升方法
        if (ps != nullptr) {
            ps->testA();
        }
    }
    weak_ptr<A> _ptra;  // 指向A对象的智能指针
};
int main() {
    shared_ptr<A> ptra(new A());  // ptra指向A对象，A的引用计数为1
    shared_ptr<B> ptrb(new B());  // ptrb指向B对象，B的引用计数为1
    ptra->_ptrb = ptrb;
    ptrb->_ptra = ptra;

    cout << ptra.use_count() << endl;
    cout << ptrb.use_count() << endl;

    ptrb->func();

    return 0;
}
/*
$ ./test3
A()
B()
1
1
非常好用的方法！
~B()
~A()
*/