## 适配器模式

适配器模式的英文翻译是 Adapter Design Pattern。顾名思义，这个模式就是用来做适配的，它将不兼容的接口转换为可兼容的接口，让原本由于接口不兼容而不能一起工作的类可以一起工作。对于这个模式，有一个经常被拿来解释它的例子，就是 USB 转接头充当适配器，把两种不兼容的接口，通过转接变得可以一起工作。
```
代理模式：代理模式在不改变原始类接口的条件下，为原始类定义一个代理类，主要目的是控制访问，而非加强功能，这是它跟装饰器模式最大的不同。  
桥接模式：桥接模式的目的是将接口部分和实现部分分离，从而让它们可以较为容易、也相对独立地加以改变。  
装饰器模式：装饰者模式在不改变原始类接口的情况下，对原始类功能进行增强，并且支持多个装饰器的嵌套使用。  
适配器模式：适配器模式是一种事后的补救策略。适配器提供跟原始类不同的接口，而代理模式、装饰器模式提供的都是跟原始类相同的接口。  
```
```cpp
#include <iostream>
#include <string>
using namespace std;

/*
适配器模式：让不兼容的接口可以在一起工作
电脑  =》   投影到    =》   投影仪上   VGA  HDMI  TypeC

VGA接口的电脑， (TV)投影仪也是VGA接口
*/
class VGA  // VGA接口类
{
   public:
    virtual void play() = 0;
};
// TV01表示支持VGA接口的投影仪
class TV01 : public VGA {
   public:
    void play() { cout << "通过VGA接口连接投影仪，进行视频播放" << endl; }
};

// 实现一个电脑类(只支持VGA接口)
class Computer {
   public:
    // 由于电脑只支持VGA接口，所以该方法的参数也只能支持VGA接口的指针/引用
    void playVideo(VGA *pVGA) { pVGA->play(); }
};
/*
方法1：换一个支持HDMI接口的电脑，这个就叫代码重构
方法2：买一个转换头（适配器），能够把VGA信号转成HDMI信号，这个叫添加适配器类
*/

// 进了一批新的投影仪，但是新的投影仪都是只支持HDMI接口
class HDMI {
   public:
    virtual void play() = 0;
};
class TV02 : public HDMI {
   public:
    void play() { cout << "通过HDMI接口连接投影仪，进行视频播放" << endl; }
};

// 由于电脑（VGA接口）和投影仪（HDMI接口）无法直接相连，所以需要添加适配器类
class VGAToHDMIAdapter : public VGA {
   public:
    VGAToHDMIAdapter(HDMI *p) : pHdmi(p) {}
    void play()  // 该方法相当于就是转换头，做不同接口的信号转换的
    {
        pHdmi->play();
    }

   private:
    HDMI *pHdmi;
};

int main() {
    Computer computer;
    // computer.playVideo(new TV01());
    computer.playVideo(new VGAToHDMIAdapter(new TV02()));
    return 0;
}
```