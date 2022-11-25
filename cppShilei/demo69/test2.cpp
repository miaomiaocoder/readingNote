#include <functional>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

void hello(string str) { cout << str << endl; }

int sum(int a, int b) { return a + b; }

template <typename Fty>
class myfunction {};

template <typename R, typename... A>
class myfunction<R(A...)> {
   public:
    using PFUNC = R (*)(A...);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A... arg) {
        return _pfunc(arg...);  // hello(arg)
    }

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