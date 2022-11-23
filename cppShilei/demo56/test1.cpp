#include <cstring>
#include <iostream>
using namespace std;

class CMyString {
   public:
    CMyString(const char* str = nullptr) {
        cout << "CMyString(const char*)" << endl;
        if (str != nullptr) {
            mptr = new char[strlen(str) + 1];
            strcpy(mptr, str);
        } else {
            mptr = new char[1];
            *mptr = '\0';
        }
    }
    ~CMyString() {
        cout << "~CMyString" << endl;
        delete[] mptr;
        mptr = nullptr;
    }
    // 带左值引用参数的拷贝构造
    CMyString(const CMyString& str) {
        cout << "CMyString(const CMyString&)" << endl;
        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
    }
    CMyString& operator=(const CMyString& str) {
        cout << "operator=(const CMyString&)" << endl;
        if (this == &str) return *this;

        delete[] mptr;

        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
        return *this;
    }
    const char* c_str() const { return mptr; }

   private:
    char* mptr;
};
CMyString GetString(CMyString& str) {
    const char* pstr = str.c_str();
    CMyString tmpStr(pstr);
    return tmpStr;
}

int main() {
    // 右值引用
    int a = 10;
    int& b = a;  // 左值：有内存、有名字   右值：没名字（临时量）或 没内存
    // int &&c = a; // 无法将左值绑定到右值引用
    // int& c = 20; // 不能用左值引用绑定一个右值

    /*
    int tmp = 20;
    const int &c = tmp;
    */
    const int& c = 20;  // 不能用左值引用绑定一个右值, 加上const可以
    /*
    int tmp = 20;
    int &&d = tmp;
    */
    int&& d = 20;  // 可以把一个右值绑定到一个右值引用上
    // 汇编指令相同，但是d可以修改

    // 非常量引用只能绑定到左值
    // CMyString& e1 = CMyString("aaa");
    // 非常量引用只能绑定到左值
    const CMyString& e2 = CMyString("aaa");
    CMyString&& e = CMyString("aaa");

    // int&& fd = d;  // 无法将左值绑定到右值引用
    int& f = d;    // 一个右值引用变量，本身是一个左值

    return 0;
}