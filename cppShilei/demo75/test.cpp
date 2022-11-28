#include <iostream>
#include <list>
#include <mutex>
#include <thread>
using namespace std;

/*
C++ thread 模拟车站三个窗口卖票的程序

线程间的互斥 =》 互斥锁mutex =》 lock_guard封装mutex
*/
int ticketCount = 100;  // 车站有100张车票，由三个窗口一起卖票
std::mutex mtx;         // 全局的一把互斥锁
/*
多线程程序
竞态条件：多线程程序执行的结果是一致的，不会随着CPU对线程不同的调用顺序，而产生不同
的运行结果。
*/
// 模拟卖票的线程函数  lock_guard unique_lock
void sellTicket(int index) {
    while (ticketCount > 0)  // ticketCount=1  锁+双重判断
    {
        // mtx.lock();
        {
            // 保证所有线程都能释放锁，防止死锁问题的发生 scoped_ptr
            lock_guard<std::mutex> lock(mtx);
            if (ticketCount > 0) {
                // 临界区代码段  =》  原子操作 =》 线程间互斥操作了 =》 mutex
                cout << "窗口:" << index << "卖出第:" << ticketCount << "张票!"
                     << endl;
                ticketCount--;
            }
        }
        // mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    list<std::thread> tlist;
    for (int i = 1; i <= 3; ++i) {
        tlist.push_back(std::thread(sellTicket, i));
    }

    for (std::thread &t : tlist) {
        t.join();
    }

    cout << "所有窗口卖票结束!" << endl;

    return 0;
}