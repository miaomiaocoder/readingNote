// 抽象工厂
#include <iostream>
#include <memory>
#include <string>

using namespace std;
// 系列产品1
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
    void show() { cout << "获取了一量宝马汽车" << _name << endl; }
};

class Audi : public Car {
   public:
    Audi(string name) : Car(name) {}
    void show() { cout << "获取了一量奥迪汽车" << _name << endl; }
};

// 系列产品2
class Light {
   public:
    virtual void show() = 0;
};

class BmwLight : public Light {
   public:
    void show() { cout << "BMW light!" << endl; }
};

class AudiLight : public Light {
   public:
    void show() { cout << "Audi light!" << endl; }
};

// 工厂方法 => 抽象工厂(对有一组关联关系的产品簇提供产品对象的统一创建)
class AbstractFactory {
   public:
    virtual Car* createCar(string name) = 0;  // 工厂方法 创建汽车
    virtual Light* createCarLight() = 0;  // 工厂方法 创建汽车关联的产品，车灯
};

// 宝马工厂
class BMWFactory : public AbstractFactory {
   public:
    Car* createCar(string name) { return new Bmw(name); }
    Light* createCarLight() { return new BmwLight(); }
};

// 奥迪工厂
class AudiFactory : public AbstractFactory {
   public:
    Car* createCar(string name) { return new Audi(name); }
    Light* createCarLight() { return new AudiLight(); }
};

int main() {
    // 现在考虑产品  一类产品（有关联关系的系列产品）

    unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
    unique_ptr<AbstractFactory> audifty(new AudiFactory());
    unique_ptr<Car> p1(bmwfty->createCar("X6"));
    unique_ptr<Car> p2(audifty->createCar("A8"));
    unique_ptr<Light> l1(bmwfty->createCarLight());
    unique_ptr<Light> l2(audifty->createCarLight());
    p1->show();
    l1->show();
    p2->show();
    l2->show();

    return 0;
}