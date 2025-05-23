/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Dynamic Memory Allocation
* Description: Create a dynamic array for variable sensor counts.
* EE Application: Handling real-time data streams.
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_sensors;
    num_sensors = 0;
    printf("Enter number of sensors: ");
    scanf("%d", &num_sensors);

    // Dynamically allocate memory for sensor readings
    float *readings = (float*)malloc(num_sensors * sizeof(float));
    if (readings == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Simulate sensor input
    for (int i = 0; i < num_sensors; i++) {
        readings[i] = i * 0.5; // Example data
        printf("Sensor %d: %.2f V\n", i+1, readings[i]);
    }
    printf("%p\n", readings);
    printf("%f\n", readings[0]);
    free(readings); // Always free dynamically allocated memory
    printf("%p\n", readings);
    readings = NULL; // Avoid dangling pointer
    printf("%p\n", readings);
    return 0;
}