// C 调用 C++:无法直接调用了！怎么办？ 把C++源码扩在extern "C"
// C++ 调用 C代码:无法直接调用了！怎么办？ 把C函数的声明扩在extern
// "C"里面，注意区别vs,g++, clang++不同的方式

#include <iostream>

using namespace std;

extern "C" {
int sum(int a, int b);
}

// int sum(int a, int b);

int sum(int a, int b)  // sum_int_int  .text
{
    return a + b;
}

int main() {
    int ret = sum(10, 20);

    cout << "ret:" << ret << endl;

    return 0;
}