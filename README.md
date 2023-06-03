# Linked list Demo
> 手搓链表Demo
>
> Note:类没有经过完整未检查，可能存在内存泄露等BUG
>
> Update 23/05/27:destroy 函数内存泄露修复

## 如何测试

1. 编译函数main.cpp

2. 一共两种测试方式：

输入Y/y或回车，进入模拟终端测试，命令用法如下：（`help()`）

```
>>> help
List Demo Ver 1.0 by Kira MintUsage: "function(argv)" or "function(argv)" .
Only one function at a time.
The first function to run should be append().

help help():                    Display this message.
quit quit():                    Quit the program.
append([value]):                Append [value] to the list.
destroy():                      Destroy the entire list after using it.
ls printList():                 Print the entire list to the console. (You can also use "ls")
getMemberNo([value]):           Returns the value of the [value] element in the list, counting from 1.
backspace():                    Deletes the last value at the end of the list.
insert([value],[place]):        Insert [value] before the [place] element, counting from 1.
replace([value],[place]):       Change the [place] element to [value], counting from 1.
cutBetween(place1,place2):      Delete elements within [place1] and [place2], excluding [place1] and [place2].
getLength():                    Get list length (number of elements).
ifMemoryLeak():                 Used for debugging to check for memory leaks.
>>>
```
输入N/n进行单轮测试

输入L/l进行重复测试（按`Ctrl-C`退出）（一种简单的内存泄露测试方法🐶）

## 函数用法

命名空间:listsSpace

lists模板类使用说明:

0.指定数据类型：

声明时使用`lists<listType> list`，将listType改为要使用的数据类型

1.lists.void append(listType appVal):

必须要最先执行的函数，向链表末端添加一个值`appVal`,如果不执行改指令，链表所以函数无法工作也可以使用`lists.void forceInit()`来强制执行初始化

2.lists.bool destroy():

链表使用完毕必须调用该函数,以防止内存泄露

3.lists.void printList():

在终端打印整个列表

4.lists.listType getMemberNo(int place):

返回获取链表中第`place`个元素的值,从1开始计数

5.lists.void backspace():

删除链表末端最后一个值

6.lists.bool insert(listType value,int place):

在第`place`个元素前插入`value`,从1开始计数

7.lists.bool replace(listType value,int place):

将第`place`个元素更改为`value`,从1开始计数

8.lists.bool cutBetween(int place1, int place2):

将`place1`,与`place2`中的元素删去

9.lists.int getLength():

获取链表长度(元素个数)

10.list.int ifMemoryLeak():

用于Debug时检查是否内存泄漏