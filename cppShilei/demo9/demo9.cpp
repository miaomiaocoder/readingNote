#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int *p = &a;
    // error: invalid conversion from ‘int**’ to ‘const int**’
    // 一级指针中 int* 可以转换为 const int*, 注意区别
    // const int **q = &p;

    // ./demo9 | c++filt -t
    int **t = &p;
    int *const *q = t;
    cout << typeid(t).name() << endl;
    cout << typeid(q).name() << endl;

    // int a = 10;
    // const int *p = &a;
    // const int *const *q = &p;

    // int a = 10;
    // const int *p = &a;
    // const int **q = &p;


    return 0;
}