/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Pointer Pitfalls
* Description: Avoid dangling pointers and memory leaks.
* EE Application: Critical for embedded systems with limited memory.
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Dangling Pointer (points to freed memory)
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 5;
    free(ptr); 
    // ptr is now a dangling pointer. Do NOT dereference it!

    // Solution: Set pointer to NULL after freeing
    ptr = NULL;

    // Memory Leak (forgetting to free memory)
    int *leak = (int*)malloc(sizeof(int));
    *leak = 10;
    // Forgot to call free(leak) -> memory leak!
    free(leak); // Always free allocated memory

    return 0;
}