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
    void operator delete(void *ptr) {
        cout << "operator delete p:" << ptr << endl;
        free(ptr);
    }

   private:
    int ma;
};
class B : virtual public A {
   public:
    void func() { cout << "call B::func" << endl; }

    void *operator new(size_t size) {
        void *p = malloc(size);
        cout << "operator new p:" << p << endl;
        return p;
    }

   private:
    int mb;
};

int main() {
    
    // A *p = new B();
    // cout << "main p:" << p << endl;
    // p->func();
    // delete p;

    // vs运行结果
    /*
    operator new p:00AB7F70
    main p:00AB7F78
    call B::func
    operator delete p:00AB7F78
    (进程 30460)已退出，代码为 3。
    */

    // 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
    B b;
    A *p = &b;  // new B(); // B::vftable
    cout << "main p:" << p << endl;
    p->func();
    // delete p;

    return 0;
}