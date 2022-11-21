#include <iostream>
#include <vector>

using namespace std;

/*
vector：向量容器
底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容的

vector<int> vec;
增加:
vec.push_back(20); 末尾添加元素 O(1)   导致容器扩容
vec.insert(it, 20); it迭代器指向的位置添加一个元素20  O(n)   导致容器扩容

删除:
vec.pop_back(); 末尾删除元素 O(1)
vec.erase(it); 删除it迭代器指向的元素 O(n)

查询:
operator[] 下标的随机访问vec[5]  O(1)
iterator迭代器进行遍历
find，for_each
foreach => 通过iterator来实现的

注意：对容器进行连续插入或者删除操作(insert/erase)，一定要更新迭代器，否则第一次insert或者erase完成，
迭代器就失效了

常用方法介绍:
size()
empty()
reserve(20)：vector预留空间的
只给容器底层开辟指定大小的内存空间，并不会添加新的元素
resize(20)：容器扩容用的
不仅给容器底层开辟指定大小的内存空间，还会添加新的元素 
swap ：
两个容器进行元素交换

*/
int main() {
    vector<int> vec;  // vector<string> vec; 0 1 2 4 8 16 32 64
    // vec.reserve(20); // 叫做给vector容器预留空间
    vec.resize(20);

    cout << vec.empty() << endl;
    cout << vec.size() << endl;  // int()

    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    cout << vec.empty() << endl;
    cout << vec.size() << endl;

    // vector的operator[]运算符重载函数
    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // 把vec容器中所有的偶数全部删除
    auto it2 = vec.begin();
    while (it2 != vec.end()) {
        if (*it2 % 2 == 0) {
            it2 = vec.erase(it2);
        } else {
            ++it2;
        }
    }

    // 通过迭代器遍历vector容器
    auto it1 = vec.begin();
    for (; it1 != vec.end(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;

    // 给vector容器中所有的奇数前面都添加一个小于奇数1的偶数   44 45    56 57
    for (it1 = vec.begin(); it1 != vec.end(); ++it1) {
        if (*it1 % 2 != 0) {
            it1 = vec.insert(it1, *it1 - 1);
            ++it1;
        }
    }

    for (it1 = vec.begin(); it1 != vec.end(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;

    return 0;
}