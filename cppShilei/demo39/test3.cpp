#include <iostream>

using namespace std;

class Base {
   public:
    virtual void show() { cout << "call Base::show" << endl; }
};
class Derive : public Base {
   private:
    void show() { cout << "call Derive::show" << endl; }
};
int main() {
    Base* p = new Derive();
    // 成员方法能不能调用，就是说方法的访问权限是不是public的，是在编译阶段就需要确定好的
    // 编译阶段只能看见 Base::show
    // 静态绑定call Base::show   动态绑定call ecx

    // 编译阶段看到的p指针是Base指针，show是public的
    p->show();  // 最终能调用到Derive::show，是在运行时期才确定的
    // 运行结果
    // call Derive::show
    delete p;
    return 0;
}
