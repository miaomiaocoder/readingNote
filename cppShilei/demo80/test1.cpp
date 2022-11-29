// 简单工厂
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Car {
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};

class Bmw : public Car {
public:
	Bmw(string name) : Car(name) {}
	void show() {
		cout << "获取了一辆宝马汽车" << _name << endl;
	}
};

class Audi : public Car {
public:
	Audi(string name) : Car(name) {}
	void show() {
		cout << "获取了一辆奥迪汽车" << _name << endl;
	}
};

enum CarType {
	BMW, AUDI
};

class SimpleFactory {
public:
	Car* createCar(CarType ct) {
		switch (ct) {
		case BMW:
			return new Bmw("X1");
		case AUDI:
			return new Audi("A6");
		default:
			cerr << "传入工厂的参数不正确:" << ct << endl;
			break;
		}
		return nullptr;
	}
};

int main() {
	// Car* p1 = new BMW("X1");
	// Car* p2 = new Audi("A6");

	unique_ptr<SimpleFactory> factory (new SimpleFactory());
	unique_ptr<Car> p1 (factory->createCar(BMW));
	unique_ptr<Car> p2(factory->createCar(AUDI));
	p1->show();
	p2->show();

	return 0;
}