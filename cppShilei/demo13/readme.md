## 类和对象，this指针

#### class的内存
```c++
// vs命令提示符中
// cl /d1 reportSingleClassLayoutCGoods main.cpp 可以查看class内存布局
// cl main.cpp /d1reportSingleClassLayoutCGoods 与上面命令等价
// cl /d1 reportSingleClassLayoutXXX [filename] 格式

>cl /d1 reportSingleClassLayoutCGoods main.cpp
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
版权所有(C) Microsoft Corporation。保留所有权利。

main.cpp

class CGoods    size(40):
        +---
 0      | _name
        | <alignment member> (size=4)
24      | _price
32      | _amount
        | <alignment member> (size=4)
        +---

```