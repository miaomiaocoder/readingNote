## C++ emplace

#### 代码示例1
```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
C++11 STL 容器 push/insert -> emplace新方法
*/

class Test {
   public:
    Test(int a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(int a, int b) { cout << "Test(int, int)" << endl; }
    Test(const Test&) { cout << "Test(const Test&)" << endl; }

    Test(const Test&&) noexcept { cout << "Test(Test&&)" << endl; }
};

int main() {
    Test t1(10);
    vector<Test> v;
    v.reserve(100);

    cout << "1================" << endl;
    // 直接插入对象，两个是没有区别的
    v.push_back(t1);
    v.emplace_back(t1);
    cout << "2================" << endl;

    // 直接插入对象，两个是没有区别的
    v.push_back(Test(20));
    v.emplace_back(Test(20));
    cout << "3================" << endl;

    v.push_back(20);
    // 给emplace传入Test对象构造所需要的参数，直接在容器底层构造对象即可
    v.emplace_back(20);
    v.emplace_back(30, 40);
    cout << "4================" << endl;

    /*
     */
    map<int, string> m;
    m.insert(make_pair(10, "zhang san"));

    // ->在map底层直接调用普通构造函数，生成一个pair对象即可
    m.emplace(10, "li si");

    return 0;
}
```
```cpp
$ ./test1
Test(int)
1================
Test(const Test&)
Test(const Test&)
2================
Test(int)
Test(Test&&)
~Test()
Test(int)
Test(Test&&)
~Test()
3================
Test(int)
Test(Test&&)
~Test()
Test(int)
Test(int, int)
4================
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
```
#### 代码示例2
```cpp
#include <iostream>
// #include <vector>
#include <map>

using namespace std;

/*
C++11 STL 容器 push/insert -> emplace新方法
*/

class Test {
   public:
    Test(int a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(int a, int b) { cout << "Test(int, int)" << endl; }
    Test(const Test&) { cout << "Test(const Test&)" << endl; }

    Test(const Test&&) noexcept { cout << "Test(Test&&)" << endl; }
};

// 实现容器的空间配置器
template <typename T>
struct MyAllocator {
    // allocate deallocate
    // construct destroy
    T* allocate(size_t size) { return (T*)malloc(size * sizeof(T)); }

    template <typename... Types>
    void construct(T* ptr, Types&&... args) {
        // args只是一个参数，而且是个Test对象，T也是Test对象
        new (ptr) T(std::forward<Types>(args)...);
    }
};

template <typename T, typename Alloc = MyAllocator<T>>
class vector {
   public:
    vector() : vec_(nullptr), size_(0), idx_(0) {}
    // 预留内存空间
    void reserve(size_t size) {
        vec_ = allocator_.allocate(size);
        size_ = size;
    }

    // push_back
    /*void push_back(const T& val) {
            allocator_.construct(vec_ + idx_, val);
            idx_++;
    }

    void push_back(T&& val) {
            allocator_.construct(vec_ + idx_, std::move(val));
            idx_++;
    }*/

    template <typename Type>
    void push_back(Type&& val) {
        allocator_.construct(vec_ + idx_, std::forward<Type>(val));
    }

    // 1. 引用折叠 实参：左值Test Test&+&&=Test& 右值 Test&& args
    template <typename... Types>
    void emplace_back(Types&&... args) {
        // 不管是左值引用、右值引用变量，它本身是个左值
        // 传递过程中要保持args的引用类型(左值的？右值的？)类型完美转发forward
        allocator_.construct(vec_ + idx_, std::forward<Types>(args)...);
        idx_++;
    }

   private:
    T* vec_;
    int size_;
    int idx_;
    Alloc allocator_;
};

int main() {
    Test t1(10);
    vector<Test> v;
    v.reserve(100);

    cout << "1================" << endl;
    // 直接插入对象，两个是没有区别的
    v.push_back(t1);
    v.emplace_back(t1);
    cout << "2================" << endl;

    // 直接插入对象，两个是没有区别的
    v.push_back(Test(20));
    v.emplace_back(Test(20));
    cout << "3================" << endl;

    v.push_back(20);
    // 给emplace传入Test对象构造所需要的参数，直接在容器底层构造对象即可
    v.emplace_back(20);
    v.emplace_back(30, 40);
    cout << "4================" << endl;

    /*
     */
    map<int, string> m;
    m.insert(make_pair(10, "zhang san"));
    m.emplace(
        10, "li si");  // ->在map底层直接调用普通构造函数，生成一个pari对象即可

    return 0;
}
```
```cpp
$ ./test2
Test(int)
1================
Test(const Test&)
Test(const Test&)
2================
Test(int)
Test(Test&&)
~Test()
Test(int)
Test(Test&&)
~Test()
3================
Test(int)
Test(int)
Test(int, int)
4================
~Test()
```
