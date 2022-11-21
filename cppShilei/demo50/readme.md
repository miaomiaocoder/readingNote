## 函数对象

把有```operator()```小括号运算符重载函数的对象，称作函数对象或者称作仿函数。
```cpp
#include <iostream>

using namespace std;

template <typename T>
bool compare(T a, T b) {
    return a > b;
}
int main() {
    cout << compare(10, 20) << endl;
    cout << compare('b', 'y') << endl;

    return 0;
}
```

```cpp
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
```

```cpp
#include <iostream>

using namespace std;

/*
1.通过函数对象调用operator()重载，可以省略函数的调用开销，比通过函数指针
调用函数（不能够inline内联调用）效率高

2.因为函数对象是用类生成的，所以可以添加相关的成员变量，用来记录函数对象使用
时更多的信息
*/
// C++函数对象的版本实现
template <typename T>
class mygreater {
   public:
    bool operator()(T a, T b)  // 二元函数对象
    {
        return a > b;
    }
};
template <typename T>
class myless {
   public:
    bool operator()(T a, T b)  // 二元函数对象
    {
        return a < b;
    }
};

// compare是C++的库函数模板
template <typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
    // 通过函数指针调用函数，是没有办法内联的，效率很低，因为有函数调用开销
    return comp(a, b); // operator()(a, b);
}

int main() {
    cout << compare(10, 20, mygreater<int>()) << endl;
    cout << compare(10, 20, myless<int>()) << endl;
    cout << compare('b', 'y', mygreater<int>()) << endl;

    return 0;
}
```