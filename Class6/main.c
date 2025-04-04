#include <stdio.h>

int main() {int temp=0;int num = 42;printf("Hello, World! The number is %d\n", num);return 0;}

/*
-O0: No optimization (default). Suitable for debugging.
-Og

-O1: Basic optimizations. Improves performance without significantly increasing compile time.

-O2: More optimizations. Enables nearly all supported optimizations.

-O3: Aggressive optimizations. Includes all -O2 optimizations plus more, like inlining functions.

-Ofast: Maximum optimization. Ignores strict standard compliance for speed.

-Os: Optimizations for reducing code size.
*/