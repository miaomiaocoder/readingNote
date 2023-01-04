# 容器之分类与各种测试（一）

## 测试array

```cpp
using std::cin;
using std::cout;
using std::string;
const long ASIZE = 500000L;

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
```

```cpp
#include <array>
#include <cstdlib>  //qsort, bsearch, NULL
#include <ctime>
#include <iostream>

#include "test.h"

using namespace std;

namespace jj01 {
void test_array() {
    cout << "\ntest_array().......... \n";

    array<long, ASIZE> c;

    clock_t timeStart = clock();
    for (long i = 0; i < ASIZE; ++i) {
        c[i] = rand();
    }
    cout << "milli-seconds : " << (clock() - timeStart) << endl;  //
    cout << "array.size()= " << c.size() << endl;
    cout << "array.front()= " << c.front() << endl;
    cout << "array.back()= " << c.back() << endl;
    cout << "array.data()= " << c.data() << endl;

    long target = get_a_target_long();

    timeStart = clock();
    qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    long* pItem = (long*)::bsearch(&target, (c.data()), ASIZE, sizeof(long),
                                   compareLongs);
    cout << "qsort()+bsearch(), milli-seconds : " << (clock() - timeStart)
         << endl;  //
    if (pItem != NULL)
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;
}
}  // namespace jj01

int main(int argc, char** argv) {
    jj01::test_array();

    return 0;
}
```

```
$ ./main

test_array().......... 
milli-seconds : 6038
array.size()= 500000
array.front()= 1804289383
array.back()= 699496062
array.data()= 0x7ffc095c3630
target (0~2147483647): 1804289383
qsort()+bsearch(), milli-seconds : 70425
found, 1804289383
```