#include <iostream>
#include <mutex>

std::mutex mtx;

// 懒汉式单例模式 => 是不是线程安全的呢？   => 线程安全的懒汉式单例模式
class Singleton {
   public:
    // 是不是可重入函数呢？   锁+双重判断
    static Singleton *getInstance()  // #3 获取类的唯一实例对象的接口方法
    {
        // lock_guard<std::mutex> guard(mtx); // 锁的粒度太大了
        if (instance == nullptr) {
            std::lock_guard<std::mutex> guard(mtx);
            if (instance == nullptr) {
                /*
                开辟内存
                给instance赋值
                构造对象
                */
                instance = new Singleton();
            }
        }
        return instance;
    }

   private:
    static Singleton *volatile instance;  // #2 定义一个唯一的类的实例对象
    Singleton()                           // #1 构造函数私有化
    {}
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};
Singleton *volatile Singleton::instance = nullptr;

int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    std::cout << p1 << " " << p2 << " " << p3 << std::endl;

    return 0;
}