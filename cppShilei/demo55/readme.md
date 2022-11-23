## CMyString
```cpp
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
    CMyString str1("aaaaaaaaaaaaaaaaaaaa");
    CMyString str2;
    str2 = GetString(str1);
    cout << str2.c_str() << endl;

    return 0;
}

/* vs2019结果
CMyString(const char*)
CMyString(const char*)
CMyString(const char*)
CMyString(const CMyString&) => tmpStr拷贝构造main函数栈帧上的临时对象
~CMyString
operator=(const CMyString&) => main函数栈帧上的临时对象给t2赋值
~CMyString
aaaaaaaaaaaaaaaaaaaa
~CMyString
~CMyString
*/

/* vs2022结果
CMyString(const char*)
CMyString(const char*)
CMyString(const char*)
operator=(const CMyString&)
~CMyString
aaaaaaaaaaa
~CMyString
~CMyString
*/

/* g++结果
CMyString(const char*)
CMyString(const char*)
CMyString(const char*)
operator=(const CMyString&)
~CMyString
aaaaaaaaaaaaaaaaaaaa
~CMyString
~CMyString
*/
```