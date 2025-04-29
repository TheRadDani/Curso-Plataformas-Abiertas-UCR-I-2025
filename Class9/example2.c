/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Functions and Arrays
* Description: Compute average of sensor readings.
* EE Application: Data smoothing in sensor arrays.
*******************************************************************/
#include <stdio.h>

// Function to compute average of an array
float average(int readings[], int size, int *sum) {
    *sum = 0;
    for (int i = 0; i < size; i++) {
        *sum += readings[i];
    }
    return (float)(*sum) / size;
}

int main() {
    int sum = 0;
    int *ptr = &sum; // Pointer to sum
    int sensor_readings[5] = {45, 52, 48, 60, 55}; // Example ADC values
    int size = sizeof(sensor_readings) / sizeof(sensor_readings[0]);
    printf("%d \n", sum);
    float avg = average(sensor_readings, size, ptr);
    printf("%d \n", sum);
    printf("Average Sensor Reading: %.2f\n", avg);
    return 0;
}