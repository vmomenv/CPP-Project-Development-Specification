## 防止头文件包含

本次将展现三种示例：
错误实例（会报错）、重复包含头文件示例但由于保护机制成功运行、正确实例
该目录下的工程文件为：重复包含头文件示例但由于保护机制成功运行，用于理解机制的运行。
本文着重讲述“重复包含头文件示例但由于保护机制成功运行”一节下的内容。

---

### 错误示范
a.h
``` c++
#include "b.h"

void functionA();
```

b.h

``` c++
#include "a.h"

void functionB();

```

main.cpp

```c++
#include "a.h"

int main() {
    functionA();
    functionB();
    return 0;
}
```

---

### 重复包含头文件示例但由于保护机制成功运行

文件结构

```
project/
│
├── a.h          // 头文件 a.h
├── b.h          // 头文件 b.h
├── c.h          // 头文件 c.h
├── a.cpp        // 源文件 a.cpp
├── b.cpp        // 源文件 b.cpp
└── main.cpp     // 主程序文件 main.cpp
```

a.h
```c++
#ifndef A_H        // 全称："if not defined A_H"（如果未定义 A_H），继续编译后续代码;后续的文件编译中，#ifndef A_H 将判断为 false，跳过整个 #ifndef 和 #endif 之间的内容,从而避免重复包含头文件内容。
#define A_H        // 定义预处理器宏 B_H

void functionA();  // 声明 functionA

#endif             //结束条件编译，配套 #ifndef,告诉编译器从这里结束 #ifndef 的作用域,任何在 #endif 之后的代码将不受 #ifndef 条件的影响

```

b.h

``` c++
#ifndef B_H
#define B_H

void functionB();

#endif 
```

main.cpp

```c++
#include "a.h"

int main() {
    functionA();
    functionB();
    return 0;
}
```
### 疑问：

#### 是否必须同时出现？
1、#ifndef 和 #endif 是必须配对出现的：
#ifndef 定义了条件开始的位置，#endif 定义了条件结束的位置。
如果没有 #endif，编译器会报错，例如：error: unterminated #ifndef.
2、#define 通常必须与 #ifndef 搭配使用：
#define B_H 是标记该文件已处理的核心步骤。如果没有它，即使有 #ifndef 和 #endif，每次编译器仍会认为头文件是未定义的，从而重复解析头文件内容。

#### 是否必须是 A_H？（为文件名的大写）
不必须是 A_H,但这是最佳实践。
可以使用任何合法的宏名，例如：
MY_HEADER_A_H
HEADER_FOR_A
GUARD_A_H