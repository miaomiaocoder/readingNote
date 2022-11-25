#include <cstring>
#include <iostream>

using namespace std;

/*
模板的完全特例化和非完全（部分）特例化
*/

template <typename T>
bool compare(T a, T b) {
    cout << "template compare" << endl;
    return a > b;
}

template <>
bool compare<const char*>(const char* a, const char* b) {
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}

int main() {
    compare(10, 20);
    compare("aaa", "bbb");
    return 0;
}

// $ ./test
// template compare
// compare<const char*>