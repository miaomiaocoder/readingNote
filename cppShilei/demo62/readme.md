## shared_ptr 交叉引用问题

#### 代码示例1
```cpp
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
```
#### 代码示例2
```cpp
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
```
#### 代码示例3
```cpp
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
```