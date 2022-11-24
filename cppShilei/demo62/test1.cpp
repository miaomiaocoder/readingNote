#include <iostream>
#include <memory>
using namespace std;

class B;  // 前置声明类B
class A {
   public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    shared_ptr<B> _ptrb;  // 指向B对象的智能指针
};
class B {
   public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
    shared_ptr<A> _ptra;  // 指向A对象的智能指针
};
int main() {
    shared_ptr<A> ptra(new A());  // ptra指向A对象，A的引用计数为1
    shared_ptr<B> ptrb(new B());  // ptrb指向B对象，B的引用计数为1
    ptra->_ptrb = ptrb;  // A对象的成员变量_ptrb也指向B对象，B的引用计数为2
    ptrb->_ptra = ptra;  // B对象的成员变量_ptra也指向A对象，A的引用计数为2

    cout << ptra.use_count() << endl;  // 打印A的引用计数结果:2
    cout << ptrb.use_count() << endl;  // 打印B的引用计数结果:2

    /*
    出main函数作用域，ptra和ptrb两个局部对象析构，分别给A对象和
    B对象的引用计数从2减到1，达不到释放A和B的条件（释放的条件是
    A和B的引用计数为0），因此造成两个new出来的A和B对象无法释放，
    导致内存泄露，这个问题就是“强智能指针的交叉引用(循环引用)问题”
    */
    return 0;
}
/*
$ ./test1
A()
B()
2
2
*/