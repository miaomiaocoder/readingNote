## 带引用计数的智能指针
#### 示例代码
```cpp
#include <iostream>
#include <memory>
using namespace std;

// 对资源进行引用计数的类
template <typename T>
class RefCnt {
   public:
    RefCnt(T* ptr = nullptr) : mptr(ptr) {
        if (mptr != nullptr) mcount = 1;
    }

    void addRef() {
        mcount++;  // 增加资源引用计数
    }

    int delRef() { return --mcount; }

   private:
    T* mptr;
    int mcount;
};

template <typename T>
class CSmartPtr {
   public:
    CSmartPtr(T* ptr = nullptr) : mptr(ptr) { mpRefCnt = new RefCnt<T>(mptr); }
    CSmartPtr(const CSmartPtr<T>& src)
        : mptr(src.mptr), mpRefCnt(src.mpRefCnt) {
        if (mptr != nullptr) mpRefCnt->addRef();
    }
    CSmartPtr<T>& operator=(const CSmartPtr<T>& src) {
        if (this == &src) mpRefCnt->addRef();
        if (0 == mpRefCnt->delRef()) {
            delete mptr;
        }
        mptr = src.mptr;
        mpRefCnt = src.mpRefCnt;
        mpRefCnt->addRef();
        return *this;
    }
    ~CSmartPtr() {
        if (0 == mpRefCnt->delRef()) {
            delete mptr;
            mptr = nullptr;
        }
    }

    T& operator*() { return *mptr; }
    T* operator->() { return mptr; }

   private:
    T* mptr;              // 指向资源的指针
    RefCnt<T>* mpRefCnt;  // 指向该资源引用计数对象的指针
};

int main() {
    CSmartPtr<int> ptr1(new int);
    CSmartPtr<int> ptr2(ptr1);
    CSmartPtr<int> ptr3;

    ptr3 = ptr2;

    *ptr1 = 20;
    cout << *ptr2 << " " << *ptr3 << endl;

    return 0;
}
```
## 参考链接
- [深入掌握C++智能指针](https://blog.csdn.net/QIANGWEIYUAN/article/details/88562935)