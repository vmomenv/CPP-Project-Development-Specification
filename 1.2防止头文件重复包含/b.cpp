#include "b.h"
#include <iostream>

void functionB() {
    std::cout << "Function B is called!" << std::endl;
    functionA(); // 调用 a.h 中声明、a.cpp 中定义的 functionA()
}
