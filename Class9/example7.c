/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Double Pointers
* Description: Use a pointer to modify another pointer's address.
* EE Application: Managing arrays of pointers (e.g., GPIO pin arrays).
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int value = 10;
    int *ptr = &value;    // Pointer to an integer
    int **dbl_ptr = &ptr; // Pointer to a pointer

    printf("Value: %d\n", **dbl_ptr); // Output: 10

    // Dynamically allocate a new integer and update ptr via dbl_ptr
    *dbl_ptr = (int*)malloc(sizeof(int));
    printf("Value: %d\n", **dbl_ptr);
    **dbl_ptr = 20; // Assign value through double pointer
    printf("New Value: %d\n", *ptr); // Output: 20

    free(ptr); // Free allocated memory
    return 0;
}