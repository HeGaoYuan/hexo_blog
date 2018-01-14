---
title: Using OpenCV to Learn CPP
date: 2017-08-25 15:43:15
categories:
	- others
tags:
	- OpenCV
---

最近想完成一个心愿，就是写一下通过学习研究OpneCV的源码来学习C++。

我们首先来研究两个最简单的类Point_和 Rect\_类的源码，然后进阶学习Mat类的源码。通过研究这些类的源码，来了解C++的一些语言特性，一来可以熟悉C++（C++需要不断练习）；二来可以学习类设计的精华，以便自己以后再设计一个类的时候应该怎么写。

<!--more-->

**我们第一个要研究的类是Point_，它是一个2维空间的Point模板类。**

```cpp
template<typename _Tp> class Point_
{
public:
  typedef _Tp value_type;
  //各种构造函数
  Point_(); //默认构造函数
  Point_(_Tp x, _Tp y); //常见的通过两个点的构造函数
  Point_(const Point_& pt); //拷贝构造函数
  Point_(const CvPoint& pt); //类型转换构造函数1
  Point_(const CvPoint2D32f& pt); //类型转换构造函数2
  Point_(const Size_<Tp>& sz);  //类型转换构造函数3
  Point_(const Vec_<Tp, 2>& v);  //类型转换构造函数4
  
  _Tp x, y; //2维空间点的两个坐标
}
```

#### 一个类最先要实现的肯定是各种各样的构造函数啦。

构造函数的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数。

1.默认的构造函数

```cpp
template<typename _Tp> inline Point_<_Tp>::Point() : x(0), y(0){}
```

2.常见的通过两个点的构造函数

```cpp
template<typename _Tp> inline Point_<_Tp>::Point(_Tp _x, _Tp _y) : x(_x), y(_y){}
```

3.拷贝构造函数

```cpp
template<typename _Tp> inline Point_<_Tp>::Point(const Point_& pt) : x(pt.x), y(pt.y){}
```

4.只有一个参数的构造函数

只有一个参数的构造函数在C++中也可以称作为**类型转换构造函数**，它可以将一个指定类型的数据（也就是这种构造函数的唯一参数类型）转换为类的对象。另一种说法：**按照默认规定，只有一个参数的构造函数也定义了一个隐式转换，将该构造函数对应数据类型转换为该类对象**。

1. 当这种**类型转换构造函数**没有声明为explicit的时候，它既可以进行显示的类型转换也可以进行隐式的类型转换。下面看看隐式类型转换的例子。

   这又和另外一个C++的概念有关，直接初始化和复制初始化，

   下面这两句代码可以看做直接初始化和复制初始化两种不同的初始化方式。但是第二句代码既可以看做是MyString对象str2的复制初始化，也可以看做是一个隐式的类型转换，即将一个C风格的字符串转化为了MyString对象。

   ```cpp
   MyString str1("hgy love dyj!");
   MyString str2 = "dyj love hgy!";
   ```

   另外的例子：

   第二句代码既可以看做复制初始化也可以看做是隐式的将int型（5的类型）转化为了MyComplex类型。还有在非初始化的时候进行的类型转换，第4句代码（没有歧义的前提下）就会隐式的先把5.5转换为一个临时的无名MyComplex类型，然后再对两个MyComplex类型进行相加。

   ```cpp
   MyComplex com1(10);
   MyComplex com2 = 5;

   MyComplex com(10, 10), sum;
   sum = com + 5.5;
   ```


2. 当这种**类型转换构造函数**声明成了explict的时候，那它只能进行显示的类型转换了，而不能进行隐式的类型转换。上面的代码：

   第一句直接初始化依然有效。

   第二句复制初始化，也可以看做隐式类型转换，编译不通过。

   第四句牵涉隐式类型转换，编译不通过。

**类型转换构造函数**可以将一个指定类型的数据转换为类的对象。但是不能反过来将一个类的对象转换为一个其他类型的数据(例如将一个Complex类对象转换成double类型数据)。C++提供**类型转换函数(type conversion function)**来解决这个问题，类型转换函数的作用是将一个类的对象转换成另一类型的数据，它是一个以operator开头的成员函数，我们到时候会介绍。

上面就是关于只有一个参数的构造函数的知识点的介绍，下面就看下相关的源码：

- 类型转换构造函数1

  ```cpp
  template<typename _Tp> inline Point_<_Tp>::Point(const CvPoint& pt) : x((_Tp)pt.x), y((_Tp)pt.y){}
  ```

- 类型转换构造函数2

  ```cpp
  template<typename _Tp> inline Point_<_Tp>::Point(const CvPoint2D32f& pt) : x(saturate_cast<_Tp>(pt.x)), y(saturate_cast<_Tp>(pt.y)){} 
  ```

- 类型转换构造函数3

  ```cpp
  template<typename _Tp> inline Point_<_Tp>::Point(const Size_<_Tp>& sz) : x(sz.width), y(sz.height){}
  ```

- 类型转换构造函数4

  ```cpp
  template<typename _Tp> inline Point_<_Tp>::Point(const Vec<_Tp, 2>& v) : x(v[0]), y(v[1]){} 
  ```

#### 然后我们来实现【类型转换构造函数】对应的【类型转换函数】

```cpp
template<typename _Tp> class Point_
{
public:
  typedef _Tp value_type;
  //类型转换构造函数
  Point_(const CvPoint& pt); //类型转换构造函数1
  Point_(const CvPoint2D32f& pt); //类型转换构造函数2
  Point_(const Size_<Tp>& sz);  //类型转换构造函数3
  Point_(const Vec_<Tp, 2>& v);  //类型转换构造函数4
  
  //类型转换函数
  operator CvPoint() const;  //类型转换函数1
  operator CvPoint2D32f() const; //类型转换函数2
  operator Vec<_Tp, 2>() const; //类型转换函数4
  
  template<typename _Tp2> operator Point_<_Tp2>() const; 
  
  _Tp x, y; //2维空间点的两个坐标
}
```

类型转换函数











```cpp

template<typename _Tp> class Rect_{
public:
  typedef _Tp value_type;
  
  //! 各种各样的构造函数
  Rect_(); //默认构造函数
  Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height); //常用的构造函数，使用4个值来进行构造，分别代表矩形左上角的坐标x、y，以及矩形的宽和高。
  Rect_(const Rect_& r); //常用的构造函数，使用一个Rect_对象来进行构造
  Rect_(const CvRect& r); //使用一个CvRect对象来进行构造(旧的OpenCV1.0中的矩形类)
  Rect_(const Point_<_Tp>& org, const Size_<_Tp>& sz);
  Rect_(const Point_<_Tp>& pt1, const Point_<_Tp>& pt2);
  
  _Tp x, y, width, height;
}
```

```cpp
template<typename _TP> inline Rect_<_Tp>::Rect_() : x(0), y(0), width(0), height(0){}

template<typename _Tp> inline Rect_<_Tp>::Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height) : x(_x), y(_y), width(_width), height(_height){}

template<typename _Tp> inline Rect_<_Tp>::Rect_(const Rect_<_Tp>& r) : x(r.x), y(r.y), width(r.width), height(r.height){}




```



