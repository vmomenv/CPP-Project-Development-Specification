#include "b.h"  // 包含 b.h
#include "c.h"  // 包含 c.h，间接重复包含了 a.h

int main() {
    functionB(); // 调用 b.h 中的 functionB
    functionC(); // 调用 c.h 中的 functionC
    return 0;
}
