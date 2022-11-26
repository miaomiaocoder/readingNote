#include <iostream>

using namespace std;
/*
C++11 函数对象的升级版 =》 lambda表达式
函数对象的缺点：
使用在泛型算法参数传递   比较性质/自定义操作  优先级队列  智能指针

lambda表达式的语法：
[捕获外部变量](形参列表)->返回值{操作代码};

如果lambda表达式的返回值不需要，那么"->返回值"可以省略的

[捕获外部变量]
[]：表示不捕获任何外部变量
[=]：以传值的方式捕获外部的所有变量
[&]：以传引用的方式捕获外部的所有变量
[this]：捕获外部的this指针
[=,&a]：以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获
[a, b]：以值传递的方式捕获外部变量a和b
[a, &b]：a以值传递捕获，b以传引用的方式捕获
*/
template <typename T = void>
class TestLambda01 {
   public:
    TestLambda01() {}
    void operator()() const { cout << "hello world" << endl; }
};

template <typename T = void>
class TestLambda02 {
   public:
    TestLambda02() {}
    int operator()(int a, int b) const { return a + b; }
};

template <typename T = int>
class TestLambda03 {
   public:
    TestLambda03(int& a, int& b) : ma(a), mb(b) {}
    void operator()() const {
        int tmp = ma;
        ma = mb;
        mb = tmp;
    }

   private:
    int& ma;
    int& mb;
};

int main() {
    auto func1 = []() -> void { cout << "hel" << endl; };
    func1();

    auto func2 = [](int a, int b) -> int { return a + b; };
    cout << func2(20, 30) << endl;

    int a = 10;
    int b = 20;
    auto func3 = [&a, &b]() {
        int tmp = a;
        a = b;
        b = tmp;
    };
    func3();
    cout << "a:" << a << " b:" << b << endl;

    cout << "---------------------" << endl;

    TestLambda01<> t1;
    t1();

    TestLambda02<> t2;
    cout << t2(100, 200) << endl;

    TestLambda03<> t3(a, b);
    t3();
    cout << "a:" << a << " b:" << b << endl;

    return 0;
}