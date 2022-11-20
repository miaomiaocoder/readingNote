#include <iostream>

using namespace std;

class Base {
   public:
    virtual void show(int i = 10) { cout << "call Base::show i:" << i << endl; }
};
class Derive : public Base {
   public:
    void show(int i = 20) { cout << "call Derive::show i:" << i << endl; }
};
int main() {
    Base *p = new Derive();  // 如果有析构函数应声明为虚析构函数
    /*
    push 0Ah => 函数调用，参数压栈是在编译时期就确定好的
    mov eax, dword ptr[p]
    mov ecx, dword ptr[eax]
    call ecx
    */
    p->show();  // 动态绑定 p-> Derive vfptr -> Derive vftable
    delete p;
    // 运行结果
    // call Derive::show i:10

    Base *p2 = new Derive();
    p2->show(500);
    delete p2;
    // 运行结果
    // call Derive::show i:500

    return 0;
}