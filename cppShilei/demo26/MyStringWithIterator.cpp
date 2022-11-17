#include <cstring>
#include <iostream>
#include <string>
// char arr[]="jkhsdkf";
using namespace std;

// 自己实现一个字符串对象
class String {
   public:
    String(const char* p = nullptr) {
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        } else {
            _pstr = new char[1];
            *_pstr = '\0';
        }
    }
    ~String() {
        delete[] _pstr;
        _pstr = nullptr;
    }
    String(const String& str) {
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }
    String& operator=(const String& str) {
        if (this == &str) return *this;

        delete[] _pstr;

        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
        return *this;
    }
    bool operator>(const String& str) const {
        return strcmp(_pstr, str._pstr) > 0;
    }
    bool operator<(const String& str) const {
        return strcmp(_pstr, str._pstr) < 0;
    }
    bool operator==(const String& str) const {
        return strcmp(_pstr, str._pstr) == 0;
    }

    int length() const { return strlen(_pstr); }
    const char* c_str() const { return _pstr; }
    // char ch = str6[6];  str6[6] = '7'
    char& operator[](int index) { return _pstr[index]; }
    // char ch = str6[6];  不允许修改！str6[6] = '7'
    const char& operator[](int index) const { return _pstr[index]; }

    // 给String字符串类型提供迭代器的实现
    class iterator {
       public:
        iterator(char* p = nullptr) : _p(p) {}
        bool operator!=(const iterator& it) { return _p != it._p; }
        void operator++() { ++_p; }
        char& operator*() { return *_p; }

       private:
        char* _p;
    };
    // begin返回的是容器底层首元素的迭代器的表示
    iterator begin() { return iterator(_pstr); }
    // end返回的是容器末尾元素后继位置的迭代器的表示
    iterator end() { return iterator(_pstr + length()); }

   private:
    char* _pstr;

    friend String operator+(const String& lhs, const String& rhs);
    friend ostream& operator<<(ostream& out, const String& str);
};
String operator+(const String& lhs, const String& rhs) {
    // char *ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
    String tmp;
    tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
    strcpy(tmp._pstr, lhs._pstr);
    strcat(tmp._pstr, rhs._pstr);
    // delete[]ptmp;
    return tmp;
}
ostream& operator<<(ostream& out, const String& str) {
    out << str._pstr;
    return out;
}
int main() {
    // 迭代器的功能：提供一种统一的方式，来透明的遍历容器
    String str1 = "hello world!";  // str1叫容器吗？底层放了一组char类型的字符
    // 容器的迭代器类型

    String::iterator it = str1.begin();
    // auto it = str1.begin();
    for (; it != str1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // c++11
    // foreach的方式来遍历容器的内部元素的值=>底层，还是通过迭代器进行遍历的
    for (char ch : str1) {
        cout << ch << " ";
    }
    cout << endl;

    // vector allocator  提供迭代器iterator的实现

    // String str1;
    String str2 = "aaa";  // string(const char*)
    String str3 = "bbb";
    String str4 = str2 + str3;
    String str5 = str2 + "ccc";
    String str6 = "ddd" + str2;

    // string str1;
    // string str2 = "aaa"; // string(const char*)
    // string str3 = "bbb";
    // string str4 = str2 + str3;
    // string str5 = str2 + "ccc";
    // string str6 = "ddd" + str2;

    cout << "str6:" << str6 << endl;
    // bool operator>(const String &str)
    if (str5 > str6) {
        cout << str5 << " > " << str6 << endl;
    } else {
        cout << str5 << " < " << str6 << endl;
    }

    int len = str6.length();
    for (int i = 0; i < len; ++i) {
        //    char& str6.operator[](i)
        cout << str6[i] << " ";
    }
    cout << endl;

    // string -> char*
    char buf[1024] = {0};
    strcpy(buf, str6.c_str());
    cout << "buf:" << buf << endl;

    return 0;
}