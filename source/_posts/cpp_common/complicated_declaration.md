---
title: "CPP Common: C/C++ 复杂的变量声明"
date: 2017-10-29 13:11:38
categories:
	- cpp_common
tags:
	- C/C++
	- 变量声明

---

​    C/C++虐我千百遍，我待C++如颖洁。

​    C/C++最让我吐槽的地方，是它复杂的变量声明，变量声明可以说应该是最最最基础的东西，一个最最最基础的东西都这么复杂，这个确实不太合理，因为当你看代码，连一个声明都要看一半天，甚至拿着笔写一写来分析，会抓狂的。OK，吐槽完毕，最后当然是选择原谅C/C++啦。

​    变量声明就是声明一个符号，及其对应的类型，类型有基本的内置类型，还有像数组这种派生类型，当然还有自己定义的各种类类型。类型就是某种数据结构吧。

​    直接举例子来讲吧，你知道下面这个声明是什么意思？

```Cpp
char * const * (*next) ();
```

​    如果你不知道是什么意思，点开Read More，我慢慢告诉你。

<!--more-->



#### ABC三步读懂变量声明法

我以`char * const * (*next)();`为例，一步一步讲解怎么读懂这个复杂的声明。

**A 不管多复杂的变量声明，首先找到变量名。先不管const, volatile等关键字。**

这个声明的变量名是next。去掉const之后，声明变成`char * * (*next)();`

**B 然后找到第一个基本内置类型，或类类型。**

然后第一个基本内置类型是char，意思就是当变量next像声明那样写在表达式中的时候，其表示一个char类型的字符。即`* *(*next)()`在表达式中表示一个char字符。

* **C 然后按照优先级的顺序反向拆解这个表达**
  - **C. 1 括号的优先级第一**
  - **C. 2 后缀操作符: 括号( )表示这是一个函数; 方括号[ ]表示这是一个数组**
  - **C. 3 前缀操作符：星号*表示“指向...的指针”。**

所以对\* \*(\*next)()这个表达进行分解：

1. `* *(*next)()`表示一个char字符，所以
2. `*(*next)()`就表示一个指针，指向char字符。
3. `(*next)()`就表示一个指针，指向一个char字符的指针。（即指针的指针）
4. `(*next)`就是一个函数，函数的参数为空，函数的返回值是一个指针的指针。（3所述）
5. `next`是一个指针，指向一个函数，这个函数的参数为空，返回值为一个指针的指针。


所以，经过ABC三步，`char * const * (*next)();`这个复杂的变量声明的意思就是：声明了一个变量叫做next，next是一个指针，指向一个函数，这个函数的参数为空，返回值为一个指针的指针。


#### 网易关于C++变量声明的笔试题目

再来说一下知乎上被大家吐槽的网易的C++笔试题目：

https://www.zhihu.com/question/65116993

a: `int * ptr[n];`

b: `int(*) ptr[n]; —>  int (*ptr)[n];`

c: `int *ptr();`

d: `int(*)ptr(); —> int(*ptr)();`

e: `int( *(  (*ptr(int, int))  ) ) (int);`

abcde分别表示什么意思？

**首先，没有(*)这种写法，所以b、d选项修改为后面的形式**

按照上面的方法来分析，这些声明中都没有const关键字，所以这一步的分析就不需要了。

* a:

A: 变量名为`ptr`

B: 基本内置类型为int

C:  1. `*ptr[n]`表示一个int型数字

2. `ptr[n]`表示一个指针，指向int型数字
3. `ptr`表示一个数组，数组的大小为n，数组中的元素为指向int型的指针。

* b:

A: 变量名为`ptr`

B: 基本内置类型为int

C: 1. `(*ptr)[n]`表示一个int型数字

2. `(*ptr)`是一个数组，数组的大小为n，数组中的元素为int型数字。
3. `ptr`是一个指针，指向数组，数组是这样的：数组的大小为n，数组中的元素为int型数字。

* c:

A: 变量名为`ptr`

B: 基本内置类型为int

C: 1. `*ptr()`表示一个int型数字

2. `ptr()`表示一个指针，指向int型数字。
3. `ptr`是一个函数，函数的参数为空，函数的返回值为一个指针，指向int型数字。

* d:

A: 变量名为`ptr`

B: 基本内置类型为int

C: 1. `(*ptr)()`表示一个int型数字

2. `(*ptr)`是一个函数，函数的参数为空，函数的返回值是int型数字。
3. `ptr`是一个指针，指向一个函数，这个函数的参数为空，函数的返回值是int型数字

* e: 

A: 变量名为`ptr`

B: 基本内置类型为int

C: 1. `( *(  (*ptr(int, int))  ) ) (int)`表示一个int型数字

2. `*(  (*ptr(int, int))  )` 是一个函数，函数接收一个int型参数，返回一个int型
3. `(*ptr(int, int))`  是一个指针，指向一个函数，这个函数接收一个int型参数，返回值为int型
4. `ptr(int, int)`是一个指针，指向另一个指针，这个指针（另一个指针）指向一个函数，这个函数接收一个int型参数，返回值为int型。
5. `ptr`是一个函数，函数的参数为两个int型，返回值是一个指针，这个指针指向另一个指针，另一个指针指向一个函数，这个函数接收一个int型参数，返回值为int型。


是不是很复杂，但是你现在有办法读懂它了，当然既然我吐槽这种写法，那么有什么办法避免这种写法了？答案是有的，typedef 和 using。

#### 用typedef来简化复杂的声明

摘要《C专家编程》里面的话来介绍typedef。

​    typedef 是一种有趣的声明形式：**它为一种类型引入新的名字**，而不是为变量分配空间。在某些方面，typedef类似于宏文本替换——它并没有引入新类型，而是为现有类型取了个新名字，但它们之间存在一个关键的区别，容我稍后解释。

​    如果现在回过头过去看看“声明是如何形成的”那一节，会发现typedef关键字可以是一个常规声明的一部分，可以出现在靠近声明开始部分的任何地方。事实上，typedef的格式与变量声明完全一样，只是多了typedef这个关键字，来向你提醒它的实质。

​    由于typedef看上去跟变量声明完全一样，其实它们读起来也是一样的。分析复杂变量声明的方法同样适用于typedef。**普通声明表示“这个名字是一个指定类型的变量”，**而**typedef关键字并不创建一个变量，而是宣称“这个名字是指定类型的同义词”。**

​    举个例子来看看typedef是如何帮助阅读复杂的声明的。

​    标准库中有一个函数，signal。它的声明如下

```cpp
void (*signal(int sig, void(*func)(int)))(int);
```

我们也可以用前面介绍的方法来分析一下，这个声明是什么意思？

* A.:变量名为signal

* B: 基本内置类型为void

* C: 

  - 1. `(*signal(int sig, void(*func)(int)))(int);`表示一个void型。
  - 2. 很明显`*signal(int sig, void(*func)(int))`是一个函数，函数的参数是一个int，返回值为void（没有返回值）。
  - 3. `signal(int sig, void(*func)(int))`是一个指针，指向一个函数，函数的参数是一个int，返回值为void。
  - 4. `signal(int, xxx)`是一个函数，函数的参数为一个int，一个xxx（待分析），返回值为一个指针，该指针指向一个函数，函数的参数是一个int，返回值为void。
  - 5. 来分析xxx：void(func)(int)
       - A. 变量名为func
       - B. 基本类型为void
       - C. 1. `(*func)(int)`表示一个void型。
         2. 很明显`*func`是一个函数，参数为一个int，返回值为空。
         3. func是一个（函数）指针，指向一个函数，一个参数为一个int，返回值为空的函数。

  连起来，这个声明声明了signal是一个函数，signal函数的参数有两个，一个是int，一个是一个函数指针，指向一个参数为int，返回值为空的函数；signal函数的返回值是一个指针，该指针指向一个函数（一个参数为int，返回值为空的函数）。

好复杂，是不是？这个时候typedef就派上用场了。

我们发现通用的部分：一个参数为int，返回值为void的函数。我们用typedef来简化。

```cpp
typedef void(*ptr_to_func)(int);
```

这个怎么读了？

首先有`typedef`关键字，所以不是一个声明，而是为一种类型引入一个新名字。我们把typedef去掉，然后“变量名”就是某种类型的新名字。

```cpp
void(*ptr_to_func)(int)
```

按照上面的分析方法：

ptr_to_func是一个（函数）指针，指向一个函数，函数的参数是int，返回值为void。

这样signal的声明就可以改写为下面的形式了：

```cpp
ptr_to_func signal(int, ptr_to_func);
```

这样一看，就知道signal是一个函数，函数的参数有两个，一个是一个int，一个是一个ptr_to_func指针，返回值是一个ptr_to_func的指针。



#### typedef 和宏文本替换的区别

还是摘要一段《C专家编程》里面的话。

typedef和宏文本替换之间存在一个关键性的区别。正确看待这个区别的方法是把typedef看成是一种彻底的“封装”类型——在声明它之后不能再往里面增加别的东西。它和宏的区别主要tti体现在两个方面

* 首先，可以用其他类型说明符对宏类型名进行扩展，但对typedef所定义的类型名却不行。如下所示：

```cpp
#define peach int
unsigned peach i;

typedef int banana;
unsigned banana i; /*错误！ 非法的！*/
```

* 其次，在连续几个变量的声明中，用typedef定义的类型能够保证声明中所有的变量均为同一种类型，而用#define定义的类型则无法保证。如下所示：

```cpp
#define int_ptr int *;
int_ptr chalk, cheese;
```

宏其实只是简单的替换，所以替换之后，第二行变为了：

```cpp
int * chalk, cheese;
```

所以其实是将chalk声明为一个指向int的指针，而cheese是一个int型。

相反，用typedef的代码，两个变量是一样的：

```cpp
typedef char * char_ptr;
char_ptr Bentley, Rolls_Royce;
```

Bentley和Rolls_Royce的类型都是指向char的指针。