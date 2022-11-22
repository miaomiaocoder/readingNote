#include <iostream>

using namespace std;

struct Data1 {
    char c;
    double t;
};
struct Data2 {
    char c;
};
struct Data3 {};
struct Data4 {
    virtual void func() {}
};
struct Data5 : public virtual Data3 {};
struct Data6 : public virtual Data4 {};

int main() {
    cout << sizeof(Data1) << endl;
    cout << sizeof(Data2) << endl;
    cout << sizeof(Data3) << endl;
    cout << sizeof(Data4) << endl;
    cout << sizeof(Data5) << endl;
    cout << sizeof(Data6) << endl;

    return 0;
}