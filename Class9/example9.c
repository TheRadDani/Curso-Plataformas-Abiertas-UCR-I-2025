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
    // calloc vs malloc
    int *p1 = calloc(4, sizeof(int));
    if (p1 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    int *p2 = calloc(1, sizeof(int[4]));
    if (p2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    int *p3 = calloc(4, sizeof *p3);
    if (p3 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int *arr = (int*)malloc(4 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }


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