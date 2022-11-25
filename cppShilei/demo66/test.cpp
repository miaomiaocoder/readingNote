#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

template <typename Container>
void showContainer(Container &con) {
    for (typename Container::iterator it = con.begin(); it != con.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

template <typename Iteraotr, typename Compare>
Iteraotr my_find_if(Iteraotr first, Iteraotr last, Compare comp) {
    for (; first != last; ++first) {
        if (comp(*first)) {  // comp.operator()(*first)
            return first;
        }
    }
    return last;
}

template <typename Compare, typename T>
class _mybind1st {  // 绑定器是函数对象的一个应用
   public:
    _mybind1st(Compare comp, T val) : _comp(comp), _val(val) {}
    bool operator()(const T &second) { return _comp(_val, second); }

   private:
    Compare _comp;
    T _val;
};

// mybind1st(greater<int>, 70)
template <typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T &val) {
    // 直接使用函数模板，好处是，可以进行类型的推演
    return _mybind1st<Compare, T>(comp, val);
}

int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    showContainer(vec);
    sort(vec.begin(), vec.end());  // 默认从小到大排序
    showContainer(vec);

    // greater 二元函数对象
    sort(vec.begin(), vec.end(), greater<int>());  // 从大到小排序
    showContainer(vec);

    /* 把70按顺序插入到vec容器中    找第一个小于70的数字
    operator()(const T &val)
    greator a > b
    less    a < b
    绑定器 + 二元函数对象 => 一元函数对象
    bind1st: bool operator() (70, const _Ty& _Right)
    bind2nd: bool operator() (const _Ty& _Left, 70)
    */
    // auto it1  = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
    // auto it1  = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));
    auto it1 =
        my_find_if(vec.begin(), vec.end(), mybind1st(greater<int>(), 70));
    if (it1 != vec.end()) {
        vec.insert(it1, 70);
    }
    showContainer(vec);

    return 0;
}