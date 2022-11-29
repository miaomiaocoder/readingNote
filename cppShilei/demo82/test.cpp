#include <iostream>
#include <memory>

using namespace std;

class Car {  // 抽象基类
   public:
    virtual void show() = 0;
};

class Bmw : public Car {
   public:
    void show() { cout << "这是一辆宝马汽车，配置有：基类配置"; }
};
class Audi : public Car {
   public:
    void show() { cout << "这是一辆奥迪汽车，配置有：基类配置"; }
};
class Benz : public Car {
   public:
    void show() { cout << "这是一辆奔驰汽车，配置有：基类配置"; }
};

// 装饰器的基类
class CarDecorator : public Car {
   public:
    CarDecorator(Car* p) : pCar(p) {}

   private:
    Car* pCar;
};

class ConcreteDecorator01 : public Car {
   public:
    ConcreteDecorator01(Car* p) : pCar(p) {}
    void show() {
        pCar->show();
        cout << ", 定速巡航";
    }

   private:
    Car* pCar;
};

class ConcreteDecorator02 : public Car {
   public:
    ConcreteDecorator02(Car* p) : pCar(p) {}
    void show() {
        pCar->show();
        cout << ", 自动刹车";
    }

   private:
    Car* pCar;
};

class ConcreteDecorator03 : public Car {
   public:
    ConcreteDecorator03(Car* p) : pCar(p) {}
    void show() {
        pCar->show();
        cout << ", 车道偏离";
    }

   private:
    Car* pCar;
};

int main() {
    Car* p1 = new ConcreteDecorator01(new Bmw());
    p1 = new ConcreteDecorator02(p1);
    p1 = new ConcreteDecorator03(p1);
    p1->show();
    cout << endl;

    Car* p2 = new ConcreteDecorator01(new Audi());
    p2->show();
    cout << endl;

    Car* p3 = new ConcreteDecorator01(new Benz());
    p3->show();
    cout << endl;

    return 0;
}