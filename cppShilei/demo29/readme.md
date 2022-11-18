### new和delete能混用吗？
```
new delete
new[] delete[]
对于普通的编译器内置类型，可以这样混用 new/delete[]   new[]/delete

但是对于自定义的类类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，
会多开辟4个字节（32位情况下是4个字节, 64位情况下8字节），记录对象的个数
不能够混用

我们可以通过自定义new, delete并记录信息，来检查内存泄漏
```

#### 例子一
```cpp
#include <iostream>

using namespace std;

// 检查内存泄漏，自定义new, delete记录信息
// 先调用operator new开辟内存空间、然后调用对象的构造函数（初始化）
void *operator new(size_t size) {
    void *p = malloc(size);
    if (p == nullptr) throw bad_alloc();
    cout << "operator new addr:" << p << endl;
    return p;
}
// delete p;  调用p指向对象的析构函数、再调用operator delete释放内存空间
void operator delete(void *ptr) {
    cout << "operator delete addr:" << ptr << endl;
    free(ptr);
}
void *operator new[](size_t size) {
    void *p = malloc(size);
    if (p == nullptr) throw bad_alloc();
    cout << "operator new[] addr:" << p << endl;
    return p;
}
void operator delete[](void *ptr) {
    cout << "operator delete[] addr:" << ptr << endl;
    free(ptr);
}

class Test {
   public:
    Test(int data = 10) { cout << "Test()" << endl; }
    ~Test() { cout << "~Test()" << endl; }

   private:
    int ma;
};

int main() {
    // Test *p1 = new Test();
    // delete p1;

    Test *p2 = new Test[5];
    cout << "p2:" << p2 << endl;
    delete p2;  // Test[0]对象析构， 直接free(p2)

    return 0;
}
```
例子一结果，注意p2的地址比addr的地址大四个字节
```cpp
$ g++ test.cpp -o test -m32
$ ./test
operator new[] addr:0x57870bb0
Test()
Test()
Test()
Test()
Test()
p2:0x57870bb4
~Test()
operator delete addr:0x57870bb4
Segmentation fault
```
例子一中```delete```部分修改为正确代码
```cpp
    Test *p2 = new Test[5];
    cout << "p2:" << p2 << endl;
    delete []p2;  // Test[0]对象析构， 直接free(p2)
// 结果如下
$ g++ test.cpp -o test -m32
$ ./test
operator new[] addr:0x56ed9bb0
Test()
Test()
Test()
Test()
Test()
p2:0x56ed9bb4
~Test()
~Test()
~Test()
~Test()
~Test()
operator delete[] addr:0x56ed9bb0
```
#### 例子二
修改例子一中的main部分
```cpp
int main() {
    Test *p1 = new Test();
    delete p1;

    // Test *p2 = new Test[5];
    // cout << "p2:" << p2 << endl;
    // delete p2;  // Test[0]对象析构， 直接free(p2)

    return 0;
}
// 此时输出结果为：
$ g++ test.cpp -o test -m32
$ ./test
operator new addr:0x57dffbb0
Test()
~Test()
operator delete addr:0x57dffbb0
```

```cpp
    Test *p1 = new Test();
    delete[] p1;  
// 此时输出结果为：
$ g++ test.cpp -o test -m32
$ ./test
operator new addr:0x58086bb0
Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
operator delete[] addr:0x58086bac
free(): invalid pointer
Aborted
```