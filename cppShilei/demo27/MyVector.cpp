#include <iostream>
using namespace std;

template <typename T>
class Allocator {
   public:
    T* allocate(size_t size)  // 负责内存开辟
    {
        return (T*)malloc(sizeof(T) * size);
    }
    void deallocate(void* p)  // 负责内存释放
    {
        free(p);
    }
    void construct(T* p, const T& val)  // 负责对象构造
    {
        new (p) T(val);  // 定位new
    }
    void destroy(T* p)  // 负责对象析构
    {
        p->~T();  // ~T()代表了T类型的析构函数
    }
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器来实现
*/
template <typename T, typename Alloc = Allocator<T>>
class vector {
   public:
    vector(int size = 10) {
        // 需要把内存开辟和对象构造分开处理
        //_first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }
    ~vector() {
        // 析构容器有效的元素，然后释放_first指针指向的堆内存
        // delete[]_first;
        for (T* p = _first; p != _last; ++p) {
            // 把_first指针指向的数组的有效元素进行析构操作
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);  // 释放堆上的数组内存
        _first = _last = _end = nullptr;
    }
    vector(const vector<T>& rhs) {
        int size = rhs._end - rhs._first;
        //_first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            //_first[i] = rhs._first[i];
            _allocator.construct(_first + i, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
    }
    vector<T>& operator=(const vector<T>& rhs) {
        if (this == &rhs) return *this;

        // delete[]_first;
        for (T* p = _first; p != _last; ++p) {
            // 把_first指针指向的数组的有效元素进行析构操作
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);

        int size = rhs._end - rhs._first;
        //_first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            //_first[i] = rhs._first[i];
            _allocator.construct(_first + i, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }
    void push_back(const T& val)  // 向容器末尾添加元素
    {
        if (full()) expand();
        //*_last++ = val;   _last指针指向的内存构造一个值为val的对象
        _allocator.construct(_last, val);
        _last++;
    }
    void pop_back()  // 从容器末尾删除元素
    {
        if (empty()) return;
        //--_last; // 不仅要把_last指针--，还需要析构删除的元素
        --_last;
        _allocator.destroy(_last);
    }
    T back() const  // 返回容器末尾的元素的值
    {
        return *(_last - 1);
    }
    bool full() const { return _last == _end; }
    bool empty() const { return _first == _last; }
    int size() const { return _last - _first; }
    T& operator[](int index) {
        if (index < 0 || index >= size()) {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    // 迭代器一般实现容器的嵌套类型
    class iterator {
       public:
        iterator(T* ptr = nullptr) : _ptr(ptr) {}
        bool operator!=(const iterator& it) const { return _ptr != it._ptr; }
        void operator++() { ++_ptr; }
        T& operator*() { return *_ptr; }  // int dat = *it; *it = 20;
        const T& operator*() const { return *_ptr; }

       private:
        T* _ptr;
    };
    iterator begin() { return iterator(_first); }
    iterator end() { return iterator(_last); }

   private:
    T* _first;         // 指向数组起始的位置
    T* _last;          // 指向数组中有效元素的后继位置
    T* _end;           // 指向数组空间的后继位置
    Alloc _allocator;  // 定义容器的空间配置器对象

    void expand()  // 容器的二倍扩容
    {
        int size = _end - _first;
        // T *ptmp = new T[2 * size];
        T* ptmp = _allocator.allocate(2 * size);
        for (int i = 0; i < size; ++i) {
            // ptmp[i] = _first[i];
            _allocator.construct(ptmp + i, _first[i]);
        }
        // delete[]_first;
        for (T* p = _first; p != _last; ++p) {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        _first = ptmp;
        _last = _first + size;
        _end = _first + 2 * size;
    }
};

class Test {
   public:
    Test() { cout << "Test()" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test&) { cout << "Test(const Test&)" << endl; }
};

int main() {
    vector<int> vec;

    for (int i = 0; i < 20; i++) {
        vec.push_back(rand() % 100 + 1);
    }

    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    vector<int>::iterator it = vec.begin();
    for (; it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // foreach底层原理，就是通过容器的迭代器来实现容器遍历的
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}