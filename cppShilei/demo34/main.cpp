#include <iostream>

using namespace std;

/*
虚函数，静态绑定和动态绑定

覆盖：
基类和派生类的方法，返回值、函数名以及参数列表都相同，而且基类的方法是虚函数，
那么派生类的方法就自动处理成虚函数，它们之间成为覆盖关系

一个类添加了虚函数，对这个类有什么影响？
总结一：
一个类里面定义了虚函数，那么编译阶段，编译器给这个类类型产生一个唯一的vftable虚函数
表，虚函数表中主要存储的内容就是RTTI指针和虚函数的地址。当程序运行时，每一张虚函数表
都会加载到内存的.rodata区。

总结二：
一个类里面定义了函数数，那么这个类定义的对象，其运行时，内存中开始部分，多存储一个
vfptr虚函数指针，指向相应类型的虚函数表vftable。一个类型定义的n个对象，它们的额vfptr
指向的都是同一张虚函数表

总结三：
一个类里面虚函数的个数，不影响对象内存大小（vfptr），影响的是虚函数表的大小
*/
class Base {
   public:
    Base(int data = 10) : ma(data) {}
    // 虚函数
    virtual void show() { cout << "Base::show()" << endl; }
    // 虚函数
    virtual void show(int) { cout << "Base::show(int)" << endl; }

   protected:
    int ma;
};
class Derive : public Base {
   public:
    Derive(int data = 20) : Base(data), mb(data) {}
    /*
    总结四：
    如果派生类中的方法，和基类继承来的某个方法，返回值、函数名、参数列表都相同，
    而且基类的方法是virtual虚函数，那么派生类的这个方法，自动处理成虚函数
    重写《=》覆盖
    */
    void show() { cout << "Derive::show()" << endl; }

   private:
    int mb;
};
int main() {
    Derive d(50);
    Base *pb = &d;

    /*
    pb->Base Base::show 如果发现show是普通函数，就进行静态绑定 call Base::show
    pb->Base Base::show 如果发现show是虚函数，就进行动态绑定了
    mov eax, dword ptr[pb]
    mov ecx, dword ptr[eax]
    call ecx（虚函数的地址） 动态（运行时期）的绑定（函数的调用）
    */
    pb->show();  //静态（编译时期）的绑定（函数的调用）call Base::show(01612DAh)

    /*
    Base::show(int) 是一个虚函数，此时就得动态绑定了
    mov eax, dword ptr[pb]
    mov ecx, dword ptr[eax]
    call ecx（虚函数的地址） 动态（运行时期）的绑定（函数的调用）
    */
    pb->show(10);  //静态绑定 call  Base::show (01612B2h)

    cout << sizeof(Base) << endl;    // 8
    cout << sizeof(Derive) << endl;  // 12

    cout << typeid(pb).name() << endl;  // class Base*
    /*
    pb的类型：Base -> 有没有虚函数
    如果Base没有虚函数，*pb识别的就是编译时期的类型  *pb <=> Base类型
    如果Base有虚函数，*pb识别的就是运行时期的类型 RTTI类型
    pb->d(vfptr)->Derive vftable  class Derive
    */
    cout << typeid(*pb).name() << endl;  // class Base  class Derive
    /*
    Base的两个show函数都是普通的函数
    Base::show()
    Base::show(int)
    4
    8
    class Base *
    class Base
    */

    /*
    给Base的两个show方法定义成virtual虚函数了
    Derive::show()
    Base::show(int)
    8
    12
    class Base *
    class Derive
    */

    return 0;
}