// 未声明虚函数情况
#include <iostream>

using namespace std;

class Base {
   public:
    Base(int data) : ma(data) { cout << "Base()" << endl; }
    ~Base() { cout << "~Base()" << endl; }
    void show() { cout << "call Base::show()" << endl; }

   protected:
    int ma;
};
class Derive : public Base {
   public:
    Derive(int data) : Base(data), mb(data), ptr(new int(data)) {
        cout << "Derive()" << endl;
    }
    ~Derive() {
        delete ptr;
        cout << "~Derive()" << endl;
    }

   private:
    int mb;
    int* ptr;
};
int main() {
    Base* pb = new Derive(10);
    pb->show();
    delete pb;  // 派生类的析构函数没有被调用到！！！

    return 0;
}

int mainbak() {
    Derive d(10);
    Base* pt = &d;
    pt->show();

    return 0;
}