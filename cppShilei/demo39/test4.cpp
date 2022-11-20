#include <iostream>

using namespace std;

class Base {
   private:
    virtual void show() { cout << "call Base::show" << endl; }
};
class Derive : public Base {
   public:
    void show() { cout << "call Derive::show" << endl; }
};
// int main() {
//     Base* p = new Derive();
//     // 成员方法能不能调用，就是说方法的访问权限是不是public的，是在编译阶段就需要确定好的
//     // 编译阶段只能看见 Base::show
//     // 静态绑定call Base::show   动态绑定call ecx

//     // error: ‘virtual void Base::show()’ is private within this context
//     p->show();
//     delete p;
//     return 0;
// }

int main() {
    Derive* p = new Derive();
    // 成员方法能不能调用，就是说方法的访问权限是不是public的，是在编译阶段就需要确定好的
    // 编译阶段只能看见 Base::show
    // 静态绑定call Base::show   动态绑定call ecx

    p->show();
    delete p;
    return 0;
}

