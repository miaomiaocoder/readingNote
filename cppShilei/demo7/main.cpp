#include <iostream>

int main() {
    const int a = 20;  // 已经改了！！！

    int *p = (int *)&a;
    *p = 30;

    printf("%d %d %d \n", a, *p, *(&a));

    return 0;
}