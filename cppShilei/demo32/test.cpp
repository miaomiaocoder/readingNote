#include <iostream>

using namespace std;

/*
1.派生类从继承可以继承来所有的成员(变量和方法)，除过构造函数和析构函数

派生类怎么初始化从基类继承来的成员变量呢？
解答：通过调用基类相应的构造函数来初始化

派生类的构造函数和析构函数，负责初始化和清理派生类部分
派生类从基类继承来的成员，的初始化和清理由谁负责呢？是由基类的构造和析构函数来负责

》》》派生类对象构造和析构的过程是：
1.派生类调用基类的构造函数，初始化从基类继承来的成员
2.调用派生类自己的构造函数，初始化派生类自己特有的成员
.....派生类对象的作用域到期了
3.调用派生类的析构函数，释放派生类成员可能占用的外部资源（堆内存，文件）
4.调用基类的析构函数，释放派生类内存中，从基类继承来的成员可能占用的外部资源（堆内存，文件）
*/
class Base {
   public:
    Base(int data) : ma(data) { cout << "Base()" << endl; }
    ~Base() { cout << "~Base()" << endl; }

   protected:
    int ma;
};
class Derive : public Base {
   public:
    //“Base”: 没有合适的默认构造函数可用
    Derive(int data)
        : Base(data),
          mb(data)  // ma(data)
    {
        cout << "Derive()" << endl;
    }
    ~Derive() { cout << "~Derive()" << endl; }

   private:
    int mb;
};
int main() {
    Derive d(20);

    return 0;
}