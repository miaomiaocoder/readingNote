#include <stdio.h>

// C 语言中 const 修饰的量可以不用初始化
// 不叫常量，叫常变量(只读变量)
void main() {
    const int a = 20;
    // const int a;
    // printf("%d\n", a);
    // int array[a] = {};

    int *p = (int *)&a;
    *p = 30;

    // 30 30 30
    printf("%d %d %d \n", a, *p, *(&a));
}