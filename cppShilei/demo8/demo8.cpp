// const和一级指针的结合
/*
const修饰的量常出现的错误是：
1.常量不能再作为左值  《=  直接修改常量的值
2.不能把常量的地址泄露给一个普通的指针或者普通的引用变量 《=
可以间接修改常量的值

const和一级指针的结合：有两种情况
C++的语言规范：const修饰的是离它最近的类型
const int *p;
可以任意指向不同的int类型的内存，但是不能通过指针间接修改指向的内存的值 int
const* p; // 与const int *p 等价

int *const p = &a; => p = &b   *p = 20;
这个指针p现在是常量，不能再指向其它内存，但是可以通过指针解引用修改指向的内存的值

const int *const p;

总结const和指针的类型转换公式：
int*    <=    const int*    是错误的！
const int*  <=   int*       是可以的！

int** <= const int**        是错误的！
const int** <= int**        是错误的！

int** <= int*const*			是错误的！
int*const* <= int**         是可以的！
*/

#include <iostream>

using namespace std;

int main() {
    // const int a = 10;
    // int *p = &a; // 错误

    /*
    const int a = 10;
    int* const p = &a; // 错误
    */

    /*
    const int a = 10;
    const int* p = &a; // 正确
    */

    // int a = 10;
    // int* p1 = &a;
    // const int* p2 = &a;  // int* 转换为 const int*
    // int* const p3 = &a;  // int* 转换为 int*
    // int *p4 = p3;
    // cout << *p4 << endl;

    // int* q1 = nullptr;
    // int* const q2 = nullptr;
    // // ./demo8 | c++filt -t 才可以得到正确答案
    // /*
    // $./demo8 | c++filt -t
    // int*
    // int*
    // */
    // cout << typeid(q1).name() << endl;
    // cout << typeid(q2).name() << endl;

    int a = 10;
    const int *p = &a;
    // int *q = p; // const int* 不能转换成 int*,
    // 跟a没有任何关系，不管a是什么类型，都不能转换
    cout << typeid(p).name() << endl;

    return 0;
}