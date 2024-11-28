## 防止头文件包含
本次将展现三种示例：

"错误实例（会报错）"

"重复包含头文件示例但由于保护机制成功运行"

"正确实例"

该目录下的工程文件为："重复包含头文件示例但由于保护机制成功运行"，用于理解机制的运行。

本文着重讲述“重复包含头文件示例但由于保护机制成功运行”一节的内容。

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
#ifndef B_H        // 防止重复包含
#define B_H

#include "a.h"     // b.h 依赖 a.h，可能会重复包含

void functionB();  // 声明 functionB

#endif 
```

c.h
```c++
#ifndef C_H        // 防止重复包含
#define C_H

#include "a.h"     // c.h 也依赖 a.h，可能会重复包含

void functionC();  // 声明 functionC

#endif

```

a.cpp
```c++
#include "a.h"
#include <iostream>

void functionA() {
    std::cout << "Function A is called!" << std::endl;
}
```

b.cpp
```c++
#include "b.h"
#include <iostream>

void functionB() {
    std::cout << "Function B is called!" << std::endl;
    functionA(); // 调用 a.h 中声明、a.cpp 中定义的 functionA()
}
```

c.cpp
```c++
#include "c.h"
#include <iostream>

void functionC() {
    std::cout << "Function C is called!" << std::endl;
    functionA(); // 调用 a.h 中声明、a.cpp 中定义的 functionA()
}
```
main.cpp

```c++
#include "b.h"  // 包含 b.h
#include "c.h"  // 包含 c.h，间接重复包含了 a.h

int main() {
    functionB(); // 调用 b.h 中的 functionB
    functionC(); // 调用 c.h 中的 functionC
    return 0;
}

```

### 风险
在上述代码中：

main.cpp 包含了 b.h 和 c.h。
b.h 和 c.h 都包含了 a.h。

### 结果
```
Function B is called!
Function A is called!
Function C is called!
Function A is called!
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

### 正常代码规范
简单的计算器项目，包含加法和乘法功能
文件内容
1. add.h
```c++
#ifndef ADD_H       // 防止重复包含
#define ADD_H

// 声明加法函数
int add(int a, int b);

#endif
```

2. multiply.h
```c++
#ifndef MULTIPLY_H  // 防止重复包含
#define MULTIPLY_H

// 声明乘法函数
int multiply(int a, int b);

#endif
```
3. add.cpp

```c++
#include "add.h"

int add(int a, int b) {
    return a + b;
}
```


4. multiply.cpp
```c++
#include "multiply.h"

int multiply(int a, int b) {
    return a * b;
}
```
5. main.cpp

```c++
#include <iostream>
#include "add.h"         // 包含加法模块
#include "multiply.h"    // 包含乘法模块

int main() {
    int x = 5, y = 3;

    std::cout << "Addition of " << x << " and " << y << " is: " << add(x, y) << std::endl;
    std::cout << "Multiplication of " << x << " and " << y << " is: " << multiply(x, y) << std::endl;

    return 0;
}
```
