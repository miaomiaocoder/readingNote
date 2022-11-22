#include <iostream>
using namespace std;

int f(int n) {
    cout << n << endl;
    return n;
}

void func(int param1, int param2) {
    int var1 = param1;
    int var2 = param2;
    // 先输出2再输出1；如果将printf换为cout进行输出，输出结果则刚好相反。
    printf("var1 = %d,var2 = %d \n", f(var1), f(var2));

    cout << "分隔线------------------------------" << endl;

    // 先输出1再输出2
    cout << f(var1) << " " << f(var2) << endl;
}

int main(int argc, char* argv[]) {
    func(1, 2);
    return 0;
}