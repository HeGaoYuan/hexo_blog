---
title: "CPP Common: extern “C”"
date: 2017-10-29 08:52:03
categories:
	- cpp_common
tags:
	- C/C++
	- extern "C"
---

Introduce the problem: 

In C++ source, what is the effect of extern "C"?

Stack overflow: https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c/1041880#1041880

在用C++的项目源码中，经常会不可避免的会看到下面的代码：

```cpp
#ifdef __cplusplus
extern "C" {
#endif
 
/*...*/
 
#ifdef __cplusplus
}
#endif
```

它到底有什么用呢，你知道吗？而且这样的问题经常会出现在面试or笔试中。 如果你不知道是什么意思，点开Read More，我慢慢告诉你。

<!--more-->

## **#ifdef _cplusplus/#endif _cplusplus及发散**

在介绍extern "C"之前，我们来看下#ifdef _cplusplus/#endif _cplusplus的作用。很明显#ifdef/#endif、#ifndef/#endif用于条件编译，#ifdef _cplusplus/#endif _cplusplus——表示如果定义了宏_cplusplus，就执行#ifdef/#endif之间的语句，否则就不执行。

在这里为什么需要#ifdef _cplusplus/#endif _cplusplus呢？因为C语言中不支持extern "C"声明，如果你明白extern "C"的作用就知道在C中也没有必要这样做，这就是条件编译的作用！在.c文件中包含了extern "C"时会出现编译时错误。

既然说到了条件编译，我就介绍它的一个重要应用——**避免重复包含头文件**。还记得腾讯笔试就考过这个题目，给出类似下面的代码（下面是我最近在研究的一个开源web服务器——Mongoose的头文件mongoose.h中的一段代码）：

```cpp
#ifndef MONGOOSE_HEADER_INCLUDED
#define    MONGOOSE_HEADER_INCLUDED
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
 
/*.................................
 * do something here
 *.................................
 */
 
#ifdef __cplusplus
}
#endif /* __cplusplus */
 
#endif /* MONGOOSE_HEADER_INCLUDED */
```

然后叫你说明上面宏#ifndef/#endif的作用？为了解释一个问题，我们先来看两个事实：

- 这个头文件mongoose.h可能在项目中被多个源文件包含（#include "mongoose.h"），而对于一个大型项目来说，这些冗余可能导致错误，因为一个头文件包含类定义或inline函数，在一个源文件中mongoose.h可能会被#include两次（如，a.h头文件包含了mongoose.h，而在b.c文件中#include a.h和mongoose.h）——这就会出错（在同一个源文件中一个结构体、类等被定义了两次）。
- 从逻辑观点和减少编译时间上，都要求去除这些冗余。然而让程序员去分析和去掉这些冗余，不仅枯燥且不太实际，**最重要的是有时候又需要这种冗余来保证各个模块的独立**。

为了解决这个问题，上面代码中的

```cpp
#ifndef MONGOOSE_HEADER_INCLUDED 

#define    MONGOOSE_HEADER_INCLUDED 

/……………………………/ 

#endif /* MONGOOSE_HEADER_INCLUDED */
```

就起作用了。如果定义了MONGOOSE_HEADER_INCLUDED，#ifndef/#endif之间的内容就被忽略掉。因此，编译时第一次看到mongoose.h头文件，它的内容会被读取且给定MONGOOSE_HEADER_INCLUDED一个值。之后再次看到mongoose.h头文件时，MONGOOSE_HEADER_INCLUDED就已经定义了，mongoose.h的内容就不会再次被读取了。

## **extern "C"**

首先从字面上分析extern "C"，它由两部分组成——extern关键字、"C"。下面我就从这两个方面来解读extern "C"的含义。

### **extern关键字**

在一个项目中必须保证函数、变量、枚举等在所有的源文件中保持一致，除非你指定定义为局部的。首先来一个例子：

```cpp
//file1.c:
    int x=1;
    int f(){do something here}
//file2.c:
    extern int x;
    int f();
    void g(){x=f();}
```

在file2.c中g()使用的x和f()是定义在file1.c中的。extern关键字表明file2.c中x，仅仅是一个变量的声明，其并不是在定义变量x，并未为x分配内存空间。变量x在所有模块中作为一种全局变量只能被定义一次，否则会出现连接错误。但是可以声明多次，且声明必须保证类型一致，如：

```cpp
//file1.c:
    int x=1;
    int b=1;
    extern c;
//file2.c:
    int x;// x equals to default of int type 0
    int f();
    extern double b;
    extern int c;
```

在这段代码中存在着这样的三个错误：

1. x被定义了两次
2. b两次被声明为不同的类型
3. c被声明了两次，但却没有定义

回到extern关键字，extern是C/C++语言中表明**函数**和**全局变量**作用范围（可见性）的关键字，该关键字告诉编译器，其声明的函数和变量可以在本模块或其它模块中使用。通常，在模块的头文件中对本模块提供给其它模块引用的函数和全局变量以关键字extern声明。例如，如果模块B欲引用该模块A中定义的全局变量和函数时只需包含模块A的头文件即可。这样，模块B中调用模块A中的函数时，在编译阶段，模块B虽然找不到该函数，但是并不会报错；它会在连接阶段中从模块A编译生成的目标代码中找到此函数。

与extern对应的关键字是 static，被它修饰的全局变量和函数只能在本模块中使用。因此，一个函数或变量只可能被本模块使用时，其不可能被extern “C”修饰。

### **"C"**

典型的，一个C++程序包含其它语言编写的部分代码。类似的，C++编写的代码片段可能被使用在其它语言编写的代码中。不同语言编写的代码互相调用是困难的，甚至是同一种编写的代码但不同的编译器编译的代码。例如，不同语言和同种语言的不同实现可能会在注册变量保持参数和参数在栈上的布局，这个方面不一样。

为了使它们遵守统一规则，可以使用extern指定一个编译和连接规约。例如，声明C和C++标准库函数strcyp()，并指定它应该根据C的编译和连接规约来链接：

```cpp
extern "C" char* strcpy(char*,const char*);
```

注意它与下面的声明的不同之处：

```cpp
extern char* strcpy(char*,const char*);
```

下面的这个声明仅表示在连接的时候调用strcpy()。

extern "C"指令非常有用，因为C和C++的近亲关系。**注意：extern "C"指令中的C，表示的一种编译和连接规约，而不是一种语言。C表示符合C语言的编译和连接规约的任何语言，如Fortran、assembler等。**

还有要说明的是，extern "C"指令仅指定编译和连接规约，但不影响语义。例如在函数声明中，指定了extern "C"，仍然要遵守C++的类型检测、参数转换规则。

再看下面的一个例子，为了声明一个变量而不是定义一个变量，你必须在声明时指定extern关键字，但是当你又加上了"C"，它不会改变语义，但是会改变它的编译和连接方式。

如果你有很多语言要加上extern "C"，你可以将它们放到extern "C"{ }中。

### **小结extern "C"**

通过上面两节的分析，我们知道extern "C"的真实目的是实现**类C和C++的混合编程**。在C++源文件中的语句前面加上extern "C"，表明它按照类C的编译和连接规约来编译和连接，而不是C++的编译的连接规约。这样在类C的代码中就可以调用C++的函数or变量等。（注：我在这里所说的类C，代表的是跟C语言的编译和连接方式一致的所有语言）

## **C和C++互相调用**

我们既然知道extern "C"是实现的类C和C++的混合编程。下面我们就分别介绍如何在C++中调用C的代码、C中调用C++的代码。首先要明白C和C++互相调用，你得知道它们之间的编译和连接差异，及如何利用extern "C"来实现相互调用。

### **C++的编译和连接**

C++是一个面向对象语言（虽不是纯粹的面向对象语言），它支持函数的重载，重载这个特性给我们带来了很大的便利。为了支持函数重载的这个特性，C++编译器实际上将下面这些重载函数：

```Cpp
void print(int i);
void print(char c);
void print(float f);
void print(char* s);
```

编译为：

```cpp
_print_int
_print_char
_print_float
_pirnt_string
```



这样的函数名，来唯一标识每个函数。注：不同的编译器实现可能不一样，但是都是利用这种机制。所以当连接是调用print(3)时，它会去查找_print_int(3)这样的函数。下面说个题外话，正是因为这点，重载被认为不是多态，多态是运行时动态绑定（“一种接口多种实现”），如果硬要认为重载是多态，它顶多是编译时“多态”。

C++中的变量，编译也类似，如全局变量可能编译g_xx，类变量编译为c_xx等。连接是也是按照这种机制去查找相应的变量。

### **C的编译和连接**

C语言中并没有重载和类这些特性，故并不像C++那样print(int i)，会被编译为_print_int，而是直接编译为_print等。因此如果直接在C++中调用C的函数会失败，因为连接是调用C中的print(3)时，它会去找_print_int(3)。因此extern "C"的作用就体现出来了。

### **C++中调用C的代码**

什么叫C++中调用C的代码？例如，整个项目大部分是C++代码，但其中有一些函数是C编写的库，

如用C编写了一个数学库libmath.so, 其头文件为math.h。

```C
//math.h
#ifndef MATH_H
#define MATH_H
int add(int x,int y);
long long power(int x, int n);
#endif
```

```c
//math.c
#include "math.h"

int add(int x, int y){
  return x+y;
}

long long power(int x, int n){
  long long result = 1;
  for(int i = 0; i < n; i++){
    result *= x;
  }
  return result;
}
```

```Cpp
//cpp_proj.cpp
#include <math.h>
#incluse <iostream>
using namespace std;

int main(){
  int a = add(2, 5);
  int b = power(2, 5);  
  cout << "add(2, 5) is: " << a << endl;
  cout << "power(2, 5) is: " << b << endl;
  return 0;
}
```

![屏幕快照 2017-10-29 上午9.27.22](https://daiyingjie.github.io/2017/10/29/extern-C/pictures/img0.jpg)



既然说是调用C，那么math.c肯定得用gcc来编译。用gcc编译math.c成动态库libmath.so，然后用nm来查看此库。发现_add 和 _power两个函数符号。

（nm的输出的意义，参考：http://www.cnblogs.com/itech/archive/2012/09/16/2687423.html）

下面来编译cpp_proj.cpp:

![屏幕快照 2017-10-29 上午9.31.35](https://daiyingjie.github.io/2017/10/29/extern-C/pictures/img1.jpg)

error: use of undeclared identifier 'add', 'power'

这种错误就是连接错误，找不到add, power函数的定义。我们的add是我们自己定义的，这个函数不在默认库里面，所以我们要使用-l和-L参数来找到此函数。但是还是报同样的错误。所以问题就来了，为什么链接器找不到对应的函数了？我们明明给了对应的参数。

下面我们将cpp_proj.cpp改为如下形式，然后就编译通过了！

![屏幕快照 2017-10-29 上午9.36.56](https://daiyingjie.github.io/2017/10/29/extern-C/pictures/img2.jpg)

为什么对cpp_proj.cpp加了extern "C"就可以了了？

我们将改之前，没有加extern "C"的文件命名为cpp_proj.c；改之后的，加了extern "C"的命名为cpp_proj_externC.cpp。然后将它们编译成.o文件，再链接。对编译之后的.o文件使用nm命令分析：

发现没有加extern "C"的cpp_proj.o的add和power两个函数被表示为了__Z3addii 和 \__Z5powerii；而加了extern "C"的cpp_proj_externC.o被表示为了_add 和 _power。

因为libmath.so是C语言的库，我们用nm也可以看出来，它的add和power两个函数的表示符号为_add 和 _power。所以cpp_proj_externC.cpp可以编译通过而cpp_proj.cpp无法编译通过，因为在C的库libmath.so中根本就找不到__Z3addii 和 \__Z5powerii这两个符号。

![Collage_Fotor](https://daiyingjie.github.io/2017/10/29/extern-C/pictures/img3.jpg)

![屏幕快照 2017-10-29 上午9.40.16](https://daiyingjie.github.io/2017/10/29/extern-C/pictures/img4.jpg)

**所以这就是extern C的作用，很简单，表示它后面的符号是用C的编译和链接的方法来进行。目的是为了能让C++和C混合使用**

### **C中调用C++的代码**

现在换成在C中调用C++的代码，这与在C++中调用C的代码**形式有所不同**，但是**本质都是一样**，都是为了混用，**为了能找到对应的函数或变量符号**。

形式有不同是因为：`extern "C"`在C中是语法错误。所以当在C项目中调用C++的代码，是需要对C++的头文件进行修改，即加上extern C修饰，并要重新编译C++的库。

```cpp
// cppExample.h
#ifndef CPP_EXAMPLE_H
#define CPP_EXAMPLE_H
extern "C" { int add( int x, int y ); }
#endif

// cppExample.cpp
#include "cppExample.h"
int add( int x, int y ) {
  return x + y;
}

// cExample.c
extern int add( int x, int y );
int main() {
  add( 2, 3 ); 
  return 0;
}
```



## 参考文献

http://www.cnblogs.com/skynet/archive/2010/07/10/1774964.html



