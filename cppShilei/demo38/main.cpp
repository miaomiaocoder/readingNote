#include <iostream>

using namespace std;

/*
抽象类和普通类有什么区别？
一般把什么类设计成抽象类？ 基类
*/
// 动物的基类  泛指   类->抽象一个实体的类型
/*
定义Animal的初衷，并不是让Animal抽象某个实体的类型
1.string _name; 让所有的动物实体类通过继承Animal直接复用该属性
2.给所有的派生类保留统一的覆盖/重写接口

拥有纯虚函数的类，叫做抽象类！（Animal）
Animal a; No!!!
抽象类不能再实例化对象了，但是可以定义指针和引用变量
*/
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
class Pig : public Animal {
   public:
    Pig(string name) : Animal(name) {}
    void bark() { cout << _name << " bark: heng heng!" << endl; }
};
void bark(Animal* p) {
    p->bark();  // Animal::bark虚函数，动态绑定了
}

// 汽车的基类
class Car  // 抽象类
{
   public:
    Car(string name, double oil) : _name(name), _oil(oil) {}
    // 获取汽车剩余油量还能跑的公里数
    double getLeftMiles() {
        // 1L 10  *  oil
        return _oil * this->getMilesPerGallon();  // 发生动态绑定了
    }
    string getName() const { return _name; }

   protected:
    string _name;
    double _oil;
    virtual double getMilesPerGallon() = 0;  // 纯虚函数
};
class Bnze : public Car {
   public:
    Bnze(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() { return 20.0; }
};
class Audi : public Car {
   public:
    Audi(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() { return 18.0; }
};
class BMW : public Car {
   public:
    BMW(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() { return 19.0; }
};
//给外部提供一个同一的获取汽车剩余路程数的API
void showCarLeftMiles(Car& car) {
    cout << car.getName() << " left miles:" << car.getLeftMiles() << "公里"
         << endl;
    // 静态绑定 call Car::getLeftMiles()
}
int main() {
    Bnze b1("奔驰", 20.0);
    Audi a("奥迪", 20.0);
    BMW b2("宝马", 20.0);
    showCarLeftMiles(b1);
    showCarLeftMiles(a);
    showCarLeftMiles(b2);
    return 0;
}