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