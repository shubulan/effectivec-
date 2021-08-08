## 0. 起因：对象的初始化反复无常

> 有时初始化，有时不初始化，而程序读取未初始化值时会有潜在错误

举例

1. class内默认类型的初始化情况

```
/*
initialization0.cpp
*/
#include <iostream>
using namespace std;
class Point1{
	int x, y;
};
struct Point2{
	int x, y;
};
int main() {
    Point1 p1;
	Point2 p2;
	cout << *((int *)(&p1))  << " "
	     << *((int *)((&p1) + 4)) << endl;//输出16和89，原因不知
	cout << p2.x << " "
	     << p2.y << endl; //输出不定值和0
	return 0;
}
```

2. 在c-part时，不保证初始化，而进入non-c-part时，规则又发生一些变化。

## 1. 应对方式：永远初始化对象

+ 内置类型：手动完成
+ 自定义类：构造函数

### 1.1 易错点--全面思考

#### 1.1.1 构造函数中的赋值与初始化

+ 要在构造函数中初始化，请用列表初始化方式,尤其是针对内置类型。在函数体内的"初始化"实际上是赋值。p.s.成员变量是const或者引用时，必须使用初始化列。因为他们不可以被赋值

```
在initialization1.cpp中对两种构造方式进行了对比测试，发现列表初始化比构造函数内赋值要快一些(废话)
```

+ 尽量将所有成员都使用初始化的方式列出来，即使该成员有默认构造的行为，这可能是开启潘多拉魔盒的钥匙；

```
ABEntry::ABEntry() : theName(),
                     theAddress(),
                     thePhones(),
                     numTimesConsulted(0)
{ }
```

+ 例外：类有多个构造函数，这些构造函数会重复的使用初始化列，工作重复且无聊。可以合理的遗漏某些赋值与初始化效率表现的一样好的变量，改用赋值操作，将赋值操作迁移到某个private函数，供所有构造函数调用。**<代码案例待补充>**

+ 初始化次序固定：大的次序是基类->依次相邻的子类**<多重继承的初始化顺序呢？代码待补充>**，小的次序是成员在类中被声明的次序，与初始化列里排布的顺序无关。因此要保证初始化列中的顺序与类内的顺序相同

#### 1.1.2 不同编译单元内定义non-local static对象的初始化次序

初见该句子时，很难理解。现在懂了。首先解释几个名词

1. **静态对象**：可以粗略的理解为不保存在堆、栈上的对象，包括

+ 全局变量、namespace内的变量
+ class内、函数内、文件作用域内用static标识的对象

在函数作用域内的static对象为局部静态对象，其他对象为非局部静态对象（non-local static）

2. **编译单元**：理解为单一.cpp文件，它编译产物为单一.o文件。大工程的编译是有多个.cpp文件的，生成的多个.o文件再加上库文件进行链接。

##### 问题说明

```
//两片代码只为说明，真实代码在filesystem.h、compileUnit0.cpp、compileUnit1.cpp
//真实代码测试是没有问题的，本案例过于简单，编译器还是聪明的
//A.cpp
class FileSystem {
public:
 	...
	size_t numDisks();
	...
private:
	...
}
extern FileSystem tfs;//留给别的文件使用的非局部静态对象
```

```
//B.cpp
class Directory {
public:
	Directory (parm);
	...
private:
	size_t disks;
};
Directory::Directory (parm){
	size_t disks = tfs.numDisks();
}
Directory temDir(params);//此时，该对象依赖A文件中的tfs对象，而此时tfs对象是否已被初始化并不确定
```

这种不同文件内的对象相互依赖的问题，需要有一个合适的对象初始化顺序。而在大的工程中想找到这样一个顺序是困难的，甚至是不可能的（这一般是代码设计错误导致的）。

##### 问题解决---单例模式

解决办法是让非局部静态对象改为局部的，也就是将初始化代码搬到函数内，让函数返回该对象的引用。这就是单例模式的实现手法

```
class FileSystem{
public:
	FileSystem(const string nm = "Windows", size_t nd = 5) : name(nm), numDisk(nd){}
	size_t numDisks() const { return numDisk;}
	string FSName() const { return name; }
private:
	string name;
	size_t numDisk;
};
inline FileSystem& tfs() {
	static FileSystem tfs;
	return tfs;
}
```

+ 这种函数很单纯，所以是使用inline关键字的好时机
+ 多线程下很不安全，任何一种静态对象在多线程下都不安全。如何实现多线程安全的单例模式是值得思考的
+ 一种解决多线程问题的方法是：在单线程启动是，手工调用所有函数，以避免多线性抢占的“竞速状态”
