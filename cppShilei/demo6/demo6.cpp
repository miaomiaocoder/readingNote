// 只要是C++编译器，都内置了__cplusplus这个宏名
// 注意区别vs,g++, clang++实现不同的方式

#ifdef __cplusplus
extern "C" {
#endif
	int sum(int a, int b) // sum  .text
	{
		return a + b;
	}
#ifdef __cplusplus
}
#endif