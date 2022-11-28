#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>  // C++ STL所有的容器都不是线程安全的
#include <thread>

using namespace std;

/*
C++多线程编程 - 线程间的同步通信机制
多线程编程两个问题：
1.线程间的互斥
竟态条件 =》 临界区代码段 =》 保证原子操作 =》互斥锁mutex  轻量级的无锁实现CAS
strace ./a.out mutex => pthread_mutex_t
2.线程间的同步通信
生产者，消费者线程模型
*/

/*
C++ wait/notify机制

notify_one：唤醒等待线程中的一个，唤醒的线程顺序执行。
notify_all：唤醒所有等待的线程，唤醒的线程抢占式执行。
wait：等待。需要其它的接口来唤醒。
*/

std::mutex mtx;              // 定义互斥锁，做线程间的互斥操作
std::condition_variable cv;  // 定义条件变量，做线程间的同步通信操作

// 生产者生产一个物品，通知消费者消费一个；消费完了，消费者再通知生产者继续生产物品
class Queue {
   public:
    void put(int val)  // 生产物品
    {
        // lock_guard<std::mutex> guard(mtx); // scoped_ptr
        unique_lock<std::mutex> lck(mtx);  // unique_ptr
        while (!que.empty()) {
            // que不为空，生产者应该通知消费者去消费，消费完了，再继续生产
            // 生产者线程进入#1等待状态，并且#2把mtx互斥锁释放掉
            cv.wait(lck);
        }
        que.push(val);
        /*
        notify_one:通知另外的一个线程的
        notify_all:通知其它所有线程的
        通知其它所有的线程，我生产了一个物品，你们赶紧消费吧
        其它线程得到该通知，就会从等待状态 =》 阻塞状态 =》
        获取互斥锁才能继续执行
        */
        cv.notify_all();
        cout << "生产者 生产:" << val << "号物品" << endl;
    }
    int get()  // 消费物品
    {
        // lock_guard<std::mutex> guard(mtx); // scoped_ptr
        unique_lock<std::mutex> lck(mtx);  // unique_ptr
        while (que.empty()) {
            // 消费者线程发现que是空的，通知生产者线程先生产物品
            // #1 进入等待状态 # 把互斥锁mutex释放
            cv.wait(lck);
        }
        int val = que.front();
        que.pop();
        cv.notify_all();  // 通知其它线程我消费完了，赶紧生产吧
        cout << "消费者 消费:" << val << "号物品" << endl;
        return val;
    }

   private:
    queue<int> que;
};

void producer(Queue *que)  // 生产者线程
{
    for (int i = 1; i <= 10; ++i) {
        que->put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void consumer(Queue *que)  // 消费者线程
{
    for (int i = 1; i <= 10; ++i) {
        que->get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    Queue que;  // 两个线程共享的队列

    std::thread t1(producer, &que);
    std::thread t2(consumer, &que);

    t1.join();
    t2.join();

    return 0;
}