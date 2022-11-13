#include <iostream>

int main() {
    // int a = 10;
    // int *p = &a;
    // const int *&q = p;
    // const int **q = &p; //const int** <= int**

    // int a = 10;
    // const int *p = &a;
    // int *&q = p;
    // int **q = &p;
    // int** <= const int**

    // int a = 10;
    // int *const p = &a;
    // int **q = &p;
    // int **q = &p; // *q =

    // 写一句代码，在内存的0x0018ff44处写一个4字节的10
    // int *&p = (int *)0x0018ff44; // ❌

    // int *p1 = (int *)0x0018ff44;
    // int *&&p2 = (int *)0x0018ff44;
    // int *const &p2 = (int *)0x0018ff44;

    // int a = 10;
    // int *p = &a;
    // int *&q1 = p;
    // const int *&q2 = p; // typeid(q).name()

    return 0;
}