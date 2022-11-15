#include <cstring>
#include <iostream>
using namespace std;

// 函数模板
template <typename T>   // 定义一个模板参数列表
bool compare(T a, T b)  // compare是一个函数模板
{
    cout << "template compare" << endl;
    return a > b;
}

// 告诉编译器，进行指定类型的模板实例化
template bool compare<int>(int, int);
template bool compare<double>(double, double);

// 针对compare函数模板，提供const char*类型的特例化版本
template <>
bool compare<const char *>(const char *a, const char *b) {
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}

// 非模板函数 - 普通函数
bool compare(const char *a, const char *b) {
    cout << "normal compare" << endl;
    return strcmp(a, b) > 0;
}