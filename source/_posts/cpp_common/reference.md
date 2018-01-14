---
title: "CPP Common: C/C++中什么是引用"
date: 2017-10-29 19:20:43
categories:
	- cpp_common
tags:
	- C/C++
	- reference
---



# 什么是引用？

引用就是一个对象的别名。

引用常常被用于按引用的方式传值：

```Cpp
void swap(int& i, int& j)
{
  int tmp = i;
  i = j;
  j = tmp;
}
int main()
{
  int x, y;
  // ...
  swap(x,y);
  // ...
}
```

这里i和j是main函数中x和y的别名。换句话说，i就是x，并不是指向x的指针，也不是x的拷贝，就是x本身。你对i进行的任何操作都会对x发生，反过来也一样。

这就是作为一个程序员你应该对引用的认识。现在，给你一种不同的视角，但是可能会让你产生混淆，那就是引用是如何实现的。