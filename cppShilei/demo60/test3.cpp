#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class CSmartPtr {
   public:
    CSmartPtr(T* ptr = nullptr) : mptr(ptr) {}
    CSmartPtr(const CSmartPtr<T>& src) { mptr = new T(*src.mptr); }
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
    /*CSmartPtr<int> p1(new int);
    CSmartPtr<int> p2(p1);*/

    /*auto_ptr<int> ptr1(new int);
    auto_ptr<int> ptr2(ptr1);*/
    /**ptr2 = 20;
    cout << *ptr1 << endl;*/

    /*
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    */

    // unique_ptr提供了带右值引用参数的拷贝构造和赋值
    unique_ptr<int> p1(new int);
    // unique_ptr<int> p2(p1);
    unique_ptr<int> p2(std::move(p1));

    cout << *p1 << endl;

    return 0;
}