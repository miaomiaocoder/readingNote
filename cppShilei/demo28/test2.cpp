// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     vector<int> vec;
//     for (int i = 0; i < 20; ++i) {
//         vec.push_back(rand() % 100 + 1);
//     }

//     // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
//     auto it = vec.begin();
//     for (; it != vec.end(); ++it)
//         if (*it % 2 == 0) {
//             // 这里的迭代器在第一次insert之后，iterator就失效了
//             vec.insert(it, *it - 1);
//             break;
//         }

//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) vec.push_back(rand() % 100 + 1);

    for (int v : vec) cout << v << " ";
    cout << endl;

    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
    auto it = vec.begin();
    for (; it != vec.end(); ++it)
        if (*it % 2 == 0) {
            it = vec.insert(it, *it - 1);
            ++it;
        }

    for (int v : vec) cout << v << " ";
    cout << endl;

    return 0;
}