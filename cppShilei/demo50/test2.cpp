#include <iostream>

using namespace std;

// 使用C的函数指针解决方案
template <typename T>
bool mygreater(T a, T b) {
    return a > b;
}
template <typename T>
bool myless(T a, T b) {
    return a < b;
}

// compare是C++的库函数模板
template <typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
    // 通过函数指针调用函数，是没有办法内联的，效率很低，因为有函数调用开销
    return comp(a, b);
}

int main() {
    cout << compare(10, 20, mygreater<int>) << endl;
    cout << compare(10, 20, myless<int>) << endl;
    cout << compare('b', 'y', mygreater<int>) << endl;

    return 0;
}
