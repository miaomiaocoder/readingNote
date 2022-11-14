#include <cstring>
#include <iostream>

using namespace std;

/*
日期类
*/
class CDate {
   public:
    // 自定义了一个构造函数，编译器就不会再产生默认构造了
    CDate(int y, int m, int d) {
        _year = y;
        _month = m;
        _day = d;
    }
    void show() { cout << _year << "/" << _month << "/" << _day << endl; }

   private:
    int _year;
    int _month;
    int _day;
};

/*
构造函数的初始化列表 ： 可以指定当前对象成员变量的初始化方式
CDate信息   CGoods商品信息的一部分  a part of...  组合的关系
*/
class CGoods {
   public:
    // “CDate”: 没有合适的默认构造函数可用
    CGoods(const char *n, int a, double p, int y, int m, int d)
        // #1 构造函数的初始化列表, int _amount = a;
        // 写在初始化列表，写在#2{}里面是执行int _amount; _amount = a;
        : _date(y, m, d), _amount(a), _price(p) {
        // #2 当前类类型构造函数体
        strcpy(_name, n);
    }
    void show() {
        cout << "name:" << _name << endl;
        cout << "amount:" << _amount << endl;
        cout << "price:" << _price << endl;
        _date.show();
    }

   private:
    char _name[20];
    int _amount;
    double _price;
    CDate _date;  // 成员对象  1.分配内存  2.调用构造函数
};
int main() {
    CGoods good("商品", 100, 35.0, 2019, 5, 12);
    good.show();

    return 0;
}