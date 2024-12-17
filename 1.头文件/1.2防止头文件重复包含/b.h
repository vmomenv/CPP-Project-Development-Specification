#ifndef B_H        // 防止重复包含
#define B_H

#include "a.h"     // b.h 依赖 a.h，可能会重复包含

void functionB();  // 声明 functionB

#endif
