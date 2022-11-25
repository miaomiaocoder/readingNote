#include <functional>
#include <iostream>

using namespace std;

// C++11 bind绑定器 => 返回的结果还是一个函数对象

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

class Test {
   public:
    int sum(int a, int b) { return a + b; }
};

int main() {
    // bind是函数模板 可以自动推演模板类型参数
    bind(hello, "hello bind!")();
    cout << bind(sum, 10, 20)() << endl;
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;

    // 参数占位符, 绑定器出了语句，无法继续使用
    bind(hello, placeholders::_1)("hello bind 2!");
    cout << bind(sum, placeholders::_1, placeholders::_2)(200, 300) << endl;

    // 此处把bind返回的绑定器binder就复用起来了
    function<void(string)> func1 = bind(hello, placeholders::_1);
    func1("hello china!");
    func1("hello shan xi!");
    func1("hello si chuan!");

    return 0;
}
/*
$ ./test1
hello bind!
30
50
hello bind 2!
500
hello china!
hello shan xi!
hello si chuan!
*/