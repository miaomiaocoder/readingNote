#include <iostream>
using namespace std;

class Test {
   public:
    // 可以构造三种，Test() Test(10) Test(10, 10)
    Test(int a = 5, int b = 5) : ma(a), mb(b) {
        cout << "Test(int, int)" << endl;
    }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& src) : ma(src.ma), mb(src.mb) {
        cout << "Test(const Test&)" << endl;
    }
    void operator=(const Test& src) {
        ma = src.ma;
        mb = src.mb;
        cout << "operator=" << endl;
    }

   private:
    int ma;
    int mb;
};
Test t1(10, 10);  // 1.Test(int, int)
int main() {
    Test t2(20, 20);  // 3.Test(int, int)
    Test t3 = t2;     // 4.Test(const Test&)

    // static Test t4(30, 30);
    static Test t4 = Test(30, 30);  // 5.Test(int, int)
    t2 = Test(40, 40);              // 6.Test(int, int) operator= ~Test()

    // (50, 50) =  (Test)50; Test(int)
    t2 = (Test)(50, 50);          // 7.Test(int,int) operator=  ~Test()
    t2 = 60;                      // Test(int) 8.Test(int,int) operator= ~Test()
    Test* p1 = new Test(70, 70);  // 9. Test(int,int)
    Test* p2 = new Test[2];       // 10. Test(int,int) Test(int,int)
    // Test* p3 = &Test(80, 80); // 11. Test(int,int)  ~Test()
    const Test& p4 = Test(90, 90);  // 12. Test(int,int)
    delete p1;                      // 13.~Test()
    delete[] p2;                    // 14. ~Test() ~Test()
}
Test t5(100, 100);  // 2.Test(int, int)