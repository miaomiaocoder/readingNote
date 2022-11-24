// // g++ test2.cpp -o test2 -lpthread
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

class A {
   public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }

    void testA() { cout << "非常好用的方法！" << endl; }
};

// 子线程
void handler01(weak_ptr<A> pw) {
    // q访问A对象的时候，需要判断A对象是否存活。
    shared_ptr<A> sp = pw.lock();
    if (sp != nullptr) {
        sp->testA();
    } else {
        cout << "A对象已经析构，不能再访问!" << endl;
    }
}

// main线程
int main() {
    // A *p = new A();
    {
        shared_ptr<A> p(new A());
        thread t1(handler01, weak_ptr<A>(p));
        t1.detach();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::this_thread::sleep_for(std::chrono::seconds(20));
    // 阻塞i，等待子线程结束
    // t1.join();

    return 0;
}