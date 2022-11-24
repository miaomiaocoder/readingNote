#include <iostream>
using namespace std;

template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr) :mptr(ptr) {}
	CSmartPtr(const CSmartPtr<T>& src) {
		mptr = new T(*src.mptr);
	}
	~CSmartPtr() { 
		delete mptr; 
		mptr = nullptr;
	}

	T& operator*() {
		return *mptr;
	}
	T* operator->() {
		return mptr;
	}
private:
	T* mptr;
};

int main()
{
	// 不带引用计数的智能指针
	CSmartPtr<int> p1(new int);
	CSmartPtr<int> p2(p1);

    // 问题， p1和p2目前管理的两套资源，用户会认为是一套
    *p1 = 20;
    *p2 = 30;

	return 0;
}