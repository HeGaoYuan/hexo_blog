---
title: "CPP Common: C/C++中struct的用法"
date: 2017-10-29 19:20:43
categories:
	- cpp_common
tags:
	- C/C++
	- struct
---

在C++中struct和class几乎没有区别，除了默认的类里面的变量或函数是public还是private的区别，到底哪个默认是public，我也懒得记了，每次写清楚就好了。所以在C++中struct就看做是class好了。但是在C中，struct准确的叫法是结构体，它准确的定义是：**结构体是一种把数据项组合在一起的数据结构。**它和C++中的struct的用法（或者说class的用法）还有有些许差别的。

再来吐槽一下C/C++，C/C++的语法真的丑陋，语法让人产生多种理解，或难以理解与记忆。从stack overflow上相关问题的点赞数都可以看出来，大家对struct这个语法很不熟，这个语法就是比较丑陋，这个锅就应该C/C++背，谁TM叫你虐我千百遍。下面就是stack overflow上的一个关于struct的问题链接。（https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c/612350#612350）

<!--more-->

#### C中strcut的用法

在C中，关键字struct引入结构声明。结构声明是由花括号内的一系列声明组成。

struct声明定义了一种数据结构。在标志结构成员表结束的右花括号之后可以跟一个变量表，就像其他基本类型的变量声明一样。

```Cpp
struct {
  int x;
  int y;
};

struct {
  int x;
  int y;
} pt1, pt2;
```

当然这样写一大堆东西比较麻烦，就有了一个叫做**结构标记**的东西，它是optional，放在struct关键字后面。**结构标记**就代表花括号内的声明，可以用它作为该声明的简写形式（K&R C的原话）。

```cpp
struct Point {
  int x;
  int y;
};
```

所以那句原话的意思就是，以后

```Cpp
struct Point p1;
```

```cpp
struct {
  int x;
  int y;
}p1;
```

就是同一个意思。

当然，你在有结构标记这个可选项的同时，也可以声明变量

```Cpp
struct Point {
  int x;
  int y;
}p1;
```

这条语句就是把结构的声明和结构变量p1的声明合在一起了。

typedef也经常和struct用在一起。

```Cpp
typedef struct Point{
  int x;
  int y;
} Point_type;
```

这条语句因为有typedef，所以它是一个为某种类型引入一个新名字。我们读法就是把typedef去掉，然后按声明变量的读法读，只是这时候“变量名”不是变量了，而是某种类型的别名。

```Cpp
struct Point{
  int x;
  int y;
} Point_type;
```

Pint_type才是“变量名”，Point是可选的**结构标记**。

以后你可以有两种方法来声明结构的变量了。一种是使用**结构标记**，一种是typedef引入的别名。

```Cpp
struct Point p1;
Point_type p2;
```

#### 什么情况下会出现混淆

当你在C中如果用下面的方式来使用struct的时候，就可能发生confusing。

情况1. 当你把上面的Point_type类型别名和Point**结构标记**写成同一个名字的时候，

情况2. 当你把结构标记和变量声明写成同一个名字的时候，

例如：

情况1.引入了别名fruit和结构标记fruit

```Cpp
typedef struct fruit{
  float weight;
  float price_per_kg;
} fruit;
```

情况2.引入了结构标记vegetable和声明了变量vegetable

```Cpp
struct vegetable{
  float weight;
  float price_per_kg;
} vegetable;
```

```cpp
struct fruit orange; //使用结构标记fruit
fruit orange; //使用类型别名fruit
struct vegetable potato; //使用结构标记vegetable
vegetable potato; // 错误！！！
```

当有了C++时，confusing进一步来了。

上面的情况2在C++中可以这样写

```Cpp
struct vegetable{
  float weight;
  float price_per_kg;
};
vegetable potato;
```

这时候vegetable就不是一个结构标记了，就是一个类型了。所以这时就可以使用类型名来声明一个对象potato了。
