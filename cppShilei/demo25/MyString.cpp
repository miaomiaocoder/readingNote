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

	String str1;
	String str2 = "aaa"; // string(const char*)
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
	if (str5 > str6)
	{
		cout << str5 << " > " << str6 << endl;
	}
	else
	{
		cout << str5 << " < " << str6 << endl;
	}

	int len = str6.length();
	for (int i = 0; i < len; ++i)
	{
		//    char& str6.operator[](i)
		cout << str6[i] << " ";
	}
	cout << endl;

	// string -> char*
	char buf[1024] = { 0 };
	strcpy(buf, str6.c_str());
	cout << "buf:" << buf << endl;


    return 0;
}