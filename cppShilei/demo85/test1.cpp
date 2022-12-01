#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
C++11 STL 容器 push/insert -> emplace新方法
*/

class Test {
   public:
    Test(int a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(int a, int b) { cout << "Test(int, int)" << endl; }
    Test(const Test&) { cout << "Test(const Test&)" << endl; }

    Test(const Test&&) noexcept { cout << "Test(Test&&)" << endl; }
};

int main() {
    Test t1(10);
    vector<Test> v;
    v.reserve(100);

    cout << "1================" << endl;
    // 直接插入对象，两个是没有区别的
    v.push_back(t1);
    v.emplace_back(t1);
    cout << "2================" << endl;

    // 直接插入对象，两个是没有区别的
    v.push_back(Test(20));
    v.emplace_back(Test(20));
    cout << "3================" << endl;

    v.push_back(20);
    // 给emplace传入Test对象构造所需要的参数，直接在容器底层构造对象即可
    v.emplace_back(20);
    v.emplace_back(30, 40);
    cout << "4================" << endl;

    /*
     */
    map<int, string> m;
    m.insert(make_pair(10, "zhang san"));

    // ->在map底层直接调用普通构造函数，生成一个pair对象即可
    m.emplace(10, "li si");

    return 0;
}