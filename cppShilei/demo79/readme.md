## 单例模式
单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
```
A *p1 = new A();
A *p2 = new A();
A *p3 = new A(); 
```
常用到的，比如日志模块，数据库模块  

单例模式：  
饿汉式单例模式：还没有获取实例对象，实例对象就已经产生了  
懒汉式单例模式：唯一的实例对象，直到第一次获取它的时候，才产生  

#### 饿汉式单例模式
```cpp
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
```

#### 懒汉单例模式示例1
```cpp
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
```

#### 懒汉单例模式示例2
```cpp
#include <iostream>

// 线程安全的懒汉式单例模式 https://blog.csdn.net/QIANGWEIYUAN
class Singleton {
   public:
    static Singleton *getInstance()  // #3 获取类的唯一实例对象的接口方法
    {
        // g++ -o run 单例模式.cpp -g   gdb run
        // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
        static Singleton instance;  // #2 定义一个唯一的类的实例对象
        return &instance;
    }

   private:
    Singleton()  // #1 构造函数私有化
    {
        // 很多初始化的代码
    }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    std::cout << p1 << " " << p2 << " " << p3 << std::endl;

    return 0;
}
```

## 参考资料
- [C++设计模式 - 单例模式](https://blog.csdn.net/QIANGWEIYUAN/article/details/88544524)