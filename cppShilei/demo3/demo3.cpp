// 函数重载

// 1.C++为什么支持函数重载，C语言不支持函数重载？
// C++代码产生函数符号的时候，函数名+参数列表类型组成的
// C代码产生函数符号的时候，函数名来决定

// 2.函数重载需要注意些什么？
// C++和C语言代码之间如何互相调用

// 函数重载
// 1.一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就称作——————函数重载。
// 2.一组函数要称得上重载，一定先是处在同一个作用域当中的。
// 3.const或者volatile的时候，是怎么影响形参类型的。
// 4.一组函数，函数名相同，参数列表也相同，仅仅是返回值不同？不叫重载

// 请你解释一下，什么是多态？
// 静态（编译时期）的多态：函数重载
// 动态（运行时期）的多态：

#include <cstring>
#include <iostream>

using namespace std;

bool compare(int a, int b)  // compare_int_int
{
    cout << "compare_int_int" << endl;
    return a > b;
}
bool compare(double a, double b)  // compare_double_double
{
    cout << "compare_double_double" << endl;
    return a > b;
}
bool compare(const char *a, const char *b)  // compare_const char*_const char*
{
    cout << "compare_char*_char*" << endl;
    return strcmp(a, b) > 0;
}
int main() {
    bool compare(int a, int b); // 函数的声明，下面三个函数会优先选择这个局部作用域

    compare(10, 20);        // call compare_int_int
    compare(10.0, 20.0);    // double -> int
    compare("aaa", "bbb");  // const char* => int

    return 0;
}