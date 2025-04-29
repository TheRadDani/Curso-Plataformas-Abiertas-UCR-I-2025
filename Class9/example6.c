/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* 
* Pass-by-Value vs. Pass-by-Reference (Pointers)
* Description: Modify variables inside functions using pointers.
* EE Application: Used to update hardware register values in drivers.
*******************************************************************/
#include <stdio.h>

// Pass-by-Value (original variables are NOT modified)
void increment_by_value(int x) {
    x++; // Only modifies the local copy
    x *= 100; // Local copy modified
}

// Pass-by-Reference (original variables ARE modified)
void increment_by_reference(int *x) {
    (*x)++; // Dereference pointer to modify original value
    (*x) *= 100;
}

int main() {
    int sensor_reading = 5;

    increment_by_value(sensor_reading);
    printf("After pass-by-value: %d\n", sensor_reading); // Output: 5

    increment_by_reference(&sensor_reading);
    printf("After pass-by-reference: %d\n", sensor_reading); // Output: 600

    return 0;
}