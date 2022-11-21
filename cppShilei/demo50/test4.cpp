#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main() {
    set<int, greater<int>> set1;
    for (int i = 0; i < 10; ++i) {
        set1.insert(rand() % 100);
    }

    for (int v : set1) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

// int main() {
//     priority_queue<int> que1;  // vector
//     for (int i = 0; i < 10; ++i) {
//         que1.push(rand() % 100);
//     }

//     while (!que1.empty()) {
//         cout << que1.top() << " ";
//         que1.pop();
//     }
//     cout << endl;

//     using MinHeap = priority_queue<int, vector<int>, greater<int>>;
//     MinHeap que2;  // vector
//     for (int i = 0; i < 10; ++i) {
//         que2.push(rand() % 100);
//     }

//     while (!que2.empty()) {
//         cout << que2.top() << " ";
//         que2.pop();
//     }
//     cout << endl;

//     return 0;
// }
