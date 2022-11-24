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