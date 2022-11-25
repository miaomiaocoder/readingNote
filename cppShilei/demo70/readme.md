#### bind 

```
#include <functional>
#include <iostream>

using namespace std;

// C++11 bind绑定器 => 返回的结果还是一个函数对象

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

class Test {
   public:
    int sum(int a, int b) { return a + b; }
};

int main() {
    // bind是函数模板 可以自动推演模板类型参数
    bind(hello, "hello bind!")();
    cout << bind(sum, 10, 20)() << endl;
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;

    // 参数占位符, 绑定器出了语句，无法继续使用
    bind(hello, placeholders::_1)("hello bind 2!");
    cout << bind(sum, placeholders::_1, placeholders::_2)(200, 300) << endl;

    // 此处把bind返回的绑定器binder就复用起来了
    function<void(string)> func1 = bind(hello, placeholders::_1);
    func1("hello china!");
    func1("hello shan xi!");
    func1("hello si chuan!");

    return 0;
}
/*
$ ./test1
hello bind!
30
50
hello bind 2!
500
hello china!
hello shan xi!
hello si chuan!
*/
```

#### bind 和 function 实现线程池
```cpp
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class Thread {
   public:
    Thread(function<void()> func) : _func(func) {}
    thread start() {
        thread t(_func);  // _func()
        return t;
    }

   private:
    function<void()> _func;
};

class ThreadPool {
   public:
    ThreadPool() {}
    ~ThreadPool() {
        // 释放Thread对象占用的堆资源
        for (int i = 0; i < _pool.size(); ++i) {
            delete _pool[i];
        }
    }
    // 开启线程池
    void startPool(int size) {
        for (int i = 0; i < size; ++i) {
            _pool.push_back(
                new Thread(bind(&ThreadPool::runInThread, this, i)));
        }

        for (int i = 0; i < size; ++i) {
            _handler.push_back(_pool[i]->start());
        }

        for (thread &t : _handler) {
            t.join();
        }
    }

   private:
    vector<Thread *> _pool;
    vector<thread> _handler;
    // 把runInThread这个成员方法充当线程函数 thread pthread_create
    void runInThread(int id) { cout << "call runInThread！ id:" << id << endl; }
};

int main() {
    ThreadPool pool;
    pool.startPool(10);
    return 0;
}

/*
$ g++ test2.cpp -o test2 -pthread
$ ./test2
call runInThread！ id:2
call runInThread！ id:9
call runInThread！ id:7
call runInThread！ id:6
call runInThread！ id:1
call runInThread！ id:0
call runInThread！ id:3
call runInThread！ id:8
call runInThread！ id:5
call runInThread！ id:4
*/
```