// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     vector<int> vec;
//     for (int i = 0; i < 20; ++i) {
//         vec.push_back(rand() % 100 + 1);
//     }

//     // 把vec容器中所有的偶数全部删除
//     auto it = vec.begin();
//     for (; it != vec.end(); ++it) {
//         if (*it % 2 == 0) {
//             // 迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
//             vec.erase(it);
//         }
//     }

//     return 0;
// }

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