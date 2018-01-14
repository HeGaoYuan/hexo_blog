---
title: "CS102: Chap4 using class in cpp"
date: 2017-10-29 08:52:03
categories:
	- Course/CS102
tags:
	- C/C++
---

第四章讲的是类

类是c++与c的主要区别，太基础与概念性的话就不说了，直接来一个列子：大家知道c语言中是没有字符串类型的，在c语言中所谓的字符串就是以字符'\0'结尾的字符数组，一个面向对象的高级语言怎么能没有这么基础的数据类型，所以C++在标准库中就提供了string类型，我们就要自己动手来实现string类型。

<!--more-->

首先，在实现一个类之前要彻底了解你要实现的类，记住一句话，设计一个类其实就是设计一种类型。我们要设计的类是字符串，字符串就是一个用来存储连续一段字符的数据结构，

第一个要实现的函数：**构造函数**

构造函数在定义这个类的某个对象的时候被调用的，想要写好构造函数，首先就要想好你的这个类的对象会以哪些方式被定义（被构造），对于一个字符串，我能想到被以下几种方式定义：

1. 默认的，不带参数的定义：

```cpp
my_string left_img_name;
```

2. 传入字符串字面值来定义：

注意：字符串字面值的类型为const char[n]

```cpp
my_string left_img_name = "/data/misc/camera/dump_data/img/frame0-left.jpg";
my_string right_img_name("/data/misc/camera/dump_data/img/frame0-left.jpg");
```

3. 重复某个字符n次来定义：

```cpp
my_string str1(6, 'a');
```

4. ​

```Cpp
class my_string{
  public:
    my_string(); //默认构造函数
    my_string();
  
  private:
    int length_;
    char *data_;
     
}；
```

```Cpp
//默认构造函数
my_string::my_string(){
  length_ = 0;
  data_ = new char[length_ + 1];
  data_[0] = '\0';
}
```

```cpp
//由c风格的字符串来构造
my_string::my_string(const char *c_str){
  length_ = strlen(c_str);
  data_ = new char[length_ + 1];
  strcpy(data_, c_str);
}
```

