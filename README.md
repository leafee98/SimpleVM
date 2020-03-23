
# Simple VM

> 软件开发实践第一次实验, 实现一个简单的虚拟机, 可以运行自己设计的字节码以及编译自己设计的语言.

各种文件后缀名以及其他特征标识尚未定义.

## 标准

语言规范见[文档标准](/doc/standard.md), 语言标准仍未定型, 仅供参考.

## 样例

见`example`目录. 目前有三个样例代码:

1. `e1`, 普通简单算术
2. `e2`, 计算两个正数的最大公因数, 结果保存在最后状态的寄存器`B`中
3. `e3`, 计算斐波那契数列的第n项(计算结果超出`int32_t`则行为未定义, 结果保存在最后状态的寄存器`B`中

## 效果

- 编译器支持编译以及反编译
- 简单虚拟机支持逐步打印指令以及寄存器和栈状态
- 在运行时, 无论如何会将程序栈和寄存器的最后状态打印出来

## 构建

使用无参数的`make`命令即可查看构建命令以及运行程序示例的命令.

## 使用

使用无参数或加入`--help`参数启动编译器和运行虚拟机即可查看帮助信息. 当前帮助信息如下:

注意反编译时会从`target`反编译出`source`. 若不加`-s`和`-t`参数, `source`和`target`仅通过先后顺序进行区分.

```
compiler [-d] [-s] <source file> [-t] <target file>

    -h, --help         display this help and exit
    -s, --source       specify the source file
    -t, --target       specify the target file
    -d, --decompile    decompile the target file to source file

runner <byte code file> [-s] [-i] [-h]

    -h, --help               show this help text.
    -s, --show-status        show the status of stack step by step
    -i, --show-instruction   show the instruction step by step.
```

## 许可

允许任何形式的学习交流, 但禁止一切形式的盈利行为, 保留代码著作权, 同时作者对使用代码产生的任何后果不负任何责任.
