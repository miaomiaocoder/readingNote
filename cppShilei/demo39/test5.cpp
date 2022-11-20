#include <cstring>
#include <iostream>

using namespace std;

class Base {
   public:
    Base() {
        /*
        push ebp
        mov ebp, esp
        sub esp, 4Ch
        rep stos esp<->ebp 0xCCCCCCCC(windows VS)
        vfptr <- &Base::vftable
        */
        cout << "call Base()" << endl;
        clear();
    }
    void clear() { memset(this, 0, sizeof(*this)); }
    virtual void show() { cout << "call Base::show()" << endl; }
};
class Derive : public Base {
   public:
    Derive() {
        /*
        push ebp
        mov ebp, esp
        sub esp, 4Ch
        rep stos esp<->ebp 0xCCCCCCCC(windows VS)
        vfptr <- &Derive::vftable
        */
        cout << "call Derive()" << endl;
    }
    void show() { cout << "call Derive::show()" << endl; }
};
int main() {
    // Base *pb1 = new Base();
    // /*
    // mov eax, dword ptr[pb1]
    // mov ecx, dword ptr[eax] eax:0x00000000 不是Base::vftable
    // call ecx
    // */
    // pb1->show(); // 动态绑定
    // delete pb1;
    // 运行结果
    // call Base()
    // (进程 17804)已退出，代码为 -1073741819。

    Base *pb2 = new Derive();
    // 动态绑定 call Derive::show()
    /*
    vfptr里面存储的是vftable的地址
    vfptr <- vftable
    */
    pb2->show();
    delete pb2;
    // 运行结果
    // call Base()   vfptr被清空
    // call Derive()   vfptr被写入 &Derive::vftable
    // call Derive::show()

    return 0;
}