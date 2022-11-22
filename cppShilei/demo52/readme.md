# 面经题目

## 商汤 C++（机器学习） 二面面经

1. 程序的内存布局

2. 堆和栈的区别

3. 函数调用参数怎么传递的？

4. 函数的参数按照什么顺序压栈？

5. 为什么函数调用的参数要从右往左压栈？

6.  ```cpp
    string func(string s1, string s2) {
        string tmp = s1 + s2;
        return tmp;
    }
    int main() {
        string s = func(s1, s2);
        return 0;
    }
    ```
    - 分析构造函数、析构函数顺序。

    - 如果func函数内写成 ```return s1 + s2``` 有什么不同？
7. 一个结构体里面定义里面定义了一个char和double, 它的空间布局是怎么样的？空结构体呢？

8. 手撕代码——[leetcode772](https://leetcode.cn/problems/basic-calculator-iii/)

