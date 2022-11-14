#include <iostream>

using namespace std;

class Test {
   public:
    Test(int data = 10) : mb(data), ma(mb) {}
    void show() { cout << "ma:" << ma << " mb:" << mb << endl; }

   private:
    // 成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关！
    int ma;
    int mb;
};
int main() {
    Test t;  // 0xCCCCCCCC  -858993460
    // g++ 输出 ma:0 mb:10
    // msvc 输出 ma:-858993460 mb:10
    t.show();
    return 0;
}