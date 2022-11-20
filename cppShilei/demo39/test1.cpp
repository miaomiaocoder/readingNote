#include <iostream>
#include <string>

using namespace std;

class Animal {
   public:
    Animal(string name) : _name(name) {}
    // 纯虚函数
    virtual void bark() = 0;

   protected:
    string _name;
};
// 以下是动物实体类
class Cat : public Animal {
   public:
    Cat(string name) : Animal(name) {}
    void bark() { cout << _name << " bark: miao miao!" << endl; }
};
class Dog : public Animal {
   public:
    Dog(string name) : Animal(name) {}
    void bark() { cout << _name << " bark: wang wang!" << endl; }
};
int main() {
    Animal *p1 = new Cat("加菲猫");  // 由于下面代码vfptr -> Dog vftable
    Animal *p2 = new Dog("二哈");    // 由于下面代码vfptr -> Cat vftable

    int *p11 = (int *)p1;
    int *p22 = (int *)p2;
    int tmp = p11[0];  // p11[0]访问的就是Cat的前4个字节
    p11[0] = p22[0];   // p22[0]访问的就是Dog的前4个字节
    p22[0] = tmp;

    p1->bark();  // p1 -> Cat vfptr -> Dog vftable bark
    p2->bark();  // p2 -> Dog vfptr -> Cat vftable bark

    delete p1;
    delete p2;

    return 0;
}
