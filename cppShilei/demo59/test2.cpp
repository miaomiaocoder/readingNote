#include <iostream>
using namespace std;

template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr = nullptr) :mptr(ptr) {}
	~CSmartPtr() { delete mptr; }
private:
	T *mptr;
};

int main()
{
    // int *p = new int;
	CSmartPtr<int> ptr(new int);
	/*其它的代码...*/

	/*由于ptr是栈上的智能指针对象，不管是函数正常执行完，还是运行过程中出现
	异常，栈上的对象都会自动调用析构函数，在析构函数中进行了delete
	操作，保证释放资源*/
	return 0;
}
