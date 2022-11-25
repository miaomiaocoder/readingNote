#include <iostream>

using namespace std;

// 模板的实参推演

int sum(int a, int b) { return a + b; }

// T包含了所有的大的类型  返回值，所有形参的类型都取出来
template <typename T>
void func(T a) {
    cout << typeid(T).name() << endl;
}

template <typename R, typename A1, typename A2>
void func2(R (*a)(A1, A2)) {
    cout << typeid(R).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
};

class Test {
   public:
    int sum(int a, int b) { return a + b; }
};

template <typename R, typename T, typename A1, typename A2>
void func3(R (T::*a)(A1, A2)) {
    cout << typeid(R).name() << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}

int main() {
    func(10);
    func("aaa");
    func(sum);
    func(&Test::sum);

    cout << "--------------" << endl;

    func(sum);
    func2(sum);

    cout << "--------------" << endl;

    func3(&Test::sum);

    return 0;
}
// g++ 结果
/*
$ ./test3 | c++filt -t
int
char const*
int (*)(int, int)
int (Test::*)(int, int)
--------------
int (*)(int, int)
int
int
int
--------------
int
Test
int
int
*/

// msvc结果
/*
int
char const *
int (__cdecl*)(int,int)
int (__thiscall Test::*)(int,int)
--------------
int (__cdecl*)(int,int)
int
int
int
--------------
int
class Test
int
int
*/