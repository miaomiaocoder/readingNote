## 智能指针基础知识
裸指针
```cpp
#include <iostream>

int main() {
    int *p = new int;
    /*其它的代码...*/
    /*
    如果这里忘记写delete，或者上面的代码段中程序return掉了，
    没有执行到这里，都会导致这里没有释放内存，内存泄漏
    */
    delete p;

    return 0;
}
```
使用智能指针
```cpp
#include <iostream>
using namespace std;

template <typename T>
class CSmartPtr {
   public:
    CSmartPtr(T* ptr = nullptr) : mptr(ptr) {}
    ~CSmartPtr() { delete mptr; }

    T& operator*() { return *mptr; }
    T* operator->() { return mptr; }

   private:
    T* mptr;
};

int main() {
    // int *p = new int;
    CSmartPtr<int> ptr(new int);
    *ptr = 20;

    class Test {
       public:
        void test() { cout << "call Test::test" << endl; }
    };
    CSmartPtr<Test> ptr2(new Test());
    (*ptr2).test();
    // (ptr2.operator->())->test();
    ptr2->test();
    /*其它的代码...*/

    /*由于ptr是栈上的智能指针对象，不管是函数正常执行完，还是运行过程中出现
    异常，栈上的对象都会自动调用析构函数，在析构函数中进行了delete
    操作，保证释放资源*/
    return 0;
}
```
1. 智能指针是代理模式的具体应用，它使用 RAII 技术代理了裸指针，能够自动释放内存，无需程序员干预，所以被称为“智能指针”。
2. 如果指针是“独占”使用，就应该选择 unique_ptr，它为裸指针添加了很多限制，更加安全。
3. 如果指针是“共享”使用，就应该选择 shared_ptr，它的功能非常完善，用法几乎与原始指针一样。
4. 应当使用工厂函数 make_unique()、make_shared() 来创建智能指针，强制初始化，而且还能使用 auto 来简化声明。
5. shared_ptr 有少量的管理成本，也会引发一些难以排查的错误，所以不要过度使用。

## 参考链接
- [深入掌握C++智能指针](https://blog.csdn.net/QIANGWEIYUAN/article/details/88562935)