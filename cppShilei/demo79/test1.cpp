#include <iostream>

// 饿汉式单例模式 一定是线程安全的
class Singleton {
   public:
    static Singleton *getInstance()  // #3 获取类的唯一实例对象的接口方法
    {
        return &instance;
    }

   private:
    static Singleton instance;  // #2 定义一个唯一的类的实例对象
    Singleton()                 // #1 构造函数私有化
    {}
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};
Singleton Singleton::instance;

int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    std::cout << p1 << " " << p2 << " " << p3 << std::endl;

    return 0;
}