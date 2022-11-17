#include <iostream>

using namespace std;

// 定义容器的空间配置器，和C++标准库的allocator实现一样
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
        // erase(it);  verify(it._ptr, _last);
        // insert(it, val); verify(it._ptr, _last);
        verify(_last - 1, _last);
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
    T& operator[](int index)  // vec[2]
    {
        if (index < 0 || index >= size()) {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    // insert erase

    // #1迭代器一般实现成容器的嵌套类型
    class iterator {
       public:
        friend class vector<T, Alloc>;
        iterator(vector<T, Alloc>* pvec = nullptr, T* ptr = nullptr)
            : _ptr(ptr), _pVec(pvec) {
            Iterator_Base* itb = new Iterator_Base(this, _pVec->_head._next);
            _pVec->_head._next = itb;
        }
        bool operator!=(const iterator& it) const {
            // 检查迭代器的有效性
            if (_pVec == nullptr || _pVec != it._pVec) {
                throw "iterator incompatable!";
            }
            return _ptr != it._ptr;
        }
        void operator++() {
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid!";
            }
            _ptr++;
        }
        T& operator*() {
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid!";
            }
            return *_ptr;
        }
        const T& operator*() const {
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid!";
            }
            return *_ptr;
        }

       private:
        T* _ptr;
        // 当前迭代器迭代器是哪个容器对象
        vector<T, Alloc>* _pVec;
    };
    // 需要给容器提供begin和end方法
    iterator begin() { return iterator(this, _first); }
    iterator end() { return iterator(this, _last); }

    // 检查迭代器失效
    void verify(T* first, T* last) {
        Iterator_Base* pre = &this->_head;
        Iterator_Base* it = this->_head._next;
        while (it != nullptr) {
            if (it->_cur->_ptr > first && it->_cur->_ptr <= last) {
                // 迭代器失效，把iterator持有的容器指针置nullptr
                it->_cur->_pVec = nullptr;
                // 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
                pre->_next = it->_next;
                delete it;
                it = pre->_next;
            } else {
                pre = it;
                it = it->_next;
            }
        }
    }

    // 自定义vector容器insert方法的实现
    iterator insert(iterator it, const T& val) {
        /*
        1.不考虑扩容 verify(_first - 1, _last);
        2.不考虑it._ptr的指针合法性
        */
        verify(it._ptr - 1, _last);
        T* p = _last;
        while (p > it._ptr) {
            _allocator.construct(p, *(p - 1));
            _allocator.destroy(p - 1);
            p--;
        }
        _allocator.construct(p, val);
        _last++;
        return iterator(this, p);
    }

    // 自定义vector容器erase方法的实现
    iterator erase(iterator it) {
        verify(it._ptr - 1, _last);
        T* p = it._ptr;
        while (p < _last - 1) {
            _allocator.destroy(p);
            _allocator.construct(p, *(p + 1));
            p++;
        }
        _allocator.destroy(p);
        _last--;
        return iterator(this, it._ptr);
    }

   private:
    T* _first;         // 指向数组起始的位置
    T* _last;          // 指向数组中有效元素的后继位置
    T* _end;           // 指向数组空间的后继位置
    Alloc _allocator;  // 定义容器的空间配置器对象

    // 容器迭代器失效增加代码
    struct Iterator_Base {
        Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
            : _cur(c), _next(n) {}
        iterator* _cur;
        Iterator_Base* _next;
    };
    Iterator_Base _head;

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

int main() {
    vector<int> vec(200);
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    // auto it1 = vec.end();
    ////vec.pop_back(); // verify(_last - 1, _last);
    // auto it2 = vec.end();
    // cout << (it1 != it2) << endl;

    /*for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            it = vec.insert(it, *it - 1);
            // vec.insert(it, *it - 1); // 这段代码在g++下迭代器不失效，msvc下失效
            ++it;
        }
    }

    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;*/

    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it % 2 == 0) {
            // 迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
            // it = vec.erase(it);  // insert(it, val)   erase(it)
            vec.erase(it); // 这段代码在g++下迭代器不失效，msvc下失效
        } else {
            ++it;
        }
    }

    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
