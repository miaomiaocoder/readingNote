## const, 指针, 引用的结合使用

```cpp
// 写一句代码，在内存的0x0018ff44处写一个4字节的10
    int *p1 = (int *)0x0018ff44;
    int *&&p2 = (int *)0x0018ff44;
    int *const &p2 = (int *)0x0018ff44;
```

```cpp
    int a = 10;
    int *p = &a;
    const int *&q = p;  // ❌错误
    // const int **q = &p;  // 引用还原成指针更方便查看
    // const int** <= int**   
```

```cpp
    int a = 10;
    const int *p = &a;
    int *&q = p; // ❌错误
    // int **q = &p; // 引用还原成指针更方便查看
    // int** <= const int**   
```

```cpp
    int a = 10;
    int *const p = &a;
    int *&q = p;  // ❌错误
    // int **q = &p; // 引用还原成指针更方便查看
    // int ** <= int *const* 错误
    // "int *const *" 类型的值不能用于初始化 "int **" 类型的实体  
```

注意引用不参与类型
```cpp
    std::cout << typeid(const int*&).name() << std::endl;
    // 打印结果为 ———— int const *
```