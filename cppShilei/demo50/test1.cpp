#include <iostream>

using namespace std;

template <typename T>
bool compare(T a, T b) {
    return a > b;
}
int main() {
    cout << compare(10, 20) << endl;
    cout << compare('b', 'y') << endl;

    return 0;
}
