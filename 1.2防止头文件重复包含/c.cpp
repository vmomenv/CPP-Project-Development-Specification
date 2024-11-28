#include "c.h"
#include <iostream>

void functionC() {
    std::cout << "Function C is called!" << std::endl;
    functionA(); // 调用 a.h 中声明、a.cpp 中定义的 functionA()
}
