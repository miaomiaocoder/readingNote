### 继承的本质和原理
```
继承的本质：
a. 代码的复用  
b. 类和类之间的关系：
组合：a part of... ...一部分的关系
继承：a kind of... ...一种的关系

继承方式     基类的访问限定     派生类的访问限定      (main)外部的访问限定
public 
			  public			public                 Y
			  protected			protected			   N
			  private			不可见的				   N         
protected(基类的成员的访问限定，在派生类里面是不可能超过继承方式的)
			  public			protected			   N
			  protected			protected			   N
			  private			不可见的				   N
private
			  public			private				   N
			  protected			private				   N
			  private			不可见的				   N

总结：
1.外部只能访问对象public的成员，protected和private的成员无法直接访问
2.在继承结构中，派生类从基类可以继承过来private的成员，但是派生类却无法直接访问
3.protected和private的区别？
在基类中定义的成员，想被派生类访问，但是不想被外部访问，那么在基类中，把相关成员定义成protected保护的；
如果派生类和外部都不打算访问，那么在基类中，就把相关成员定义成private私有的。
```
```
默认的继承方式是什么？
要看派生类是用class定义的，还是struct定义的？
class定义派生类，默认继承方式就是private私有的
struct定义派生类，默认继承方式就是public的
```