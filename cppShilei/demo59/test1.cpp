#include <iostream>

int main() {
    int *p = new int;
    /*其它的代码...*/
    /*
    如果这里忘记写delete，或者上面的代码段中程序return掉了，
    没有执行到这里，都会导致这里没有释放内存，内存泄漏
    */
    delete p;

    return 0;
}
