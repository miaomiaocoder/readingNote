## 虚基类和虚继承
### 内存布局
#### 示例1
```cpp
#include <iostream>

using namespace std;

class A {
public:
private:
    int ma;
};
class B : virtual public A {
public:
private:
    int mb;
};
/*
A a; 4个字节
B b; ma,mb  8个字节+4=12个字节   vbptr
*/
int main() {
    return 0;
}
```
利用VS命令提示符查看类A, 类B大小
```cpp
>cl main.cpp /d1reportSingleClassLayoutA
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class A size(4):
        +---
 0      | ma
        +---


>cl main.cpp /d1reportSingleClassLayoutB
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class B size(12):
        +---
 0      | {vbptr}
 4      | mb
        +---
        +--- (virtual base A)
 8      | ma
        +---

B::$vbtable@:
 0      | 0
 1      | 8 (Bd(B+0)A)
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
               A       8       0       4 0
```
#### 示例2
```cpp
class A {
public:
    virtual void func() { cout << "call A::func" << endl; }
private:
    int ma;
};
class B : virtual public A {
public:
    void func() { cout << "call B::func" << endl; }
private:
    int mb;
};


>cl main.cpp /d1reportSingleClassLayoutA
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class A size(8):
        +---
 0      | {vfptr}
 4      | ma
        +---

A::$vftable@:
        | &A_meta
        |  0
 0      | &A::func

A::func this adjustor: 0


>cl main.cpp /d1reportSingleClassLayoutB
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class B size(16):
        +---
 0      | {vbptr}
 4      | mb
        +---
        +--- (virtual base A)
 8      | {vfptr}
12      | ma
        +---

B::$vbtable@:
 0      | 0
 1      | 8 (Bd(B+0)A)

B::$vftable@:
        | -8
 0      | &A::func
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
               A       8       0       4 0
```
#### 示例3
```cpp
class A {
public:
    void func() { cout << "call A::func" << endl; }

private:
    int ma;
};
class B : virtual public A {
public:
    virtual void func() { cout << "call B::func" << endl; }

private:
    int mb;
};


>cl main.cpp /d1reportSingleClassLayoutA
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class A size(4):
        +---
 0      | ma
        +---


>cl main.cpp /d1reportSingleClassLayoutB
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.34.31933 版
class B size(16):
        +---
 0      | {vfptr}
 4      | {vbptr}
 8      | mb
        +---
        +--- (virtual base A)
12      | ma
        +---

B::$vftable@:
        | &B_meta
        |  0
 0      | &B::func

B::$vbtable@:
 0      | -4
 1      | 8 (Bd(B+4)A)

B::func this adjustor: 0
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
               A      12       4       4 0
```

### 内存布局代码示例

#### code1
```cpp
#include <iostream>

using namespace std;

class A {
   public:
    virtual void func() { cout << "call A::func" << endl; }
    void operator delete(void *ptr) {
        cout << "operator delete p:" << ptr << endl;
        free(ptr);
    }

   private:
    int ma;
};
class B : virtual public A {
   public:
    void func() { cout << "call B::func" << endl; }

    void *operator new(size_t size) {
        void *p = malloc(size);
        cout << "operator new p:" << p << endl;
        return p;
    }

   private:
    int mb;
};

int main() {
    // 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
    A *p = new B();
    cout << "main p:" << p << endl;
    p->func();
    delete p;

    return 0;
}


// msvc x86运行结果
operator new p:00AB7F70
main p:00AB7F78
call B::func
operator delete p:00AB7F78
(进程 30460)已退出，代码为 3。

// g++运行结果
operator new p:0x5605b2f15eb0
main p:0x5605b2f15ec0
call B::func
operator delete p:0x5605b2f15ec0
free(): invalid pointer
Aborted
```

#### code2
```cpp
#include <iostream>

using namespace std;

class A {
   public:
    virtual void func() { cout << "call A::func" << endl; }
    void operator delete(void *ptr) {
        cout << "operator delete p:" << ptr << endl;
        free(ptr);
    }

   private:
    int ma;
};
class B : virtual public A {
   public:
    void func() { cout << "call B::func" << endl; }

    void *operator new(size_t size) {
        void *p = malloc(size);
        cout << "operator new p:" << p << endl;
        return p;
    }

   private:
    int mb;
};

int main() {  
    // 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
    B b;
    A *p = &b;  // new B(); // B::vftable
    cout << "main p:" << p << endl;
    p->func();
    // delete p;

    return 0;
}

// msvc x86
main p:0133FBE4
call B::func
(进程 7016)已退出，代码为 0。

// g++
main p:0x7fffb461bd50
call B::func

// 运行结果
```

