#include <cstring>
#include <iostream>
#include <vector>
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
    friend CMyString operator+(const CMyString& lhs, const CMyString& rhs);
    friend ostream& operator<<(ostream& out, const CMyString& str);
};

CMyString operator+(const CMyString& lhs, const CMyString& rhs) {
    // char* ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
    CMyString tmpStr;
    tmpStr.mptr = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
    strcpy(tmpStr.mptr, lhs.mptr);
    strcat(tmpStr.mptr, rhs.mptr);
    // delete []ptmp;
    return tmpStr;
    // return CMyString(ptmp);
}

ostream& operator<<(ostream& out, const CMyString& str) {
    out << str.mptr;
    return out;
}

int main() {
    CMyString str1 = "aaa";

    vector<CMyString> vec;
    vec.reserve(10);

    cout << "----------------------------" << endl;
    vec.push_back(str1);
    vec.push_back(CMyString("bbb"));
    cout << "----------------------------" << endl;

    return 0;
}