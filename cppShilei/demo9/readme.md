## const和二级（多级）指针的结合

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
    int *p = &a;
    // error: invalid conversion from ‘int**’ to ‘const int**’
    // 一级指针中 int* 可以转换为 const int*, 注意区别
    const int **q = &p; // 错误 const int *||*q这样分开看，如果成立，可以把常量的地址赋值给p，错误; const int b = 20; *q = &b; (*q 等于 p, &b赋值给p, 错误)

    // 下面正确
    int a = 10;
    const int *p = &a;
    const int **q = &p;

    // 下面正确
    int a = 10;
    const int *p = &a;
    const int *const *q = &p;
```

```cpp
    // ./demo9 | c++filt -t
    int a = 10;
    int *p = &a;
    int **t = &p;
    int *const* q = t; // int*const* <= int** 可行
    cout << typeid(t).name() << endl;
    cout << typeid(q).name() << endl; 
```


例子
```cpp
    int a = 10;
    const int *p = &a;
    int *const* q = &p; // int *const* <= const int ** 
                        // 先看左边的const, const* <= *  ✔可行;  
                        // 去掉的左边的const, 看右边的const
                        // int* <= const int *, ❌错误;
                        // 错误

    int a = 10;
    int *const p = &a;
    int **q = &p; // 错误 int ** <= int *const * 也就是 * <= const* 

    int a = 10;
    int *p = &a;
    int **const q = &p;  // 正确 int** <= int**;

    int a = 10;
    int *p = &a;
    int *const*q = &p; // const* <= * 正确
```