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