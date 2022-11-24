#include <iostream>
using namespace std;

template <typename T>
class CSmartPtr {
   public:
    CSmartPtr(T* ptr = nullptr) : mptr(ptr) {}
    ~CSmartPtr() {
        delete mptr;
        mptr = nullptr;
    }

    T& operator*() { return *mptr; }
    T* operator->() { return mptr; }

   private:
    T* mptr;
};

int main() {
    // 不带引用计数的智能指针
    CSmartPtr<int> p1(new int);
    CSmartPtr<int> p2(p1);

    // 这个main函数运行，代码直接崩溃，问题出在默认的拷贝构造函数做的是浅拷贝，
    // 两个智能指针都持有一个new int资源，ptr2先析构释放了资源，
    // 到ptr1析构的时候，就成了delete野指针了，造成程序崩溃。

    return 0;
}