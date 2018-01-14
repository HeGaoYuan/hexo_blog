---
title: "CPP Common: C++中const关键字"
date: 2017-10-25 19:20:43
categories:
	- cpp_common
tags:
	- C/C++
	- const
---



#### The C++ 'const' Declaration: Why & How

#### C++ 与const关键字有关的声明

The 'const' system is one of the really messy features of C++.

It is simple in concept: variables declared with ‘const’ added become constants and cannot be altered by the program. However it is also used to bodge in a substitute for one of the missing features of C++ and there it gets horridly complicated and sometimes frustratingly restrictive. The following attempts to explain how 'const' is used and why it exists.

'const'的确是C++的一个很麻烦的特性。

'const'在概念上非常简单：一个添加了'const'关键字声明的变量将变为“常量”，也就是它的值不能再被程序所改变了。然而‘const'作为C++语言一个缺失特性的替代修补事物，使得它变得令人讨厌的复杂以及有时令人沮丧的局限。下面我们将来解释一下如何使用’const‘以及‘const’存在的原因。

<!--more-->

##### Simple Use of 'const'

##### 'const'关键字的简单使用

The simplest use is to declare a named constant. This was available in the ancestor of C++, C.

'const'关键字最简单的使用是声明一个常量。这个在C++语言的鼻祖C语言中也被用到。

To do this, one declares a constant as if it was a variable but add ‘const’ before it. One has to initialise it immediately in the constructor because, of course, one cannot set the value later as that would be altering it. For example,

```cpp
const int Constant1 = 96;
```

will create an integer constant, unimaginatively called ‘`Constant1`’, with the value 96.

为了声明一个常量，就像声明一个变量一样，只需要在其前面加上‘const'关键字。但是必须立即对其进行初始化，显而易见一个常量声明之后不能再被赋值，因为这会改变它的值。例如：

```cpp
const int Constant1 = 96;
```

将会创建一个叫做'Constant1'整型常量，其值为96。

Such constants are useful for parameters which are used in the program but do not need to be changed after the program is compiled. It has an advantage for programmers over the C preprocessor ‘`#define`’ command in that it is understood & used by the compiler itself, not just substituted into the program text by the preprocessor before reaching the main compiler, so error messages are much more helpful.

程序中有些参数在程序被编译之后再也没有必要改变，这样的参数将其声明为常量是有用的。对于程序员来说，使用‘const‘关键字比C语言的预处理器'#define'要好，这是因为const关键字会被编译器理解和处理，而'#define'是在编译之前做简单的文本替换，在编译时并不会被编译器检查错误。

It also works with pointers but one has to be careful where ‘`const’` is put as that determines whether the pointer or what it points to is constant. For example,

```cpp
const int * Constant2;
```

declares that `Constant2` is a variable pointer to a constant integer and

```cpp
int const * Constant3;
```

is an alternative syntax which does the same, whereas

```cpp
int * const Constant3;
```

declares that `Constant3` is constant pointer to a variable integer and

```Cpp
int const * const Constant4;
```

declares that Constant4 is constant pointer to a constant integer. Basically ‘const’ applies to whatever is on its immediate left (other than if there is nothing there in which case it applies to whatever is its immediate right).

‘const’关键字也可以用于指针，但是需要注意‘const’放置的位置决定了是指针本身还是指针所指向的对象是常量。例如：

```cpp
const int * Constant2;
```

声明了Constant2是一个指针，指向一个常量整型

```cpp
int const * Constant2;
```

这是另外一种表达方式，也声明了Constant2是一个指针，指向一个整型常量，而

```cpp
int * const Constant3;
```

声明了Constant3是一个常量指针，指向一个整型变量，而

```Cpp
int const * const Constant4;
```

声明了Constant4是一个常量指针，指向一个常量整型。

总结：一般情况下，‘const’应用于它左边的“字符”（int，*，&等），除非它左边没有字符，则应用于它右边的字符。

##### Use of 'const' in Functions Return Values

##### 在有返回值的函数中使用'const'

Of the possible combinations  of pointers and ‘`const`’, the constant pointer to a variable is useful for storage that can be changed in value but not moved in memory.

在const和指针可能的组合中，指向某个变量的常量指针对于那些值会改变但是内存位置不会改变的变量是有用的。

Even more useful is a pointer (constant or otherwise) to a ‘`const`’ value. This is useful for returning constant strings and arrays from functions which, because they are implemented as pointers, the program could otherwise try to alter and crash. Instead of a difficult to track down crash, the attempt to alter unalterable values will be detected during compilation.

更有用的是一个指向常量的指针（指针本事是不是常量无所谓）。这个指针对于从函数中返回常字符串和常数组是有用的，（字符串和数组都以指针的方式实现），程序如果试图改变它们的话就会崩溃。为了不费力追踪崩溃，试图改变不可改变的值将会在编译阶段被检查。

For example, if a function which returns a fixed ‘Some text’ string is written like

举个例子，如果一个函数返回一个固定的字符串“Some text"，像下面这样

```cpp
char *Function1(){
  return "Some text";
}
```

then the program could crash if it accidentally tried to alter the value doing

如果程序不小心试图像这样改变值，那么这个程序将会崩溃

```cpp
Function1()[1] = 'a';
```

whereas the compiler would have spotted the error if the original function had been written

然而编译器会发现这个错误，如果原来的函数用以下方式来写的话

```cpp
const char *Function1(){
  return "Some text";
}
```

because the compiler would then know that the value was unalterable. (Of course, the compiler could theoretically have worked that out anyway but C is not that clever.)

因为编译器将会知道这个值是不可改变的。

#### Where it Gets Messy - in Parameter Passing

#### 哪里会发生混乱了-在参数传递的时候

When a subroutine or function is called with parameters, variables passed as the parameters might be read from in order to transfer data into the subroutine/function, written to in order to transfer data back to the calling program or both to do both. Some languages enable one to specify this directly, such as having ‘`in:`’, ‘`out:`’ & ‘`inout:`’ parameter types, whereas in C one has to work at a lower level and specify the method for passing the variables choosing one that also allows the desired data transfer direction.

当一个子程序或者一个函数被带有参数的调用的时候，变量作为参数传递，也许会被读取来将数据转移到被调函数里，也许被写来将数据转移到调用程序，或者都有可能。一些编程语言直接指定某个，比如有像'in:', 'out:', 'inout:'这样的参数类型，然而C语言中，程序员需要以low level的方式工作，并且xxxx

举个例子，一个像这样的子程序

```cpp
void Subroutine1(int Parameter1){
  printf("%d", Parameter1);
}
```

接收以C/C++默认方式传递参数—也就是一个拷贝。因此子程序能够读取传递给它的变量的值，但是不能够改变它，因为任何子程序对其所做的改变都是对拷贝做的，当子程序结束时，这些改变会丢失。例如：

```cpp
void Subroutine2(int Parameter1){
  Parameter1 = 96;
}
```

这段程序将不会改变它调用的变量，不会将其设置为96。

在C++中给参数名字前面加一个“&”会导致，在子程序中是变量本身而不是其拷贝会被作为参数使用，因此可以从子程序中传回数据。于是

```cpp
void Subroutine3(int &Parameter1){
  Parameter1 = 96;
}
```

会将该函数调用的变量值置为96.在C++中这种以其本身传递变量而不是其一份拷贝，被称为“引用”。

这种传递变量的方式是C++对C的一个增加。为了在原始的C语言中传递可变的变量，另外一个方法被用来完成这个任务。这个方法是使用一个指向某个变量的指针来作为参数，然后改变这个指针所指向的东西。举个例子

```cpp
void Subroutine4(int *Parameter1){
  *Parameter1 = 96;
}
```

这样也是有效的，但是要求在子程序中对变量的使用都变成*Parameter1这样的方式，并且调用子程序也要变成穿传递指针的方式。这样非常的麻烦。

但是‘const’从哪里进入这个例子了？通过引用或指针的方式，而不是拷贝的方式来传递参数有第二个非常常见的好处，就是当拷贝一个变量会费许多内存或者费很多时间的时候。这多半发生在大的复合的用户定义的变量类型上（如C语言中的结构体和C++中 的类）。例如一个这样的子程序声明

```
void Subroutine4(big_structure_type &Parameter1);
```

也许会使用‘&’，因为这个子程序也许会改变传入它的变量，也许这个子程序仅仅是为了节约拷贝变量所花费的时间。如果这个函数在其他人的库中被编译（看不到源码）那么我们无法知道到底这个子程序加上‘&’符号的目的是哪一个。如果程序员希望子程序不会改变变量，那么这样做是有风险的。

为了解决这个风险，‘const’能够被用在参数列表中。例如

```cpp
void Subroutine4(big_structure_type const &Parameter1);
```

这样会导致变量不以拷贝的形式传递，而以引用的形式，并且当改变变量的值的时候，程序会停止。



理想情况下，程序员不需要明确指定变量是如何被传递的这些细节，而只需要说明变量传递的方向即可（传入还是传出），编译器会自动的去优化。但是C是很底层的语言，所以程序员需要自己来明确指定。