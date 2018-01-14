---
title: "CPP Common: C++中直接初始化和拷贝初始化"
date: 2017-10-29 19:20:43
categories:
	- cpp_common
tags:
	- C/C++
	- initialization
---

转载自 https://sqrt-1.me/?p=241

<!--more-->

# C++的直接初始化与复制初始化

C++中的**直接初始化**指的是直接调用类的构造函数进行初始化，例如

```cpp
string a; //调用默认构造函数
string a("hello"); //调用参数为const char *类型的构造函数
string b(a); //调用拷贝构造函数
```

**复制初始化**指的是用“=”号来初始化对象，例如

```Cpp
string a="hello";
string b=a;
```

在上面的例子中，这两种写法是完全等效的，但是直接初始化和复制初始化在一些情况下还是有区别的。

根据C++的标准，直接初始化就是直接调用类的构造函数来初始化对象，例如在string a(“hello”)中，string类的string(const char *)构造函数会被调用，a被直接初始化。

然而根据标准，复制初始化应该是先调用对应的构造函数创建一个临时对象，再调用拷贝构造函数将临时对象拷贝给要创建的对象。例如在string a=”hello”中，string类的string(const char *)构造函数会被首先调用，创建一个临时对象，然后拷贝构造函数将这个临时对象复制到a。

标准还规定，为了提高效率，允许编译器跳过创建临时对象这一步，直接调用构造函数构造要创建的对象，这样就完全等价于直接初始化了。

经过我的测试，常见的编译器（gcc和VC++）都会直接跳过创建临时对象这一步，即使没有打开任何优化选项。

这样一来，也许你就会认为他们完全等同了，其实不然。下面分析两种情况。

**1、当拷贝构造函数为private时。**

虽然编译器会跳过创建临时对象这一步，但是这个类必须要能够正确的调用指定的构造函数和拷贝构造函数才能编译通过。优化是编译器采取的措施，但是程序必须使得不优化时代码也符合语法。

C++中有一些系统类型不允许复制，例如iostream和fstream这样的类。如果你想把自定义的类设置为不允许复制，把拷贝构造函数和赋值运算符声明为private即可，前面所说的系统类型也是这样做的。

我们用ifstream举例说明直接初始化和复制初始化的区别。用一个字符串来构造ifstream对象，即打开以字符串为文件名的文件输入流。

```Cpp
ifstream file("filename"); //编译通过
ifstream file="filename"; //编译出错，ifstream类的拷贝构造函数为private
```



我们来分析一下为什么第二个语句会编译出错。根据C++标准，第二个语句应该做以下两件事情：用”filename”初始化一个临时的ifstream对象，把临时的对象用拷贝构造函数复制给file。由于拷贝构造函数是private，所以没有权限调用此函数，编译出错。

注：Visual Studio的C++编译器并没有遵循标准，而是不考虑拷贝构造函数是否为private，直接编译通过。

**2、当拷贝构造函数为explicit，或者指定的构造函数为explicit时。**

C++中如果一个构造函数为explicit，那么只能显式调用这个构造函数，把这个构造函数用作“隐式类型转换”是不可以的。

我们定义一个类A，然后进行以下测试

```Cpp
class A{
  public:
  A(int a){} 
  A(const A &a){}
};
int main(){
  A a(1);
  A b=1;
  return 0;
}
```

可以编译通过。然后我们把参数为int的构造函数改为explicit，代码如下

```Cpp
class A{
  public:
  explicit A(int a){}
  A(const A &a){}
};
int main(){
  A a(1);
  A b=1;
  return 0;
}
```

“A a(1)”可以编译通过，“A b=1”这句报错，错误信息是“conversion from ‘int’ to non-scalar type ‘A’ requested”。这意味着编译器找不到int类型转换成A类型的转换函数了。如果不加explicit，参数为int的构造函数可以用于自动把int转换为A类型，但是现在不可以了。第一句的“A a(1)”有参数为int的构造函数的显式调用，而第二句“A b=1”没有显式调用。

下面我们只把拷贝构造函数改成explicit

```Cpp
class A{
  public:
  A(int a){}
  explicit A(const A &a){}};
int main(){
  A a(1);
  A b=1;
  return 0;
}
```

还是第二句编译错误。错误信息是“no matching function for call to ‘A::A(A)’”，这说明编译器找不到拷贝构造函数了。和前面第一种情况中说明的一样，编译器在把临时对象复制到b中时，需要调用A类的拷贝构造函数。现在拷贝构造函数是explicit的，只能显式的调用，不能隐含调用。第二句没有“A b(temp)”这样显式复制对象，所以编译出错。