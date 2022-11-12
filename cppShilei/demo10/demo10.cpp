#if 0
#include <iostream>

using namespace std;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
     cout << "swap(int *x, int *y)" << endl;
}
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
    cout << "swap(int &x, int &y)" << endl;
}

int main() {
    // int a = 10;
    // int *p = &a;
    // int &b = a;
    // *p = 20;
    // cout << a << " " << *p << " " << b << endl;
    // b = 30;
    // cout << a << " " << *p << " " << b << endl;

    int a = 10;
    int b = 20;
    swap(&a, &b);
    cout << "a:" << a << " b:" << b << endl;
    swap(a, b);
    cout << "a:" << a << " b:" << b << endl;

    return 0;
}
#endif

#if 0
#include <iostream>

using namespace std;

int main() {
    int array[5] = {};
    int *p = array;
    int (*t)[5] = &array;
    // 定义一个引用变量，来引用array数组
    // int (*q)[5] = &array  用&替换*就可以得到引用
    int(&q)[5] = array;

    // g++ -m32 demo10.cpp -o demo10 按照32位编译结果 20 4 20
    // $ sudo apt-get install build-essential module-assistant  
    // $ sudo apt-get install gcc-multilib g++-multilib  
    cout << sizeof(array) << endl;
    cout <<  sizeof(p) << endl;
    cout << sizeof(t) <<endl;
    cout << sizeof(q) << endl;

    // ./demo10 | c++filt -t
    cout << typeid(array).name() << endl;
    cout << typeid(p).name() << endl;
    cout << typeid(t).name() << endl;
    cout << typeid(q).name() << endl;

    return 0;
}
#endif

#include <iostream>

using namespace std;

int main() {
    int a = 10;  // 左值，它有内存，有名字，值可以修改的
    int &b = a;

    // int &c = 20; // 20是右值：没内存，没名字
    // C++11提供了右值引用
    int &&c = 20;
    c = 30;

    int &e = c;  // √可行，一个右值引用变量，本身是一个左值
    int &&f = c; // ×错误，无法将右值引用绑定到左值

    cout << e << endl;

    /*
    int temp = 20;
    temp -> b
    */
    const int &d = 20;
    return 0;
}
