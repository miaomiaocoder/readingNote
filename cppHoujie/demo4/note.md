# 容器之分类与各种测试（三）

## 测试list

![使用list](使用list.png)

```cpp
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

long get_a_target_long() {
    long target = 0;

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string() {
    long target = 0;
    char buf[10];

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

int compareLongs(const void* a, const void* b) {
    return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b) {
    if (*(string*)a > *(string*)b)
        return 1;
    else if (*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

#include <algorithm>  //find()
#include <cstdio>     //snprintf()
#include <cstdlib>    //abort()
#include <ctime>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

using namespace std;

namespace jj03 {
void test_list(long& value) {
    cout << "\ntest_list().......... \n";

    list<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (exception& p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds : " << (clock() - timeStart) << endl;
    cout << "list.size()= " << c.size() << endl;
    cout << "list.max_size()= " << c.max_size() << endl;  // 357913941
    cout << "list.front()= " << c.front() << endl;
    cout << "list.back()= " << c.back() << endl;

    string target = get_a_target_string();
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;

    timeStart = clock();
    c.sort();
    cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

    c.clear();
    // test_moveable(list<MyString>(), list<MyStrNoMove>(), value);
}
}  // namespace jj03

int main(int argc, char** argv) {
    long value;
    cin >> value;
    jj03::test_list(value);

    return 0;
}
```

g++ 测试结果
```cpp
$ ./main
1000000

test_list().......... 
milli-seconds : 247703
list.size()= 1000000
list.max_size()= 192153584101141162
list.front()= 180428938
list.back()= 429357853
target (0~2147483647): 429357853
std::find(), milli-seconds : 26840
found, 429357853
c.sort(), milli-seconds : 1004464
```

msvc测试结果
```cpp
1000000

test_list()..........
milli-seconds : 3113
list.size()= 1000000
list.max_size()= 119304647
list.front()= 41
list.back()= 12679
target (0~32767): 23456
std::find(), milli-seconds : 8
found, 23456
c.sort(), milli-seconds : 5098
```

## 测试forward_list

![使用容器forward_list](使用容器forward_list.png)

```cpp
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

long get_a_target_long() {
    long target = 0;

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string() {
    long target = 0;
    char buf[10];

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

int compareLongs(const void* a, const void* b) {
    return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b) {
    if (*(string*)a > *(string*)b)
        return 1;
    else if (*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

#include <algorithm>
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <forward_list>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace jj04 {
void test_forward_list(long& value) {
    cout << "\ntest_forward_list().......... \n";

    forward_list<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_front(string(buf));
        } catch (exception& p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds : " << (clock() - timeStart) << endl;
    cout << "forward_list.max_size()= " << c.max_size() << endl;  // 536870911
    cout << "forward_list.front()= " << c.front() << endl;

    string target = get_a_target_string();
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;

    timeStart = clock();
    c.sort();
    cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

    c.clear();
}
}  // namespace jj04

int main(int argc, char** argv) {
    long value;
    cin >> value;
    jj04::test_forward_list(value);

    return 0;
}
```

msvc x86 测试结果
```cpp
1000000

test_forward_list()..........
milli-seconds : 2905
forward_list.max_size()= 134217727
forward_list.front()= 12679
target (0~32767): 23456
std::find(), milli-seconds : 8
found, 23456
c.sort(), milli-seconds : 5312
```

## deque结构

![deque结构](deque结构.png)