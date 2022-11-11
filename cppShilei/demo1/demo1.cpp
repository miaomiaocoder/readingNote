// 形参带默认值的函数
#include <iostream>

using namespace std;

int sum(int a = 10, int b = 20);

int main() {
    int a = 10;
    int b = 20;

    // mov eax, dword ptr[ebp-8]
    // push eax
    // mov ecx, dword ptr[ebp-4]
    // push ecx
    // call sum
    int ret = sum(a, b);
    cout << "ret:" << ret << endl;

    /*
        push 14H
        mov ecx, dword ptr[ebp-4]
        push ecx
        call sum
        */
    ret = sum(b);
    cout << "ret:" << ret << endl;

    /*
        push 14H
        push 0Ah
        call sum
        */
    ret = sum();
    cout << "ret:" << ret << endl;

    return 0;
}

int sum(int a, int b) { return a + b; }