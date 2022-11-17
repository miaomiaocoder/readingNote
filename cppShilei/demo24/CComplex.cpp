#include <iostream>
using namespace std;

/*
C++的运算符重载：使对象的运算表现得和编译器内置类型一样
template<typename T>
T sum(T a, T b)
{
	return a+b; // a.operator+(b)
}
复数类
*/
class CComplex
{
public:
	// CComplex() CComplex(20) CComplex(30, 30)
	CComplex(int r = 0, int i = 0)
		:mreal(r), mimage(i) {}
	// 指导编译器怎么做CComplex类对象的加法操作
	//CComplex operator+(const CComplex &src)
	//{
		//CComplex comp;
		//comp.mreal = this->mreal + src.mreal;
		//comp.mimage = this->mimage + src.mimage;
		//return comp;
		//return CComplex(this->mreal + src.mreal,
			//this->mimage + src.mimage);
	//}
	CComplex operator++(int) // 带参数的是后置++
	{
		//CComplex comp = *this;
		//mreal += 1;
		//mimage += 1;
		//return comp;
		return CComplex(mreal++, mimage++);
	}
	CComplex& operator++() // 不带参数的是前置++
	{
		mreal += 1;
		mimage += 1;
		return *this;
	}
	void operator+=(const CComplex &src)
	{
		mreal += src.mreal;
		mimage += src.mimage;
	}
	void show() { cout << "real:" << mreal << " image:" << mimage << endl; }
private:
	int mreal;
	int mimage;

	friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);
	friend ostream& operator<<(ostream &out, const CComplex &src);
	friend istream& operator>>(istream &in, CComplex &src);
};
CComplex operator+(const CComplex &lhs, const CComplex &rhs)
{
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}
ostream& operator<<(ostream &out, const CComplex &src)
{
	out << "mreal:" << src.mreal << " mimage:" << src.mimage << endl;
	return out;
}
istream& operator>>(istream &in, CComplex &src)
{
	in >> src.mreal >> src.mimage;
	return in;
}
int main()
{
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	// comp1.operator+(comp2) 加法运算符的重载函数
	// 
	CComplex comp3 = comp1 + comp2;
	comp3.show();
	CComplex comp4 = comp1 + 20; // comp1.operator+(20) int->CComplex  CComplex(int)
	comp4.show();
	// 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法
	// ，就在全局作用域找合适的运算符重载函数
	//            ::operator+(30, comp1)
	CComplex comp5 = 30 + comp1;
	comp5.show();

	// CComplex operator++(int)
	comp5 = comp1++; // ++ --单目运算符  operator++() 不带参数的是前置++  operator++(int) 带参数的是后置++
	comp1.show();
	comp5.show();
	// CComplex operator++()
	comp5 = ++comp1;
	comp1.show();
	comp5.show();

	// void comp1.operator+=(comp2)   ::operator+=(comp1, comp2)
	comp1 += comp2;
	//comp1.show(); // 对象信息的输出
	//cout ::operator<<(cout, comp1)   void << endl;
	//ostream& operator<<(ostream &out, const CComplex &src)
	cout << comp1 << endl;
	cin >> comp1 >> comp2;
	cout << comp1 << comp2 << endl;

    return 0;
}

template<typename T>
void show(T a)// CComplex a
{
	//a.show();
	cout << a << endl; // T int  cout<<10<<endl;  CComplex
}