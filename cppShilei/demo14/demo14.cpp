#include <iostream>

using namespace std;

/*
OOP编程复习一下
OOP实现一个顺序栈

构造函数和析构函数
函数的名字和类名一样
没有返回值
*/
class SeqStack {
   public:
    // 构造函数 SeqStack s1;  SeqStack s2(20);
    // 是可以带参数的，因此可以提供多个构造函数，叫做构造函数的重载
    SeqStack(int size = 10) {
        cout << this << " SeqStack()" << endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }
    // 析构函数
    // 是不带参数的，所有析构函数只能有一个
    ~SeqStack() {
        cout << this << " ~SeqStack()" << endl;
        delete[] _pstack;
        _pstack = nullptr;
    }
    void push(int val) {
        if (full()) resize();
        _pstack[++_top] = val;
    }
    void pop() {
        if (empty()) return;
        --_top;
    }
    int top() { return _pstack[_top]; }
    bool empty() { return _top == -1; }
    bool full() { return _top == _size - 1; }

   private:
    int *_pstack;  // 动态开辟数组，存储顺序栈的元素
    int _top;      // 指向栈顶元素的位置
    int _size;     // 数组扩容的总大小

    void resize() {
        int *ptmp = new int[_size * 2];
        // 
        for (int i = 0; i < _size; ++i) {
            ptmp[i] = _pstack[i]; 
        }  // memcpy(ptmp, _pstack, sizeof(int)*_size); realloc
        delete[] _pstack;
        _pstack = ptmp;
        _size *= 2;
    }
};
SeqStack gs;  // 程序结束时析构
int main() {
    /*
    .data
    heap
    stack
    */
    SeqStack *ps = new SeqStack(60);  // 相当于 malloc内存开辟+SeqStack(60)对象构造
    ps->push(70);
    ps->push(80);
    ps->pop();
    cout << ps->top() << endl;
    // 堆上的对象我们必须手动delete
    delete ps;  //先调用ps->~SeqStack()+然后free(ps)   delete和free的区别

    // 1.开辟内存  2.调用构造函数
    SeqStack s;
    // s.init(5);  // 对象成员变量的初始化操作

    for (int i = 0; i < 15; ++i) {
        s.push(rand() % 100);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }

    // s.release(); // 释放对象成员变量占用的外部堆内存（外部资源）

    SeqStack s1(50);

    // s1.~SeqStack(); // 析构函数调用以后，我们说对象不存在了

    s1.push(30);  // 堆内存的非法访问了！！！

    return 0;  //
}