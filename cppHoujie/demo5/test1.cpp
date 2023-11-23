#include <iostream>
#include <string>

using namespace std;

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
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
namespace jj06 {
void test_multiset(long& value) {
    cout << "\ntest_multiset().......... \n";

    multiset<string> c;
    char buf[10];
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.insert(string(buf));
        } catch (exception& p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds : " << (clock() - timeStart) << endl;
    cout << "multiset.size()= " << c.size() << endl;
    cout << "multiset.max_size()= " << c.max_size() << endl;  // 214748364

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);  // 比 c.find(...) 慢很多
        cout << "std::find(), milli-seconds : " << (clock() - timeStart)
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    {
        timeStart = clock();
        auto pItem = c.find(target);  // 比 std::find(...) 快很多
        cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    c.clear();
    // test_moveable(multiset<MyString>(),multiset<MyStrNoMove>(), value);
}
}  // namespace jj06

int main(int argc, char** argv) {
    long value;
    cin >> value;
    jj06::test_multiset(value);

    return 0;
}