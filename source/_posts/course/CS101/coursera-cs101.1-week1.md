---
title: "Course: CS101.1 Week 1"
date: 2017-10-30 19:20:43
categories:
	- Course/CS101.1
tags:
	- Coursera

---

**In a nutshell: **course introduction and overview, the roles of abstraction and implementation in systems design, the road ahead.

<!--more-->

# Boolean Logic

- 布尔值：0，1

基本的布尔运算：与，或，非

x AND y, x OR y, NOT(x)

- 布尔表达式：由布尔值和布尔运算符组成的表达式

NOT(0 OR (1 AND 1)) = NOT(0 OR 1) = NOT 1 = 0

- 布尔函数：

f(x, y, z) = (x AND y) OR (NOT(x) AND z)

真值表(Truth table)和公式(Formula)是两种不同但是等价的布尔函数的表达方式

- 布尔运算性质：

Commutative Laws:

Associative Laws:

Distributive Laws:

De Morgan Laws: 

这些性质一般是为了简化布尔表达式的，例如：

NOT(NOT(x) AND NOT(x OR y)) = De Morgan Law = NOT(NOT(x) AND (NOT(x) AND NOT(y))) = Associative Law =NOT((NOT(x) AND NOT(x)) AND NOT(y)) = Indempotence = NOT(NOT(x) AND NOT(y)) = De Morgan Law = NOT(NOT(x)) OR NOT(NOT(y)) = Double Negation = x OR y

- 真值表与公式互推

从公式推出真值表很简单，只需列出所有可能input，然后带入公式计算output。

我们知道我们的unit要做什么（某种布尔函数），现在我们的任务就是将这个布尔函数用基本的运算（与、或、非）描述出来。所以，我们需要知道怎么样从真值表推理出布尔函数表达式：

|  x   |  y   |  z   |  f   |
| :--: | :--: | :--: | :--: |
|  0   |  0   |  0   |  1   |
|  0   |  0   |  1   |  0   |
|  0   |  1   |  0   |  1   |
|  0   |  1   |  1   |  0   |
|  1   |  0   |  0   |  1   |
|  1   |  0   |  1   |  0   |
|  1   |  1   |  0   |  0   |
|  1   |  1   |  1   |  0   |

方法：找到结果为1的行，然后将它们按下面的表达式写出来，然后简化

NOT(x) AND NOT(y) AND NOT(z) OR

NOT(x) AND y AND NOT(z) OR

x AND NOT(y) AND NOT(z)
= (NOT(x) AND NOT(z)) OR (x AND NOT(y) AND NOT(z))

= NOT(z) AND (NOT(x) OR NOT(y))

- 布尔逻辑中的一个重要发现

Any boolean funciton can be represented using an expression containing **AND, OR, NOT** operations.

由于：

x OR y = NOT( NOT(x) AND NOT(y) )

所以可以改为：Any boolean funciton can be represented using an expression containing **AND, NOT **operations.

Can we get less?

有另外一个神奇的运算的存在：与非运算(NAND)

x NAND y = NOT (x AND y), It gives 0 only if both its inputs are 1. 

又由于：

NOT(x) = x NAND x

x AND y = NOT(x NAND y) = (x NAND y) NAND (x NAND y)

**So, if you have a NAND gate, you can computing everything!**

# Logic Gates

逻辑门其实就是布尔逻辑运算的物理实现

最基础，最重要的逻辑门：与非门

基础的逻辑门：与门，或门，非门

组合门：有基础的逻辑门组合成的门，例如：加法门，乘法门

# HDL: hardware description language

这门课并不会让你真的拿点洛铁，二极管来搭建一个真实的电脑。所有的操作都是在仿真环境下进行的，使用硬件描述语言（HDL）来完成的。只需要有最基础的与非门就可以实现一台功能完善的电脑。如第一章介绍的，就是使用与非门来实现基础的逻辑门，进一步实现各种组合门，再进一步实现各种功能器件（如内存，ALU等），在进一步实现一个Computer。

我们以实现一个异或门为例，看看怎么使用HDL和与非门来实现这个新的门。





- HDL is a functional or declarative language. There is no procedure going on. There's no program execution going on. It is nothing more than a static description of the gate diagram.
- The order of HDL statements is insignificant
- Before using a chip part, you must know its interface. For example: Not(in=, out=), And(a=, b=, out= ), Or(a=, b=, out= )
- Connections like partName(a=a,…) and partName(…, out=out) are common 