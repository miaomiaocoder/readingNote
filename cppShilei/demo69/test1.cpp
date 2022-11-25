#include <functional>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

void hello(string str) { cout << str << endl; }

int sum(int a, int b) { return a + b; }

template <typename Fty>
class myfunction {};

template <typename R, typename A1>
class myfunction<R(A1)> {
   public:
    using PFUNC = R (*)(A1);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A1 arg) {
        return _pfunc(arg);  // hello(arg)
    }

   private:
    PFUNC _pfunc;
};

template <typename R, typename A1, typename A2>
class myfunction<R(A1, A2)> {
   public:
    using PFUNC = R (*)(A1, A2);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A1 arg1, A2 arg2) { return _pfunc(arg1, arg2); }

   private:
    PFUNC _pfunc;
};

int main() {
    function<void(string)> func1 = hello;
    func1("hello world!");

    myfunction<void(string)> func2(hello);
    func2("hello world!");  // func2.operator() ("hello world!")

    myfunction<int(int, int)> func3(sum);
    cout << func3(10, 20) << endl;
    return 0;
}