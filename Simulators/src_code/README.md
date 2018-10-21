# MiniC Compiler

## 运行环境
Linux操作系统

## 编译方法：
依赖的软件：

- cmake
- flex
- bison
- 支持c++11的编译器，部分工具的编译需要32位支持

```
$ cd /path/to/MiniCCompiler
$ cmake .
$ make
```

## 运行方法
上述编译方法会在bin目录下产生parser,Eeyore,Tigger,allc\_reg,riscv几个可执行文件，分别是MiniC前端分析模块、Eeyore模拟器、Tigger模拟器、寄存器分配模块、转riscv汇编模块。

parser、allc\_reg、riscv从标准输入读入，输出到标准输出。

Eeyore和Tigger从命令行参数指定的文件读入，输出到标准输出，加-d选项进入调试模式。

## 语法定义
[MiniC语法](doc/MiniC.tex)

[Eeyore语法](doc/Eeyore.tex)

[Tigger语法](doc/Tigger.tex)
