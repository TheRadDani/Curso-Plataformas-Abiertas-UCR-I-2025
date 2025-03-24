#include <stdio.h>

void print_message() {
#ifdef DEBUG
    printf("This is a debug build.\n");
#else
    printf("This is a release build.\n");
#endif
}

int main() {
    print_message();
    return 0;
}
