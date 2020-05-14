# C预处理器和C库

> 预处理指令：：#define、#include、#ifdef、#else、#endif、#ifndef、#if、 #elif、#line、#error、#pragma
> 
> 关键字：_Generic、_Noreturn、_Static_assert
> 
> 函数/宏：sqrt()、atan()、atan2()、exit()、atexit()、assert()、memcpy()、 memmove()、va_start()、va_arg()、va_copy()、va_end()
> 
> C预处理器的其他功能
> 
> 通用选择表达式
> 
> 内联函数
> 
> C库概述和一些特殊用途的方便函数

C预处理器在程序执行之前查看程序（故称之为预处理器）。根据程序 中的预处理器指令，预处理器把符号缩写替换成其表示的内容。预处理器可 以包含程序所需的其他文件，可以选择让编译器查看哪些代码。预处理器并 不知道 C。基本上它的工作是把一些文本转换成另外一些文本。

--------------

## 翻译程序的第一步

在预处理之前，编译器必须对该程序进行一些翻译处理。<br>首先，编译器 把源代码中出现的字符映射到源字符集。该过程处理多字节字符和三字符序 列——字符扩展让C更加国际化<br>
第二，编译器定位每个反斜杠后面跟着换行符的实例，并删除它们。也 就是说，把下面两个物理行（physical line）：
```C
printf("That's wond\
erful!\n");
```
转换成一个逻辑行（logical line）：
```C
printf("That's wonderful\n!");
```
注意，在这种场合中，“换行符”的意思是通过按下Enter键在源代码文件 中换行所生成的字符，而不是指符号表征\n。

由于预处理表达式的长度必须是一个逻辑行，所以这一步为预处理器做 好了准备工作。一个逻辑行可以是多个物理行。

第三，编译器把文本划分成预处理记号序列、空白序列和注释序列（记号是由空格、制表符或换行符分隔的项）。这里要注意的是， 编译器将用一个空格字符替换每一条注释。因此，下面的代码：
```C
int/* 这看起来并不像一个空格*/fox;
将变成：
int fox;
```
而且，实现可以用一个空格替换所有的空白字符序列（不包括换行符）。<br>最后，程序已经准备好进入预处理阶段，预处理器查找一行中以#号 开始的预处理指令。

------------------------
## 明示常量

#define预处理器指令和其他预处理器指令一样，以#号作为一行的开 始。ANSI和后来的标准都允许#号前面有空格或制表符，而且还允许在#和 指令的其余部分之间有空格。但是旧版本的C要求指令从一行最左边开始， 而且#和指令其余部分之间不能有空格。指令可以出现在源文件的任何地 方，其定义从指令出现的地方到该文件末尾有效。我们大量使用#define指令 来定义明示常量（manifest constant）（也叫做符号常量），但是该指令还有 许多其他用途。

预处理器指令从#开始运行，到后面的第1个换行符为止。也就是说，指 令的长度仅限于一行。然而，前面提到过，在预处理开始前，编译器会把多 行物理行处理为一行逻辑行。

```C
* preproc.c -- 简单的预处理示例 */
#include <stdio.h>
#define TWO 2　　　/* 可以使用注释 */
#define OW "Consistency is the last refuge of the unimagina\
tive.- Oscar Wilde" /* 反斜杠把该定义延续到下一行 */
#define FOUR TWO*TWO
#define PX printf("X is %d.\n", x)
#define FMT　"X is %d.\n"
int main(void)
{
int x = TWO;
PX;
x = FOUR;
printf(FMT, x);
printf("%s\n", OW);
printf("TWO: OW\n");
return 0;
}
```

每行#define（逻辑行）都由3部分组成。第1部分是#define指令本身。第 2部分是选定的缩写，也称为宏。有些宏代表值（如本例），这些宏被称为 类对象宏（object-like macro）。C 语言还有类函数宏（function-like macro），稍后讨论。宏的名称中不允许有空格，而且必须遵循C变量的命 名规则：只能使用字符、数字和下划线（_）字符，而且首字符不能是数 字。第3部分（指令行的其余部分）称为替换列表或替换体（见图）。 一旦预处理器在程序中找到宏的示实例后，就会用替换体代替该宏（也有例 外，稍后解释）。从宏变成最终替换文本的过程称为宏展开（macro expansion）。注意，可以在#define行使用标准C注释。如前所述，每条注释 都会被一个空格代替。
![](image/2020-05-14-08-34-30.png)

由于编译器在编译期对所有的常量表达式（只包含 常量的表达式）求值，所以预处理器不会进行实际的乘法运算，这一过程在 编译时进行。预处理器不做计算，不对表达式求值，它只进行替换。

一般而言，预处理器发现程序中的宏后，会用宏等价的替换文本进行替 换。如果替换的字符串中还包含宏，则继续替换这些宏。唯一例外的是双引 号中的宏。因此，下面的语句：
```C
printf("TWO: OW");
```
打印的是TWO: OW，而不是打印：
2: Consistency is the last refuge of the unimaginative.- Oscar Wilde

要打印这行，应该这样写：
```C
printf("%d: %s\n", TWO, OW);
```
这行代码中，宏不在双引号内。

对于绝大部分数字常量，应该使用字符常 量。如果在算式中用字符常量代替数字，常量名能更清楚地表达该数字的含 义。如果是表示数组大小的数字，用符号常量后更容易改变数组的大小和循 环次数。如果数字是系统代码（如，EOF），用符号常量表示的代码更容易 移植（只需改变EOF的定义）。助记、易更改、可移植，这些都是符号常量 很有价值的特性。

C语言现在也支持const关键字，提供了更灵活的方法。用const可以创建 在程序运行过程中不能改变的变量，可具有文件作用域或块作用域。另一方 面，宏常量可用于指定标准数组的大小和const变量的初始值。

```C
#define LIMIT 20
const int LIM = 50;
static int data1[LIMIT];　　　 // 有效
static int data2[LIM];　　　　　// 无效
const int LIM2 = 2 * LIMIT;　　// 有效
const int LIM3 = 2 * LIM;　　　// 无效
```

这里解释一下上面代码中的“无效”注释。在C中，非自动数组的大小应 该是整型常量表达式，这意味着表示数组大小的必须是整型常量的组合（如 5）、枚举常量和sizeof表达式，不包括const声明的值（这也是C++和C的区 别之一，在C++中可以把const值作为常量表达式的一部分）。但是，有的实 现可能接受其他形式的常量表达式。例如，GCC 4.7.3不允许data2的声明， 但是Clang 4.6允许。

**记号**

从技术角度来看，可以把宏的替换体看作是记号（token）型字符串， 而不是字符型字符串。C预处理器记号是宏定义的替换体中单独的“词”。空白把这些词分开。
```C
#define FOUR 2*2
```
该宏定义有一个记号：2*2序列。但是，下面的宏定义中：
```C
#define SIX 2 * 3
```
有3个记号：2、*、3。

替换体中有多个空格时，字符型字符串和记号型字符串的处理方式不 同。考虑下面的定义：
```C
#define EIGHT 4 * 8
```
如果预处理器把该替换体解释为字符型字符串，将用4 * 8替换EIGHT。 即，额外的空格是替换体的一部分。如果预处理器把该替换体解释为记号型 字符串，则用3个的记号4 * 8（分别由单个空格分隔）来替换EIGHT。换而 言之，解释为字符型字符串，把空格视为替换体的一部分；解释为记号型字 符串，把空格视为替换体中各记号的分隔符。在实际应用中，一些C编译器 把宏替换体视为字符串而不是记号。在比这个例子更复杂的情况下，两者的区别才有实际意义。

顺带一提，C编译器处理记号的方式比预处理器复杂。由于编译器理解 C语言的规则，所以不要求代码中用空格来分隔记号。例如，C编译器可以 把2*2直接视为3个记号，因为它可以识别2是常量，*是运算符。

**重定义常量**

假设先把LIMIT定义为20，稍后在该文件中又把它定义为25。这个过程 称为重定义常量。不同的实现采用不同的重定义方案。除非新定义与旧定义 相同，否则有些实现会将其视为错误。另外一些实现允许重定义，但会给出 警告。ANSI标准采用第1种方案，只有新定义和旧定义完全相同才允许重定义。

具有相同的定义意味着替换体中的记号必须相同，且顺序也相同。因 此，下面两个定义相同：
```C
#define SIX 2 * 3
#define SIX 2 * 3
```
这两条定义都有 3 个相同的记号，额外的空格不算替换体的一部分。而 下面的定义则与上面两条宏定义不同：
```C
#define SIX 2*3
```

这条宏定义中只有一个记号，因此与前两条定义不同。如果需要重定义 宏，使用#undef 指令

如果确实需要重定义常量，使用const关键字和作用域规则更容易些。

-------------------------
## 在#define中使用参数

在#define中使用参数可以创建外形和作用与函数类似的类函数宏。带有 参数的宏看上去很像函数，因为这样的宏也使用圆括号。类函数宏定义的圆 括号中可以有一个或多个参数，随后这些参数出现在替换体中，如图。
![](image/2020-05-14-09-02-06.png)

下面是一个类函数宏的示例：
```C
#define SQUARE(X) X*X
```
在程序中可以这样用：
```C
z = SQUARE(2);
```

这看上去像函数调用，但是它的行为和函数调用完全不同。

示例：
```C
/* mac_arg.c -- 带参数的宏 */
#include <stdio.h>
#define SQUARE(X) X*X
#define PR(X)　 printf("The result is %d.\n", X)
int main(void)
{
int x = 5;
int z;
printf("x = %d\n", x);
z = SQUARE(x);
printf("Evaluating SQUARE(x): ");
PR(z);
z = SQUARE(2);
printf("Evaluating SQUARE(2): ");
PR(z);
printf("Evaluating SQUARE(x+2): ");
PR(SQUARE(x + 2));
printf("Evaluating 100/SQUARE(2): ");
PR(100 / SQUARE(2));
printf("x is %d.\n", x);
printf("Evaluating SQUARE(++x): ");
PR(SQUARE(++x));
printf("After incrementing, x is %x.\n", x);
return 0;
}
```
这里，SQUARE 是宏标识符，SQUARE(X)中的 X 是宏参数，X*X 是替 换列表。程序中出现SQUARE(X)的地方都会被X*X替换。这与前 面的示例不同，使用该宏时，既可以用X，也可以用其他符号。宏定义中的 X由宏调用中的符号代替。因此，SQUARE(2)替换为2*2，X实际上起到参数 的作用。

宏参数与函数参数不完全相同.

程序中设置x的值为 5，你可能认为SQUARE(x+2)应该是 7*7，即 49。但是，输出的结果是 17， 这不是一个平方值！导致这样结果的原因是，我们前面提到过，预处理器不 做计算、不求值，只替换字符序列。预处理器把出现x的地方都替换成x+2。 因此，x*x变成了x+2*x+2。如果x为5，那么该表达式的值为：

5+2*5+2 = 5 + 10 + 2 = 17

该例演示了函数调用和宏调用的重要区别。函数调用在程序运行时把参 数的值传递给函数。宏调用在编译之前把参数记号传递给程序。这两个不同 的过程发生在不同时期。是否可以修改宏定义让SQUARE(x+2)得36？当然 可以，要多加几个圆括号：

#define SQUARE(x) (x)*(x)

现在SQUARE(x+2)变成了(x+2)*(x+2)，在替换字符串中使用圆括号就得 到符合预期的乘法运算。

100/SQUARE(2)
将变成：
100/2*2

根据优先级规则，从左往右对表达式求值：(100/2)*2，即50*2，得 100。把SQUARE(x)定义为下面的形式可以解决这种混乱：

#define SQUARE(x) (x*x)

这样修改定义后得100/(2*2)，即100/4，得25。
要处理前面的两种情况，要这样定义：

#define SQUARE(x) ((x)*(x))

尽管如此，这样做还是无法避免程序中最后一种情况的问题。 SQUARE(++x)变成了++x*++x，递增了两次x，一次在乘法运算之前，一次 在乘法运算之后：

++x*++x = 6*7 = 42

由于标准并未对这类运算规定顺序，所以有些编译器得 7*6。而有些编 译器可能在乘法运算之前已经递增了x，所以7*7得49。在C标准中，对该表 达式求值的这种情况称为未定义行为。无论哪种情况，x的开始值都是5，虽 然从代码上看只递增了一次，但是x的最终值是7。

解决这个问题最简单的方法是，避免用++x 作为宏参数。一般而言，不 要在宏中使用递增或递减运算符。但是，++x可作为函数参数，因为编译器 会对++x求值得5后，再把5传递给函数。

**用宏参数创建字符串：#运算符**

C允许在字符串中包含宏参数。在类函数宏的替换体中，#号作为一个 预处理运算符，可以把记号转换成字符串。例如，如果x是一个宏形参，那 么#x就是转换为字符串"x"的形参名。这个过程称为字符串化 （stringizing）。

```C
/* subst.c -- 在字符串中替换 */
#include <stdio.h>
#define PSQR(x) printf("The square of " #x " is %d.\n",((x)*(x)))
int main(void)
{
int y = 5;
PSQR(y);
PSQR(2 + 4);
return 0;
}
```
调用第1个宏时，用"y"替换#x。调用第2个宏时，用"2 + 4"替换#x。 ANSI C字符串的串联特性将这些字符串与printf()语句的其他字符串组合，生 成最终的字符串。例如，第1次调用变成：
```C
printf("The square of " "y" " is %d.\n",((y)*(y)));
```
然后，字符串串联功能将这3个相邻的字符串组合成一个字符串：
```C
"The square of y is %d.\n"
```

**预处理器粘合剂：##运算符**

与#运算符类似，##运算符可用于类函数宏的替换部分。而且，##还可 用于对象宏的替换部分。##运算符把两个记号组合成一个记号。例如，可以 这样做：
```C
#define XNAME(n) x ## n
```
然后，宏XNAME(4)将展开为x4。

```C
// glue.c -- 使用##运算符
#include <stdio.h>
#define XNAME(n) x ## n
#define PRINT_XN(n) printf("x" #n " = %d\n", x ## n);
int main(void)
{
int XNAME(1) = 14;　　 // 变成 int x1 = 14;
int XNAME(2) = 20;　　// 变成 int x2 = 20;
int x3 = 30;
PRINT_XN(1);　　　　　 // 变成 printf("x1 = %d\n", x1);
PRINT_XN(2);　　　　　 // 变成 printf("x2 = %d\n", x2);
PRINT_XN(3);　　　　　 // 变成 printf("x3 = %d\n", x3);
return 0;
}
```
注意，PRINT_XN()宏用#运算符组合字符串，##运算符把记号组合为一 个新的标识符。

**变参宏：...和__VA_ARGS__**

一些函数（如 printf()）接受数量可变的参数。stdvar.h 头文件提供了工具，让用户自定义带可变参数的函数。C99/C11也对宏提 供了这样的工具。虽然标准中未使用“可变”（variadic）这个词，但是它已 成为描述这种工具的通用词（虽然，C标准的索引添加了字符串化 (stringizing)词条，但是，标准并未把固定参数的函数或宏称为固定函数和不变宏）。

通过把宏参数列表中最后的参数写成省略号（即，3个点...）来实现这 一功能。这样，预定义宏_ _VA_ARGS_ _可用在替换部分中，表明省略号代表什么。例如，下面 的定义：
```C
#define PR(...) printf(_ _VA_ARGS_ _)
```

假设稍后调用该宏：
```C
PR("Howdy");
PR("weight = %d, shipping = $%.2f\n", wt, sp);
```
对于第1次调用，_ _VA_ARGS_ _展开为1个参数："Howdy"。
对于第2次调用，_ _VA_ARGS_ _展开为3个参数："weight = %d, shipping = $%.2f\n"、wt、sp。

因此，展开后的代码是：
```C
printf("Howdy");
printf("weight = %d, shipping = $%.2f\n", wt, sp);
```

示例：
```C
// variadic.c -- 变参宏
#include <stdio.h>
#include <math.h>
#define PR(X, ...) printf("Message " #X ": " __VA_ARGS__)
int main(void)
{
double x = 48;
double y;
y = sqrt(x);
PR(1, "x = %g\n", x);
PR(2, "x = %.2f, y = %.4f\n", x, y);
return 0;
}
```
第1个宏调用，X的值是1，所以#X变成"1"。展开后成为：
```C
print("Message " "1" ": " "x = %g\n", x);
```
然后，串联4个字符，把调用简化为：
```C
print("Message 1: x = %g\n", x);
```

记住，省略号只能代替最后的宏参数：
```C
#define WRONG(X, ..., Y) #X #_ _VA_ARGS_ _ #y //不能这样做
```
----------------------------

## 宏和函数的选择

使用宏比使用普通函数复杂一些，稍有不慎会产生奇怪的副作用。一些 编译器规定宏只能定义成一行。不过，即使编译器没有这个限制，也应该这 样做。


宏和函数的选择实际上是时间和空间的权衡。宏生成内联代码，即在程 序中生成语句。如果调用20次宏，即在程序中插入20行代码。如果调用函数 20次，程序中只有一份函数语句的副本，所以节省了空间。然而另一方面， 程序的控制必须跳转至函数内，随后再返回主调程序，这显然比内联代码花 费更多的时间。


宏的一个优点是，不用担心变量类型（这是因为宏处理的是字符串，而 不是实际的值）。因此，只要能用int或float类型都可以使用SQUARE(x)宏。


C99提供了第3种可替换的方法——内联函数。

对于简单的函数，程序员通常使用宏，如下所示：
```C
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define ABS(X) ((X) < 0 ? -(X) : (X))
#define ISSIGN(X) ((X) == '+' || (X) == '-' ? 1 : 0)
```

要注意以下几点:

+ 记住宏名中不允许有空格，但是在替换字符串中可以有空格。ANSI C 允许在参数列表中使用空格
+ 用圆括号把宏的参数和整个替换体括起来。这样能确保被括起来的部分 在下面这样的表达式中正确地展开：
```C
forks = 2 * MAX(guests + 3, last);
```
+ 用大写字母表示宏函数的名称。该惯例不如用大写字母表示宏常量应用 广泛。但是，大写字母可以提醒程序员注意，宏可能产生的副作用。
+ 如果打算使用宏来加快程序的运行速度，那么首先要确定使用宏和使用 函数是否会导致较大差异。在程序中只使用一次的宏无法明显减少程序的运 行时间。在嵌套循环中使用宏更有助于提高效率。许多系统提供程序分析器 以帮助程序员压缩程序中最耗时的部分。

----------------------
## 文件包含：#include

当预处理器发现#include 指令时，会查看后面的文件名并把文件的内容 包含到当前文件中，即替换源文件中的#include指令。这相当于把被包含文 件的全部内容输入到源文件#include指令所在的位置。

#include指令有两种形 式：
```C
#include <stdio.h>　　　　 ←文件名在尖括号中
#include "mystuff.h"　　　←文件名在双引号中
```
在 UNIX 系统中，尖括号告诉预处理器在标准系统目录中查找该文件。 双引号告诉预处理器首先在当前目录中（或文件名中指定的其他目录）查找 该文件，如果未找到再查找标准系统目录
```C
#include <stdio.h>　　　　 ←查找系统目录
#include "hot.h"　　　　　 ←查找当前工作目录
#include "/usr/biff/p.h" ←查找/usr/biff目录
```

集成开发环境（IDE）也有标准路径或系统头文件的路径。许多集成开 发环境提供菜单选项，指定用尖括号时的查找路径。在 UNIX 中，使用双引 号意味着先查找本地目录，但是具体查找哪个目录取决于编译器的设定。有 些编译器会搜索源代码文件所在的目录，有些编译器则搜索当前的工作目 录，还有些搜索项目文件所在的目录

包含一个大型头文件不一定显著增加程序的大小。在大部分情况下，头 文件的内容是编译器生成最终代码时所需的信息，而不是添加到最终代码中 的材料。


**头文件示例**

假设你开发了一个存放人名的结构，还编写了一些使用该结构的函数。 可以把不同的声明放在头文件中。
```C
// names_st.h -- names_st 结构的头文件
// 常量
#include <string.h>
#define SLEN 32
// 结构声明
struct names_st
{
char first[SLEN];
char last[SLEN];
};
// 类型定义
typedef struct names_st names;
// 函数原型
void get_names(names *);
void show_names(const names *);
char * s_gets(char * st, int n);
```
该头文件包含了一些头文件中常见的内容：#define指令、结构声明、 typedef和函数原型。注意，这些内容是编译器在创建可执行代码时所需的信 息，而不是可执行代码。为简单起见，这个特殊的头文件过于简单。通常， 应该用#ifndef和#define防止多重包含头文件。

可执行代码通常在源代码文件中，而不是在头文件中。例如，下程序中有头文件中函数原型的定义。该程序包含了names_st.h头文件，所以 编译器知道names类型。
```C
// names_st.c -- 定义 names_st.h中的函数
#include <stdio.h>
#include "names_st.h"　　// 包含头文件
// 函数定义
void get_names(names * pn)
{
printf("Please enter your first name: ");
s_gets(pn->first, SLEN);
printf("Please enter your last name: ");
s_gets(pn->last, SLEN);
}
void show_names(const names * pn)
{
printf("%s %s", pn->first, pn->last);
}
char * s_gets(char * st, int n)
{
char * ret_val;
char * find;
ret_val = fgets(st, n, stdin);
if (ret_val)
{
find = strchr(st, '\n');　 // 查找换行符
if (find)　　　　　　　　　 // 如果地址不是NULL，
*find = '\0';　　　　 // 在此处放置一个空字符
else
while (getchar() != '\n')
continue;　　　// 处理输入行中的剩余字符
}
return ret_val;
}
```

```C
// useheader.c -- 使用 names_st 结构
#include <stdio.h>
#include "names_st.h"
// 记住要链接 names_st.c
int main(void)
{
names candidate;
get_names(&candidate);
printf("Let's welcome ");
show_names(&candidate);
printf(" to this program!\n");
return 0;
}
```

**使用头文件**

浏览任何一个标准头文件都可以了解头文件的基本信息。头文件中最常 用的形式如下。

明示常量——例如，stdio.h中定义的EOF、NULL和BUFSIZE（标准I/O 缓冲区大小）。

宏函数——例如，getc(stdin)通常用getchar()定义，而getc()经常用于定 义较复杂的宏，头文件ctype.h通常包含ctype系列函数的宏定义。

结构模版定义——标准I/O函数使用FILE结构，该结构中包含了文件和与文件缓冲区相关的信息。FILE结构在头文件stdio.h中。


类型定义——标准 I/O 函数使用指向 FILE 的指针作为参数。通常， stdio.h 用#define 或typedef把FILE定义为指向结构的指针。类似地，size_t和 time_t类型也定义在头文件中。

许多程序员都在程序中使用自己开发的标准头文件。如果开发一系列相 关的函数或结构，那么这种方法特别有价值。

另外，还可以使用头文件声明外部变量供其他文件共享。例如，如果已 经开发了共享某个变量的一系列函数，该变量报告某种状况（如，错误情 况），这种方法就很有效。这种情况下，可以在包含这些函数声明的源代码 文件定义一个文件作用域的外部链接变量：
```C
int status = 0;　　　　// 该变量具有文件作用域，在源代码文件
```

然后，可以在与源代码文件相关联的头文件中进行引用式声明：
```C
extern int status;　　 // 在头文件中
```
这行代码会出现在包含了该头文件的文件中，这样使用该系列函数的文 件都能使用这个变量。虽然源代码文件中包含该头文件后也包含了该声明， 但是只要声明的类型一致，在一个文件中同时使用定义式声明和引用式声明 没问题。

需要包含头文件的另一种情况是，使用具有文件作用域、内部链接和 const 限定符的变量或数组。const 防止值被意外修改，static 意味着每个包含 该头文件的文件都获得一份副本。因此，不需要在一个文件中进行定义式声 明，在其他文件中进行引用式声明。

------------------
## 其他指令

**#undef指令**

#undef指令用于“取消”已定义的#define指令。
```C
#define LIMIT 400
```
然后，下面的指令:
```C
#undef LIMIT
```
将移除上面的定义。现在就可以把LIMIT重新定义为一个新值。即使原 来没有定义LIMIT，取消LIMIT的定义仍然有效。如果想使用一个名称，又 不确定之前是否已经用过，为安全起见，可以用#undef 指令取消该名字的定 义。

**从C预处理器角度看已定义**

处理器在识别标识符时，遵循与C相同的规则：标识符可以由大写字 母、小写字母、数字和下划线字符组成，且首字符不能是数字。当预处理器 在预处理器指令中发现一个标识符时，它会把该标识符当作已定义的或未定 义的。这里的已定义表示由预处理器定义。如果标识符是同一个文件中由前 面的#define指令创建的宏名，而且没有用#undef 指令关闭，那么该标识符是 已定义的。如果标识符不是宏，假设是一个文件作用域的C变量，那么该标识符对预处理器而言就是未定义的。
```C
#define LIMIT 1000　　　　 // LIMIT是已定义的
#define GOOD　　　　　　　 // GOOD 是已定义的
#define A(X) ((-(X))*(X))　// A 是已定义的
int q;　　　　　　　　　　　// q 不是宏，因此是未定义的
#undef GOOD　　　　　　　　// GOOD 取消定义，是未定义的
```

注意，#define宏的作用域从它在文件中的声明处开始，直到用#undef指 令取消宏为止，或延伸至文件尾（以二者中先满足的条件作为宏作用域的结 束）。另外还要注意，如果宏通过头文件引入，那么#define在文件中的位置 取决于#include指令的位置。


**条件编译**

可以使用其他指令创建条件编译（conditinal compilation）。也就是说， 可以使用这些指令告诉编译器根据编译时的条件执行或忽略信息（或代码） 块。

1. #ifdef、#else和#endif指令

我们用一个简短的示例来演示条件编译的情况。考虑下面的代码：
```C
#ifdef MAVIS
#include "horse.h"// 如果已经用#define定义了 MAVIS，则执行下面的指令
#define STABLES 5
#else
#include "cow.h"　　　 //如果没有用#define定义 MAVIS，则执行下面的指令
#define STABLES 15
#endif
```
#ifdef指令说明，如果预处理器已定义了后面的标识符（MAVIS），则 执行#else或#endif指令之前的所有指令并编译所有C代码（先出现哪个指令 就执行到哪里）。如果预处理器未定义MAVIS，且有 #else指令，则执行 #else和#endif指令之间的所有代码。

#ifdef #else很像C的if else。两者的主要区别是，预处理器不识别用于标记块的花括号（{}），因此它使用#else（如果需要）和#endif（必须存在） 来标记指令块。这些指令结构可以嵌套。也可以用这些指令标记C语句块.
```C
/* ifdef.c -- 使用条件编译 */
#include <stdio.h>
#define JUST_CHECKING
#define LIMIT 4
int main(void)
{
int i;
int total = 0;
for (i = 1; i <= LIMIT; i++)
{
total += 2 * i*i + 1;
#ifdef JUST_CHECKING
printf("i=%d, running total = %d\n", i, total);
#endif
}
printf("Grand total = %d\n", total);
return 0;
}
```

可以用这种方法 在调试程序。定义JUST_CHECKING并合理使用#ifdef，编译器将执行用于 调试的程序代码，打印中间值。调试结束后，可移除JUST_CHECKING定义 并重新编译。如果以后还需要使用这些信息，重新插入定义即可。这样做省 去了再次输入额外打印语句的麻烦。#ifdef还可用于根据不同的C实现选择合 适的代码块。

2. #ifndef指令

#ifndef指令与#ifdef指令的用法类似，也可以和#else、#endif一起使用， 但是它们的逻辑相反。#ifndef指令判断后面的标识符是否是未定义的，常用 于定义之前未定义的常量。

通常，包含多个头文件时，其中的文件可能包含了相同宏定义。#ifndef 指令可以防止相同的宏被重复定义。在首次定义一个宏的头文件中用#ifndef 指令激活定义，随后在其他头文件中的定义都被忽略。

#ifndef指令通常用于防止多次包含一个文件。也就是说，应该像下面这 样设置头文件：
```C
/* things.h */
#ifndef THINGS_H_
#define THINGS_H_
/* 省略了头文件中的其他内容*/
#endif
```

假设该文件被包含了多次。当预处理器首次发现该文件被包含时， THINGS_H_是未定义的，所以定义了THINGS_H_，并接着处理该文件的其 他部分。当预处理器第2次发现该文件被包含时，THINGS_H_是已定义的， 所以预处理器跳过了该文件的其他部分。

为何要多次包含一个文件？最常见的原因是，许多被包含的文件中都包 含着其他文件，所以显式包含的文件中可能包含着已经包含的其他文件。这 有什么问题？在被包含的文件中有某些项（如，一些结构类型的声明）只能 在一个文件中出现一次。C标准头文件使用#ifndef技巧避免重复包含。但 是，这存在一个问题：如何确保待测试的标识符没有在别处定义。通常，实 现的供应商使用这些方法解决这个问题：用文件名作为标识符、使用大写字 母、用下划线字符代替文件名中的点字符、用下划线字符做前缀或后缀（可 能使用两条下划线）。例如，查看stdio.h头文件，可以发现许多类似的代 码：

但是，由于标准保留使用下划线作为前缀，所以在自 己的代码中不要这样写，避免与标准头文件中的宏发生冲突。

3. #if和#elif指令

#if指令很像C语言中的if。#if后面跟整型常量表达式，如果表达式为非 零，则表达式为真。可以在指令中使用C的关系运算符和逻辑运算符：
```C
#if SYS == 1
#include "ibm.h"
#endif
```
可以按照if else的形式使用#elif（早期的实现不支持#elif）。例如，可 以这样写
```C
#if SYS == 1
#include "ibmpc.h"
#elif SYS == 2
#include "vax.h"
#elif SYS == 3
#include "mac.h"
#else
#include "general.h"
#endif
```

较新的编译器提供另一种方法测试名称是否已定义，即用#if defined (VAX)代替#ifdef VAX。

这里，defined是一个预处理运算符，如果它的参数是用#define定义 过，则返回1；否则返回0。这种新方法的优点是，它可以和#elif一起使用。 下面用这种形式重写前面的示例：

```C
#if defined (IBMPC)
#include "ibmpc.h"
#elif defined (VAX)
#include "vax.h"
#elif defined (MAC)
#include "mac.h"
#else
#include "general.h"
#endif
```

条件编译还有一个用途是让程序更容易移植。改变文件开头部分的几个 关键的定义，即可根据不同的系统设置不同的值和包含不同的文件。

**预定义宏**

C标准规定了一些预定义宏，如表：
![](image/2020-05-14-17-53-20.png)

C99 标准提供一个名为_ _func_ _的预定义标识符，它展开为一个代表 函数名的字符串（该函数包含该标识符）。那么，_ _func_ _必须具有函数 作用域，而从本质上看宏具有文件作用域。因此，_ _func_ _是C语言的预定 义标识符，而不是预定义宏。

```C
// predef.c -- 预定义宏和预定义标识符
#include <stdio.h>
void why_me();
int main()
{
printf("The file is %s.\n", __FILE__);
printf("The date is %s.\n", __DATE__);
printf("The time is %s.\n", __TIME__);
printf("The version is %ld.\n", __STDC_VERSION__);
printf("This is line %d.\n", __LINE__);
printf("This function is %s\n", __func__);
why_me();
return 0;
}
void why_me()
{
printf("This function is %s\n", __func__);
printf("This is line %d.\n", __LINE__);
}
```

**#line和#error**

#line指令重置_ _LINE_ _和_ _FILE_ _宏报告的行号和文件名。可以这 样使用#line：
```C
#line 1000　　　　　　 // 把当前行号重置为1000
#line 10 "cool.c"　　　// 把行号重置为10，把文件名重置为cool.c
```

#error 指令让预处理器发出一条错误消息，该消息包含指令中的文本。 如果可能的话，编译过程应该中断。可以这样使用#error指令：
```C
#if _ _STDC_VERSION_ _ != 201112L
#error Not C11
#endif
```

# #pragma

在现在的编译器中，可以通过命令行参数或IDE菜单修改编译器的一些 设置。#pragma把编译器指令放入源代码中。例如，在开发C99时，标准被 称为C9X，可以使用下面的编译指示（pragma）让编译器支持C9X：

```C
#pragma c9x on
```
一般而言，编译器都有自己的编译指示集。例如，编译指示可能用于控 制分配给自动变量的内存量，或者设置错误检查的严格程度，或者启用非标 准语言特性等。

C99还提供_Pragma预处理器运算符，该运算符把字符串转换成普通的 编译指示。例如：
```C
_Pragma("nonstandardtreatmenttypeB on")
```
等价于下面的指令：
```C
#pragma nonstandardtreatmenttypeB on
```
由于该运算符不使用#符号，所以可以把它作为宏展开的一部分：
```C
#define PRAGMA(X) _Pragma(#X)
#define LIMRG(X) PRAGMA(STDC CX_LIMITED_RANGE X)
```
然后，可以使用类似下面的代码：
```C
LIMRG ( ON )
```

顺带一提，下面的定义看上去没问题，但实际上无法正常运行：
```C
#define LIMRG(X) _Pragma(STDC CX_LIMITED_RANGE #X)
```
问题在于这行代码依赖字符串的串联功能，而预处理过程完成之后才会 串联字符串。

_Pragma 运算符完成“解字符串”（destringizing）的工作，即把字符串中 的转义序列转换成它所代表的字符。因此，
```c
_Pragma("use_bool \"true \"false")
```
变成了：
```C
#pragma use_bool "true "false
```
