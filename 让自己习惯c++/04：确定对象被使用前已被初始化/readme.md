## 对象的初始化反复无常

有时初始化，有时不初始化

```
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

## 读取未初始化值时会有潜在错误





在c-part时，不保证初始化，而进入non-c-part时，规则又发生一些变化。最好的应对方式：永远初始化。

+ 内置类型：手动完成
+ 自定义类：构造函数：确保每一个构造函数都都将每一个给成员初始化。

构造函数中的赋值与初始化

```

```

