#include <cstring>
#include <iostream>
using namespace std;

class CMyString {
   public:
    CMyString(const char* str = nullptr) {
        cout << "CMyString(const char*)" << endl;
        if (str != nullptr) {
            mptr = new char[strlen(str) + 1];
            strcpy(mptr, str);
        } else {
            mptr = new char[1];
            *mptr = '\0';
        }
    }
    ~CMyString() {
        cout << "~CMyString" << endl;
        delete[] mptr;
        mptr = nullptr;
    }
    // 带左值引用参数的拷贝构造
    CMyString(const CMyString& str) {
        cout << "CMyString(const CMyString&)" << endl;
        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
    }
    // 带右值引用参数的拷贝构造
    CMyString(CMyString&& str) noexcept  // str引用的就是一个临时对象
    {
        cout << "CMyString(CMyString&&)" << endl;
        mptr = str.mptr;
        str.mptr = nullptr;
    }
    // 带左值引用参数的赋值重载函数
    CMyString& operator=(const CMyString& str) {
        cout << "operator=(const CMyString&)" << endl;
        if (this == &str) return *this;

        delete[] mptr;

        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
        return *this;
    }
    // 带右值引用参数的赋值重载函数
    CMyString& operator=(CMyString&& str) noexcept  // 临时对象
    {
        cout << "operator=(CMyString&&)" << endl;
        if (this == &str) return *this;

        delete[] mptr;

        mptr = str.mptr;
        str.mptr = nullptr;
        return *this;
    }
    const char* c_str() const { return mptr; }

   private:
    char* mptr;
    friend CMyString operator+(const CMyString& lhs, const CMyString& rhs);
    friend ostream& operator<<(ostream& out, const CMyString& str);
};

CMyString operator+(const CMyString& lhs, const CMyString& rhs) {
    // char* ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
    CMyString tmpStr;
    tmpStr.mptr = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
    strcpy(tmpStr.mptr, lhs.mptr);
    strcat(tmpStr.mptr, rhs.mptr);
    // delete []ptmp;
    return tmpStr;
    // return CMyString(ptmp);
}

ostream& operator<<(ostream& out, const CMyString& str) {
    out << str.mptr;
    return out;
}

template <typename T>
struct Allocator {
    T* allocate(size_t size)  // 负责内存开辟
    {
        return (T*)malloc(sizeof(T) * size);
    }
    void deallocate(void* p)  // 负责内存释放
    {
        free(p);
    }
    /*void construct(T *p, const T &val) // 负责对象构造
    {
            new (p) T(val); // 定位new
    }
    void construct(T *p, T &&val) // 负责对象构造
    {
            new (p) T(std::move(val)); // 定位new
    }*/
    template <typename Ty>
    void construct(T* p, Ty&& val) {
        new (p) T(std::forward<Ty>(val));
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
            _allocator.destroy(
                p);  // 把_first指针指向的数组的有效元素进行析构操作
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

    //////////////////////////////////////////
    /*void push_back(const T &val) // 接收左值
    {
            if (full())
                    expand();

            _allocator.construct(_last, val);
            _last++;
    }

    void push_back(T &&val) // 接收右值 一个右值引用变量本身还是一个左值
    {
            if (full())
                    expand();

            _allocator.construct(_last, std::move(val));
            _last++;
    }*/
    // void push_back(CMyString &val)
    // CMyString&& + && = void push_back(CMyString&&val)
    template <typename Ty>    // 函数模板的类型推演 + 引用折叠
    void push_back(Ty&& val)  // Ty CMyString& + && = CMyString&
    {
        if (full()) expand();

        // move(左值)：移动语义，得到右值类型   (int&&)a
        // forward:类型完美转发，能够识别左值和右值类型
        _allocator.construct(_last, std::forward<Ty>(val));
        _last++;
    }

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

int main() {
    CMyString str1 = "aaa";
    vector<CMyString> vec;

    cout << "-----------------------" << endl;
    vec.push_back(str1);   // CMyString&
    vec.push_back(std::move(str1)); 
    vec.push_back(CMyString("bbb"));  // CMyString&& move  forword
    cout << "-----------------------" << endl;

    return 0;
}