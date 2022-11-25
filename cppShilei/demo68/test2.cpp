#include <iostream>

using namespace std;

template <typename T>
class Vector {
   public:
    Vector() { cout << "call Vector template init" << endl; }
};

// 下面这个是对char*类型提供的完全特例化版本  #1
template <>
class Vector<char *> {
   public:
    Vector() { cout << "call Vector<char*> init" << endl; }
};

// 下面这个是对指针类型提供的部分特例化版本  #2
template <typename Ty>
class Vector<Ty *> {
   public:
    Vector() { cout << "call Vector<Ty*> init" << endl; }
};

// 针对函数指针（有返回值，有两个形参变量）提供的部分特例化
template <typename R, typename A1, typename A2>
class Vector<R (*)(A1, A2)> {
   public:
    Vector() { cout << "call Vector<R(*) (A1, A2)> init" << endl; }
};

// 针对函数（有一个返回值，有两个形参变量）类型提供的部分特例化
template <typename R, typename A1, typename A2>
class Vector<R(A1, A2)> {
   public:
    Vector() { cout << "call Vector<R (A1, A2)> init" << endl; }
};

int sum(int a, int b) { return a + b; }

int main() {
    Vector<int> vec1;
    Vector<char *> vec2;
    Vector<int *> vec3;
    Vector<int (*)(int, int)> vec4;
    Vector<int(int, int)> vec5;

    // 注意区分一下函数类型和函数指针类型
    typedef int (*PFUNC1)(int, int);
    PFUNC1 pfunc1 = sum;
    cout << pfunc1(10, 20) << endl;

    typedef int PFUNC2(int, int);
    PFUNC2 *pfunc2 = sum;
    cout << pfunc2(40, 20) << endl;

    return 0;
}