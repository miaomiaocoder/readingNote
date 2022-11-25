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