/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* 
* Dynamic Memory with Error Checking
* Best Practices: Avoid leaks, check allocations, use `const`.
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Safe malloc wrapper with null check
void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if(ptr==NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int main() {
    const size_t buffer_size = 256;

    char *buffer = (char*)safe_malloc(buffer_size * sizeof(char));

    // Initialize memory
    memset(buffer, 0, buffer_size);

    // use snprintf to avoid buffer overflow
    snprintf(buffer, buffer_size, "Hello, World! %zu", buffer_size);

    printf("%s\n", buffer);
    free(buffer); // Always free memory
    buffer = NULL; // Prevent dangling pointers

    return 0;
}