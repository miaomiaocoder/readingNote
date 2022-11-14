#include <iostream>
using namespace std;

/*
指向类成员(成员变量和成员方法)的指针
*/
class Test
{
public:
	void func() { cout << "call Test::func" << endl; }
	static void static_func() { cout << "Test::static_func" << endl; }
// private:
	int ma;
	static int mb;
};
int Test::mb;
int main()
{
	Test t1;
	Test *t2 = new Test();

	// 指向成员方法的指针
	// msvc x86报错：无法从“void (__thiscall Test::* )(void)”转换为“void (__cdecl *)(void)”
    // g++报错：error: cannot convert ‘void (Test::*)()’ to ‘void (*)()’ in initialization
    // void (*pfunc)() = &Test::func;
	void (Test::*pfunc)() = &Test::func;
	(t1.*pfunc)();
	(t2->*pfunc)();

	// 如何定义函数指针指向类的static成员方法呢？
    void (*ptrfunc)() = &Test::static_func;
    (*ptrfunc)();


	// int a=10; int *p=&a; *p=30;
	//无法从“int Test::* ”转换为“int *”
	int Test::*p = &Test::ma;
	t1.*p = 20;
	cout << t1.*p << endl;

	t2->*p = 30;
	cout << t2->*p << endl;

	int *p1 = &Test::mb;
	*p1 = 40;
	cout << *p1 << endl;


	delete t2;
	return 0;
}