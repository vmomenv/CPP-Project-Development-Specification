#ifndef C_H        // 防止重复包含
#define C_H

#include "a.h"     // c.h 也依赖 a.h，可能会重复包含

void functionC();  // 声明 functionC

#endif
