## lambda表达式的应用实践
#### 代码示例1
```cpp
#include <functional>
#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, function<int(int, int)>> caculateMap;

    caculateMap[1] = [](int a, int b) -> int { return a + b; };
    caculateMap[2] = [](int a, int b) -> int { return a - b; };
    caculateMap[3] = [](int a, int b) -> int { return a * b; };
    caculateMap[4] = [](int a, int b) -> int { return a / b; };

    cout << "选择：";
    int choice;
    cin >> choice;
    cout << "10 和 15:" << caculateMap[choice](10, 15) << endl;

    return 0;
}
```
#### 代码示例2
```cpp
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>

using namespace std;

/*
既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，
怎么办？用什么类型来表示lambda表达式？
当然是用function类型来表示函数对象的类型了   bind1st/bind2nd bind绑定器

lambda表达式 =》 函数对象
*/

class Data {
   public:
    Data(int val1 = 10, int val2 = 10) : ma(val1), mb(val2) {}
    bool operator>(const Data& data) const { return ma > data.ma; }
    bool operator<(const Data& data) const { return ma < data.ma; }

   private:
    int ma;
    int mb;
};

class data2 {
   public:
    data2(int val1 = 10, int val2 = 10) : ma(val1), mb(val2) {}
    int ma;
    int mb;
};

int main() {
    // 优先级队列
    priority_queue<Data> q;
    q.push(Data(10, 20));
    q.push(Data(15, 15));
    q.push(Data(20, 10));

    using FUNC = function<bool(data2&, data2&)>;
    priority_queue<data2, vector<data2>, FUNC> maxHeap(
        [](data2& d1, data2& d2) -> bool { return d1.ma > d2.ma; });

    // 智能指针自定义删除器   delete p;  FILE*   fclose(FILE*)
    unique_ptr<FILE, function<void(FILE*)>> ptr1(fopen("data.txt", "w"),
                                                 [](FILE* pf) { fclose(pf); });

    return 0;
}
```