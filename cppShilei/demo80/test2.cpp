// 工厂方法
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Car {
   public:
    Car(string name) : _name(name) {}
    virtual void show() = 0;

   protected:
    string _name;
};

class Bmw : public Car {
   public:
    Bmw(string name) : Car(name) {}
    void show() { cout << "获取了一辆宝马汽车" << _name << endl; }
};

class Audi : public Car {
   public:
    Audi(string name) : Car(name) {}
    void show() { cout << "获取了一辆奥迪汽车" << _name << endl; }
};

class Factory {
   public:
    virtual Car* createCar(string name) = 0;  // 工厂方法 创建汽车
};

// 宝马工厂
class BMWFactory : public Factory {
   public:
    Car* createCar(string name) { return new Bmw(name); }
};

// 奥迪工厂
class AudiFactory : public Factory {
   public:
    Car* createCar(string name) { return new Audi(name); }
};

int main() {
    unique_ptr<Factory> bmwfty(new BMWFactory());
    unique_ptr<Factory> audifty(new AudiFactory());
    unique_ptr<Car> p1(bmwfty->createCar("X6"));
    unique_ptr<Car> p2(audifty->createCar("A8"));
    p1->show();
    p2->show();

    return 0;
}
