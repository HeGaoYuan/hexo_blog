---
title: "linux: IO Redirection"
date: 2017-08-24 21:27:59
categories: 
	- linux
tags:
	- linux
	- IO redirection
---

In this lesson we are going to unleash what may be the coolest feature of the command line. It’s called I/O redirection. The “I/O” stands for input/output and with this facility you can redirect the input and output of commands to and from files.

<!--more-->

### redirection standard output

 To redirect standard output to another file besides the screen, we use the “>” redirection operator followed by the name of the file. 

```shell
ls /usr/local/lib > local_lib.txt
```

When we redirect output with the “>” redirection operator, the destination file is always rewritten from the beginning. So, how can we append redirected output to a file instead of overwriting the file from the beginning? For that, we use the “>>” redirection operator, like so:

```shell
ls /usr/local/lib >> local_lib.txt
```

Using the “>>” operator will result in the output being appended to the file. If the file does not already exist, it is created just as though the “>” operator had been used.

### redirection standard error

 To redirect standard error to another file besides the screen, we use the “2>”  followed by the name of the file. 

```bash
ls /myusr/local/lib 2> ls_error_message.txt
```

### redirection standard output and error to a same file

 To redirect standard output and standard error to a same file, we use the “&>”  followed by the name of the file. 

```shell
ls /myusr/local/lib &> error_and_output.txt
```

### summarize

just remember four different output redirection "operator" 

\> , \>>, 2>, &> 

### Reference

http://billie66.github.io/TLCL/book/chap07.html