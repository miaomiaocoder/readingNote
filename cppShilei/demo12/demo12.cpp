/*
new和delete
new和malloc的区别是什么？
delete和free的区别是什么？

malloc和free，称作C的库函数
new和delete，称作运算符

new不仅可以做内存开辟，还可以做内存初始化操作
malloc开辟内存失败，是通过返回值和nullptr做比较；而new开辟
内存失败，是通过抛出bad_alloc类型的异常来判断的。
*/

#include <iostream>

using namespace std;

// #if 0
int main() {
    int *p = (int *)malloc(sizeof(int));
    if (p == nullptr) {
        return -1;
    }
    *p = 20;
    free(p);

    int *p1 = new int(20);
    delete p1;

    // try {
    //     int *p1 = new int(20);
    // } catch (const bad_alloc &e) {
    // }

    // 开辟数组类型
    int *q = (int *)malloc(sizeof(int) * 20);
    if (q == nullptr) {
        return -1;
    }
    free(q);

    // new int[20] 不初始化
    // new int[20]() 会初始化为0
    // int *q1 = new int[20]; 
    int *q1 = new int[20]();  // 20个int sizeof(int) * 20
    delete[] q1;
}
// #endif

#if 0
int main()
{
	// new有多少种？
	int *p1 = new int(20);

	int *p2 = new (nothrow) int;

	const int *p3 = new const int(40);

	// 定位new  
	int data = 0;
	int *p4 = new (&data) int(50);
	cout << "data:" << data << endl;
	return 0;
}
#endif