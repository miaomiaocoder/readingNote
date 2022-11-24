#include <iostream>
#include <memory>
using namespace std;
/*
shared_ptr: 强智能指针 可以改变资源引用计数
weak_ptr: 弱智能指针 不会改变资源的引用计数
*/
// 定义对象的时候，用强智能指针；引用对象的地方，使用弱智能指针

class B;  // 前置声明类B
class A {
   public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    weak_ptr<B> _ptrb;  // 指向B对象的智能指针
};
class B {
   public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
    weak_ptr<A> _ptra;  // 指向A对象的智能指针
};
int main() {
    shared_ptr<A> ptra(new A());  // ptra指向A对象，A的引用计数为1
    shared_ptr<B> ptrb(new B());  // ptrb指向B对象，B的引用计数为1
    ptra->_ptrb = ptrb;
    ptrb->_ptra = ptra;

    cout << ptra.use_count() << endl;
    cout << ptrb.use_count() << endl;

    return 0;
}
/*
$ ./test2
A()
B()
1
1
~B()
~A()
*/