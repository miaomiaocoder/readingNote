## C++ 左值引用和右值引用

#### 引用是一种更安全的指针。
1. 引用是必须初始化的，指针可以不初始化
2. 引用只有一级引用，没有多级引用；指针可以有一级指针，也可以有多级指针
3. 定义一个引用变量，和定义一个指针变量，其汇编指令是一模一样的；通过引用变量修改所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层指令也是一模一样的

**引用和指针底层指令**
```cpp
    int a = 10;
    int *p = &a;
    int &b = a;
    *p = 20;
    b = 30;
```
```c++
    // msvc下反汇编结果
    int* p = &a;
00BC1836  lea         eax,[a]  
00BC1839  mov         dword ptr [p],eax  
    int& b = a;
00BC183C  lea         eax,[a]  
00BC183F  mov         dword ptr [b],eax  
    *p = 20;
00BC1842  mov         eax,dword ptr [p]  
00BC1845  mov         dword ptr [eax],14h  
    b = 30;
00BC184B  mov         eax,dword ptr [b]  
00BC184E  mov         dword ptr [eax],1Eh 
```
```c
    // gcc 反汇编结果
    lea     rax, [rbp-20]
    mov     QWORD PTR [rbp-8], rax
    lea     rax, [rbp-20]
    mov     QWORD PTR [rbp-16], rax
    mov     rax, QWORD PTR [rbp-8]
    mov     DWORD PTR [rax], 20
    mov     rax, QWORD PTR [rbp-16]
    mov     DWORD PTR [rax], 30
```
**引用大小**
```cpp
// demo10.cpp
#include <iostream>

using namespace std;

int main() {
    int array[5] = {};
    int *p = array;
    int (*t)[5] = &array;
    // 定义一个引用变量，来引用array数组
    // int (*q)[5] = &array  用&替换*就可以得到引用
    int(&q)[5] = array;

    // g++ -m32 demo10.cpp -o demo10 按照32位编译结果 20 4 4 20
    // msvc 选择x86模式结果 20 4 4 20
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
```
**demo10.cpp 代码运行结果**
```c
$ g++ -m32 demo10.cpp -o demo10
$ ./demo10 | c++filt -t
20
4
4
20
int [5]
int*
int (*) [5]
int [5]
```
#### 右值引用
1. ```int &&c = 20;``` 专门用来引用右值类型，指令上，可以自动产生临时量，然后直接引用临时量。可以通过 ```c = 40;```修改
2. **右值引用变量本身是一个左值，只能用左值引用来引用它**
3. **不能用一个右值引用变量，来引用一个左值**   
    ```c++
        int &&c = 20;
        int &e = c;  // √可行，一个右值引用变量，本身是一个左值
        int &&f = c; // ×错误，无法将右值引用绑定到左值
    ```

```cpp
    int &&c = 20;
    c = 30; // 可行
    const int &d = 20;
    d = 40; // 错误
```
```c++
// msvc 反汇编结果, int&& c = 20 和 const int &d = 20 指令相同
    int&& c = 20;
00444A9F  mov         dword ptr [ebp-18h],14h  
00444AA6  lea         eax,[ebp-18h]  
00444AA9  mov         dword ptr [c],eax  
    c = 30;
00444AAC  mov         eax,dword ptr [c]  
00444AAF  mov         dword ptr [eax],1Eh  
    const int& d = 20;
00444AB5  mov         dword ptr [ebp-30h],14h  
00444ABC  lea         eax,[ebp-30h]  
00444ABF  mov         dword ptr [d],eax 
```