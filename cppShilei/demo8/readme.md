## const和一级指针的结合

#### const修饰的量常出现的错误
- 1.常量不能再作为左值  《=  直接修改常量的值
- 2.不能把常量的地址泄露给一个普通的指针或者普通的引用变量 《= 可以间接修改常量的值


```cpp
    const int a = 10;
    int *p = &a;     // 错误  invalid conversion from ‘const int*’ to ‘int*’
```

#### const和一级指针的结合
C++的语言规范：**const修饰的是离它最近的类型**, 从右向左读
```c++
    // const 修饰指针指向的量;
    // 指针指向的是一个“只读变量”，不允许修改;
    const int *p; //可以任意指向不同的int类型的内存，但是不能通过指针间接修改指向的内存的值
    int const *p; // 与const int *p 等价
```

```c++
    // const 修饰指针本身
    int *const p = &a; // 这个指针p现在是常量，不能再指向其它内存，但是可以通过指针解引用修改指向的内存的值
    // 距离p最近的符合是const，意味着p是常量，p的类型由声明符的其它部分决定，*表明p是指针, int表明p指向的对象是int
```


```c++
    // const 修饰了指针的本身和指向的量
    const int *const p = &a;
    int const *const p = &b; // 与 const int *const等价
```

#### const和指针的类型转换
```cpp
    // 左值 <= 右值
    int*    <=    const int*    //是错误的！
    const int*  <=   int*       //是可以的！

    // const 和 二级指针结合
    int** <= const int**        //是错误的！
    const int** <= int**        //是错误的！

    // const 和 一级指针结合
    int** <= int*const*			//是错误的！  
    int*const* <= int**         //是可以的！
    // int* const* p 中const修饰的是一级指针
```

```cpp
    int a = 10;
    int* p1 = &a;
    const int* p2 = &a;  // int* 转换为 const int*
    int* const p3 = &a;  // int* 转换为 int*
    int *p4 = p3;        // int* 转换为 int*
```

**const如果右边没有指针*的话，const是不参与类型的**
```cpp
    int* q1 = nullptr;
    int* const q2 = nullptr;
    // ./demo8 | c++filt -t 才可以得到正确答案(g++， clang++下需要这样)
    /* 例子
    $./demo8 | c++filt -t
    int*
    int*
    */
    cout << typeid(q1).name() << endl;
    cout << typeid(q2).name() << endl; // 注意 q2 结果为 int *
```
