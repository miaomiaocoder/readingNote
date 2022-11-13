## new, delete

#### new 有几种
在C++中，new有三种典型的使用方法：```plain new```，```nothrow new``` 和 ```placement new```（有三种分法，也有四种的）
- ```plain new``` 是普通```new```, **定义**如下
    ```cpp
        void* operator new(std::size_t) throw(std::bad_alloc);
        void operator delete(void *) throw();
    ```

    ```plain new```在空间分配失败的情况下，抛出异常```std::bad_alloc```而不是返回```NULL```
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;
    int main()
    {
	    try
	    {
		    char *p = new char[10e11];
		    delete p;
	    }
	    catch (const std::bad_alloc &ex)
	    {
		    cout << ex.what() << endl;
	    }
	    return 0;
    }
    //执行结果：bad allocation
    ```
- ```nothrow new``` 是普通```new```, ```nothrow new```在空间分配失败的情况下是不抛出异常，而是返回```NULL```。**定义**如下
    ```cpp
        void * operator new(std::size_t,const std::nothrow_t&) throw();
        void operator delete(void*) throw();
    ```
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    int main()
    {
        char *p = new(nothrow) char[10e11];
        if (p == NULL) 
        {
            cout << "alloc failed" << endl;
        }
        delete p;
        return 0;
    }
    //运行结果：alloc failed
    ```
- ```placement new``` 这种new允许在一块已经分配成功的内存上重新构造对象或对象数组。placement new不用担心内存分配失败，因为它根本不分配内存，它做的唯一一件事情就是调用对象的构造函数。定义如下：
    ```cpp
        void* operator new(size_t,void*);
        void operator delete(void*,void*);
    ```
    > 使用```placement new```需要注意两点：

    > 1. ```palcement new``` 的主要用途就是反复使用一块较大的动态分配的内存来构造不同类型的对象或者他们的数组

    > 2. ```placement new``` 构造起来的对象数组，要显式的调用他们的析构函数来销毁（析构函数并不释放对象的内存），千万不要使用```delete```，这是因为```placement new```构造起来的对象或数组大小并不一定等于原来分配的内存大小，使用```delete```会造成内存泄漏或者之后释放内存时出现运行时错误。
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;
    class ADT {
        int i;
        int j;
    public:
        ADT() {
            i = 10;
            j = 100;
            cout << "ADT construct i=" << i << " j=" << j << endl;
        }
        ~ADT() {
            cout << "ADT destruct" << endl;
        }
    };
    int main()
    {
        char* p = new(nothrow) char[sizeof ADT + 1];
        if (p == NULL) {
            cout << "alloc failed" << endl;
        }
        ADT* q = new(p) ADT;  //placement new:不必担心失败，只要p所指对象的的空间足够ADT创建即可
        //delete q;//错误!不能在此处调用delete q;
        q->ADT::~ADT();//显示调用析构函数
        delete[] p;
        return 0;
    }
    //输出结果：
    //ADT construct i=10 j=100
    //ADT destruct
    ```
1. 普通new
形式：
```
int* p = new int;
```
此时不能通过p是否为nullptr来判断内存是否开辟成功，而是需要通过bad_alloc来捕获异常。

2. (nothrow) new
形式：
```cpp
int *p = new (nothrow) int(20);
```
此时指针已经退化为C语言中通过malloc开辟内存得到的指针，是可以通过判空来验证是否成功开辟内存。

3. 申请指向常量内存的指针的new
形式：
```cpp
    const int* p = new const int(20);
```

4. 定位new
形式：
```cpp
    int data = 0;
    int *p = new (&data) int(20);
```
在已知的内存上进行new。

#### 参考链接
   
[阿秀的学习笔记](https://interviewguide.cn/)

