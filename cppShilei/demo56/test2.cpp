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
    // 带右值引用参数的拷贝构造
    CMyString(CMyString&& str) noexcept  // str引用的就是一个临时对象
    {
        cout << "CMyString(CMyString&&)" << endl;
        mptr = str.mptr;
        str.mptr = nullptr;
    }
    // 带左值引用参数的赋值重载函数
    CMyString& operator=(const CMyString& str) {
        cout << "operator=(const CMyString&)" << endl;
        if (this == &str) return *this;

        delete[] mptr;

        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
        return *this;
    }
    // 带右值引用参数的赋值重载函数
    CMyString& operator=(CMyString&& str) noexcept  // 临时对象
    {
        cout << "operator=(CMyString&&)" << endl;
        if (this == &str) return *this;

        delete[] mptr;

        mptr = str.mptr;
        str.mptr = nullptr;
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
    CMyString str1("aaaaaaaaaaa");
    CMyString str2;
    str2 = GetString(str1);
    cout << str2.c_str() << endl;

    return 0;
}
