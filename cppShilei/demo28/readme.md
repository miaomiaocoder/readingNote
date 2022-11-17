### 迭代器的失效问题？
1. 迭代器为什么会失效？  
    **a**：当容器调用erase方法后，当前位置到容器末尾元素的所有的迭代器全部失效了  
    **b**：当容器调用insert方法后，当前位置到容器末尾元素的所有的迭代器全部失效了。  
    ```
               迭代器依然有效    迭代器全部失效   
    首元素   ->  插入点/删除点  ->  末尾元素  
    ```
    **c**：insert来说，如果引起容器内存扩容，原来容器的所有的迭代器就全部失效了。
    ```  
    首元素   ->  插入点/删除点  ->  末尾元素  
    ```
    **d**：不同容器的迭代器是不能进行比较运算的

2. 迭代器失效了以后，问题该怎么解决？  
    对插入/删除点的迭代器进行更新操作

> 注意以上是msvc下失效的情况，msvc和g++下测试的迭代器失效情况不同。从GCC的标准库实现而言，vector的迭代器定位是使用的裸指针，因此只要没有发生重新分配内存（包括```reserve```，```shrink_to_fit```，以及因```push_back```，```insert```导致的扩大），迭代器实际上不会失效。
```cpp  
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> arr = {1, 2, 3};
    arr.reserve(10);
    auto it = arr.begin() + 2;
    arr.insert(arr.begin() + 1, 5);
    cout << *it << endl;

    for (auto &x : arr) cout << x << " ";
    cout << endl;
}
/*
linux下测试为：
$ ./test
2
1 5 2 3 
###############
msvc下测试为：
C:\Users\renzhenhua\Desktop\VS项目\ConsoleApplication\Debug\ConsoleApplication.exe (进程 22780)已退出，代码为 -1073741819。
按任意键关闭此窗口. . .
*/
```    

#### 例子一
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    // 把vec容器中所有的偶数全部删除
    auto it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            // 迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
            vec.erase(it);
        }
    }

    return 0;
}
```
修改后的代码，要注意保证程序逻辑不变
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    for (int v : vec) cout << v << " ";
    cout << endl;

    // 把vec容器中所有的偶数全部删除
    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it % 2 == 0)
            it = vec.erase(it);
        else
            ++it;
    }

    for (int v : vec) cout << v << " ";
    cout << endl;

    return 0;
}
// linux下输出结果
$ make test1
$ ./test1
84 87 78 16 94 36 87 93 50 22 63 28 91 60 64 27 41 27 73 37 
87 87 93 63 91 27 41 27 73 37 
```

#### 例子二
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
    auto it = vec.begin();
    for (; it != vec.end(); ++it)
        if (*it % 2 == 0) {
            // 这里的迭代器在第一次insert之后，iterator就失效了
            vec.insert(it, *it - 1);
            break;
        }

    return 0;
}
```
修改后的代码，要注意保证程序逻辑不变
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) vec.push_back(rand() % 100 + 1);

    for (int v : vec) cout << v << " ";
    cout << endl;

    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
    auto it = vec.begin();
    for (; it != vec.end(); ++it)
        if (*it % 2 == 0) {
            it = vec.insert(it, *it - 1);
            ++it;
        }
        
    for (int v : vec) cout << v << " ";
    cout << endl;

    return 0;
}
```

#### 参考链接
- [c++标准库是如何实现迭代器失效的？ - nekosu的回答 - 知乎](https://www.zhihu.com/question/460078504/answer/1892277203)
- [c++标准库是如何实现迭代器失效的？ - rayhunter的回答 - 知乎](https://www.zhihu.com/question/460078504/answer/1893604802)