---
title: "linux: Expansion Quote Regex"
date: 2017-09-26 20:32:04
categories: 
	- linux
tags:
	- linux
	- expansion/quote/regex
---

There are three conception in linux that may confusing. They are expansion, quote and regex.

<!--more-->

#### Expansion:

Each time you type a command line and press the enter key, bash performs several processes upon the text before it carries out your command. We have seen a couple of cases of how a simple character sequence, for example “*”, can have a lot of meaning to the shell. The process that makes this happen is called expansion. With expansion, you type something and it is expanded into something else before the shell acts upon it.

```shell
$ echo *
Desktop Documents ls-output.txt Music Pictures Public Templates Videos
```

More Expansion

pathname expansion: *

tilde character expansion: ~

arithmetic expansion: $((expression))

brace expansion: {a..z}, {1, 2, 3}, {A{1, 2}, B{3, 4}}

parameter expansion: $HOME

command substitution: $(command line), \`command line`

#### Quote:

The shell provides a mechanism called quoting to selectively suppress unwanted expansions.

```shell
$ echo The total is $100.00
The total is 00.00
```

```shell
$ echo The total is \$100.00
The total is 100.00
```

More quote:

double quotes:

The first type of quoting we will look at is double quotes. If you place text inside double quotes, all the special characters used by the shell lose their special meaning and are treated as ordinary characters. The exceptions are $, \ (backslash), and ` (back-quote). This means that word-splitting, pathname expansion, tilde expansion, and brace expansion are suppressed, but parameter expansion, arithmetic expansion, and command substitution are still carried out.

single quotes:

If we need to suppress all expansions, we use single quotes. 

escape character:

Sometimes we only want to quote a single character. To do this, we can precede a character with a backslash, which in this context is called the escape character. 

#### Regular Expression:

Simply put, regular expressions are symbolic notations used to identify patterns in text.

```shell
$ ls /usr/bin | grep zip
```

While it may not seem apparent, our grep searches have been using regular expressions all along, albeit very simple ones. The regular expression “bzip” is taken to mean that a match will occur only if the line in the file contains at least four characters and that somewhere in the line the characters “b”, “z”, “i”, and “p” are found in that order, with no other characters in between. The characters in the string “bzip” are all literal characters, in that they match themselves. In addition to literals, regular expressions may also include metacharacters that are used to specify more complex matches. Regular expression metacharacters consist of the following:

```
^ $ . [ ] { } - ? * + ( ) | \
```



> Note: As we can see, many of the regular expression metacharacters are also characters that have meaning to the shell when expansion is performed. When we pass regular expressions containing metacharacters on the command line, it is vital that they be enclosed in quotes to prevent the shell from attempting to expand them.



**Added on 2017.10.24**

In above, it described the basic function of grep command, match the specific pattern. Sometimes, we want to extract the specific pattern. For example, recently I want to extract the frame_id from a string, the string looks like "test_1536x1088\_wide_1.yuv", "test1536_1088\_wide2.yuv",…..."test1536_1088\_wide56.yuv"….., what I want to do is extract the frame_id substring.

```shell
prompt> var=test1536x1088_wide56.yuv

prompt> echo $var | grep -oE "wide.*" 

prompt> wide_56.yuv

prompt> echo $var | grep -oE "wide.*" | grep -oE [0-9]+

prompt> 56
```

Notes: -o means output the specific pattern

​             -E means extended regular expression; if you use metacharacters, you should use -E

**Remember: Expansion and Regex are different things!!!**

More Regular Expression Detail:

https://github.com/HeGaoYuan/notes_of_python_for_everyone/blob/master/using_python_to_access_web_data/week2/regular_expression.ipynb

Reference: 

https://billie66.github.io/TLCL/book/chap08.html

https://billie66.github.io/TLCL/book/chap20.html

https://github.com/HeGaoYuan/notes_of_python_for_everyone/blob/master/using_python_to_access_web_data/week2/regular_expression.ipynb