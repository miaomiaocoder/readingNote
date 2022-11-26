#include <functional>
#include <iostream>
#include <map>

using namespace std;

/*
既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，
怎么办？用什么类型来表示lambda表达式？
当然是用function类型来表示函数对象的类型了   bind1st/bind2nd bind绑定器

lambda表达式 =》 函数对象
*/

int main() {
    map<int, function<int(int, int)>> caculateMap;

    caculateMap[1] = [](int a, int b) -> int { return a + b; };
    caculateMap[2] = [](int a, int b) -> int { return a - b; };
    caculateMap[3] = [](int a, int b) -> int { return a * b; };
    caculateMap[4] = [](int a, int b) -> int { return a / b; };

    cout << "选择：";
    int choice;
    cin >> choice;
    cout << "10 和 15:" << caculateMap[choice](10, 15) << endl;

    return 0;
}
