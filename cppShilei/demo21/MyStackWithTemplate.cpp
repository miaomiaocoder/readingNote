#include <iostream>

using namespace std;

/*
函数模板
类模板 => 实例化 => 模板类
*/

// 类模板
template <typename T = int>
class SeqStack  // 模板名称+类型参数列表 = 类名称
{
   public:
    // 构造和析构函数名不用加<T>，其它出现模板的地方都加上类型参数列表
    SeqStack(int size = 10) : _pstack(new T[size]), _top(0), _size(size) {}
    ~SeqStack() {
        delete[] _pstack;
        _pstack = nullptr;
    }
    SeqStack(const SeqStack<T>& stack) : _top(stack._top), _size(stack._size) {
        _pstack = new T[_size];
        // 不要用memcopy进行拷贝
        for (int i = 0; i < _top; ++i) {
            _pstack[i] = stack._pstack[i];
        }
    }
    SeqStack<T>& operator=(const SeqStack<T>& stack) {
        if (this == &stack) return *this;

        delete[] _pstack;

        _top = stack._top;
        _size = stack._size;
        _pstack = new T[_size];
        // 不要用memcopy进行拷贝
        for (int i = 0; i < _top; ++i) {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }

    void push(const T& val);  // 入栈操作

    void pop()  // 出栈操作
    {
        if (empty()) return;
        --_top;
    }
    T top() const  // 返回栈顶元素
    {
        if (empty()) throw "stack is empty!";  // 抛异常也代表函数逻辑结束
        return _pstack[_top - 1];
    }
    bool full() const { return _top == _size; }  // 栈满
    bool empty() const { return _top == 0; }     // 栈空
   private:
    T* _pstack;
    int _top;
    int _size;

    // 顺序栈底层数组按2倍的方式扩容
    void expand() {
        T* ptmp = new T[_size * 2];
        for (int i = 0; i < _top; ++i) {
            ptmp[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = ptmp;
        _size *= 2;
    }
};
template <typename T>
void SeqStack<T>::push(const T& val)  // 入栈操作
{
    if (full()) expand();
    _pstack[_top++] = val;
}
int main() {
    // 类模板的选择性实例化
    // 模板类 class SeqStack<int>{};
    SeqStack<int> s1;
    s1.push(20);
    s1.push(78);
    s1.push(32);
    s1.push(15);
    s1.pop();
    cout << s1.top() << endl;

    SeqStack<> s2;

    return 0;
}