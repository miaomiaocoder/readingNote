## 不带引用计数的智能指针

C++库中提供的不带引用计数的智能指针主要包括：  
```auto_ptr```  
C++11新标准：```unique_ptr```   
boost：```scoped_ptr```

#### ```autp_ptr```
- ```auto_ptr```智能指针不带引用计数，那么它处理浅拷贝的问题，是直接把前面的```auto_ptr```都置为```nullptr```，只让最后一个```auto_ptr```持有资源。

#### ```scoped_ptr```  
- 从根本上杜绝了智能指针浅拷贝的发生，所以```scoped_ptr```也是不能用在容器当中的，如果容器互相进行拷贝或者赋值，就会引起```scoped_ptr```对象的拷贝构造和赋值，这是不允许的，代码会提示编译错误。

#### ```unique_ptr```  
- unique_ptr有一点和scoped_ptr做的一样，就是去掉了拷贝构造函数和operator=赋值重载函数，禁止用户对unique_ptr进行显示的拷贝构造和赋值，防止智能指针浅拷贝问题的发生。

- 但是unique_ptr提供了带右值引用参数的拷贝构造和赋值，也就是说，unique_ptr智能指针可以通过右值引用进行拷贝构造和赋值操作，或者在产生unique_ptr临时对象的地方，如把unique_ptr作为函数的返回值。

> 可以看到，unique_ptr从名字就可以看出来，最终也是只能有一个该智能指针引用资源，因此建议在使用不带引用计数的智能指针时，可以优先选择unique_ptr智能指针。

## 参考链接
- [深入掌握C++智能指针](https://blog.csdn.net/QIANGWEIYUAN/article/details/88562935)
- [罗剑锋的 C++ 实战笔记](https://time.geekbang.org/column/intro/100051801)
