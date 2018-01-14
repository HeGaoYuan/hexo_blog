---
title: "linux: Environment Variable"
date: 2017-08-24 21:27:59
categories: 
	- linux
tags:
	- linux
	- environment variable
---

由无法启动eclipse而引起的环境变量配置文件的探索

其实这一切和linux启动的流程还很相关：

http://www.ruanyifeng.com/blog/2013/08/linux_boot_process.html

图形界面登录时后台启动的login shell是一个非交互式的！

ssh远程登录启动的login shell是一个交互式的！

/etc/profile 会去source /etc/bash.bashrc，但是如果是非交互式的，会do nothing and return

.profile会去source .bashrc，但如果是非交互式的，会do nothing and return

图形界面登录之后往往再Ctrl + Alt + T来开启一个新的终端，此时启动的shell是一个交互式的，非登录式的shell，会去load /etc/bash.bashrc 和 .bashrc两个文件

目前有四个配置文件

/etc/profile .profile

/etc/bash.bashrc .bashrc

还有/etc/environment待学习。