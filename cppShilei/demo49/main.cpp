#include <iostream>
#include <vector>
using namespace std;

/*
容器的迭代器
const_iterator:常量的正向迭代器  只能读，而不能写了
iterator:普通的正向迭代器
reverse_iterator:普通的反向迭代器
const_reverse_iterator:常量的反向迭代器
*/

int main() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100);
    }

    // vector<int>::iterator
    // auto it1 = vec.begin();
    // const_iterator   <=   iterator
    /*
    class const_iterator
    {
    public:
            const T& operator*(){return *_ptr;}
    }
    class iterator : public const_iterator
    {
            T& operator*(){return *_ptr;}
    }
    */
    vector<int>::const_iterator it1 = vec.begin();
    for (; it1 != vec.end(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;

    // rbegin()：返回的是最后一个元素的反向迭代器表示
    // rend：返回的是首元素前驱位置的迭代器的表示
    // vector<int>::reverse_iterator
    vector<int>::const_reverse_iterator rit = vec.rbegin();
    for (; rit != vec.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    /*for (int v : vec)
    {
            cout << v << " ";
    }
    */
    cout << endl;

    return 0;
}
