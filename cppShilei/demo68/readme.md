## 模板的完全特例化和部分特例化
#### 代码示例1
```cpp
#include <cstring>
#include <iostream>

using namespace std;

/*
模板的完全特例化和非完全（部分）特例化
*/

template <typename T>
bool compare(T a, T b) {
    cout << "template compare" << endl;
    return a > b;
}

template <>
bool compare<const char*>(const char* a, const char* b) {
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}

int main() {
    compare(10, 20);
    compare("aaa", "bbb");
    return 0;
}

// $ ./test
// template compare
// compare<const char*>
```
#### 代码示例2
```cpp
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
/*
$ ./test2
call Vector template init
call Vector<char*> init
call Vector<Ty*> init
call Vector<R(*) (A1, A2)> init
call Vector<R (A1, A2)> init
30
60
*/
```
#### 代码示例3
```cpp
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
```