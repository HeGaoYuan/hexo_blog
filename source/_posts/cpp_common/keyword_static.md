---
title: "CPP Common: C++中static关键字"
date: 2017-10-25 19:20:43
categories:
	- cpp_common
tags:
	- C/C++
	- static
---

static是C++的一个关键字，被static关键字修饰的变量具有静态生存期，和整个程序具有相同的生存期。static关键字主要用于以下四个方面。

1. 函数内的静态变量
2. 静态对象
3. 类中的静态数据成员
4. 类中的静态函数成员

<!--more-->

## 函数内的静态变量

当静态变量在函数内部中时，它们只会被初始化一次，即使再次调用该函数，静态变量也会保持它当前的值而不会重新初始化。

这些静态变量存储在静态存储区而不是在栈中。

```cpp
void counter(){
  static int count = 0;
  cout << count++;
}
int main(){
  for(int i = 0; i < 5; i++){
    counter();
  }
}
```

输出：

```
0 1 2 3 4
```

让我们看一下同样的程序，但是没有使用静态变量，会是怎样的结果。

```cpp
void counter(){
  static int count = 0;
  cout << count++;
}
int main(){
  for(int i = 0; i < 5; i++){
    counter();
  }
}
```

输出：

```
0 0 0 0 0
```

如果我们不使用static关键字，变量count，在counter函数每次被调用的时候都会重新初始化，在每次离开counter函数的时候都会消亡。但是，如果我们使用static关键字，一旦count变量被第一次初始化，它就会在整个main函数阶段保持生存期，并且即使再次调用该函数，count变量也会保持它上一次的值，而不是被重新初始化。

如果你没有初始化一个静态变量，它们会默认被初始化为0。

## 静态对象

Static关键字对对象也有同样的作用。对象被声明为static，其会被分配在静态存储区，并且它的生存期为整个程序阶段。

静态对象像其他的对象一样，使用构造函数进行初始化。

```
class Abc{
private:
  int i;
public:
  Abc(){
    i = 0;
    cout << "constructor" << endl;
  }
  ~Abc(){
    cout << "destructor" << endl;
  }
};

void f(){
  static Abc obj;
}

int main(){
  int x = 0;
  if(x == 0){
    f();
  }
  cout << "END" << endl;
}
```

输出：

```
constructor END destructor
```

你一定在想：为什么析构函数没有在if语句的末尾被调用。那是因为obj为声明为static的了，它和程序拥有相同的生命期，因此obj的析构函数在main函数退出的时候被调用。

如果你将上面代码的static关键字去掉，会得到如下输出：

```
constructor destructor END
```

## 类中的静态数据成员

类中的静态数据成员为该类的所有对象共享，静态数据成员具有静态生存期。

类的静态数据成员不是使用构造函数进行初始化，因为它们并不依赖于对象的初始化。

此外，类的静态数据成员必须被明确的初始化，一般在类外。如果没有被初始化，链接器会报错。

```cpp

#include <iostream>

using namespace std;

class Point {     //Point类定义

public:       //外部接口

       Point(int x = 0, int y = 0) : x(x), y(y) { //构造函数

           //在构造函数中对count累加，所有对象共同维护同一个count

           count++;

       }

       Point(Point &p) {    //复制构造函数

           x = p.x;

           y = p.y;

           count++;

       }

       ~Point() {  count--; }

       int getX() { return x; }

       int getY() { return y; }

      void showCount() {           //输出静态数据成员

           cout << "  Object count = " << count << endl;

       }

private:      //私有数据成员

       int x, y;

       static int count;       //静态数据成员声明，用于记录点的个数

};

int Point::count = 0;//静态数据成员定义和初始化，使用类名限定
```

## 类的静态函数成员

类的静态函数成员是为整个类工作，而不是为某个类的对象工作。

可以通过obj.static_function()的方式访问静态函数成员，也可以通过calssName::static_function()的方式来访问静态函数成员。

类的静态函数成员和非静态函数成员的区别：

当进入函数体时，非静态函数成员知道具体是哪个对象调用了它，而静态函数成员不知道是哪个对象调用了它，因为非静态函数成员被调用的时候，会有一个隐含的this指针，这个this指针就指向当前调用非静态函数成员的对象；即使你使用obj.static_function()这种形式调用静态函数成员，它也没法知道是哪个对象调用了它。

静态函数成员不能访问普通的数据成员和函数成员，只能访问静态数据成员和静态函数成员，非要访问非静态数据的时候，需要显式的将对象（指针）传入静态函数中。