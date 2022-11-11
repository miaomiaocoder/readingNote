#include <iostream>

using namespace std;

// void func(int *a) {}        // int
void func(int *const a) {}  // int
int main() {
    int a = 10;
    const int b = 10;

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;

    return 0;
}