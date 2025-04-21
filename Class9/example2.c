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
float average(int readings[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += readings[i];
    }
    return (float)sum / size;
}

int main() {
    int sensor_readings[5] = {45, 52, 48, 60, 55}; // Example ADC values
    int size = sizeof(sensor_readings) / sizeof(sensor_readings[0]);
    float avg = average(sensor_readings, size);
    printf("Average Sensor Reading: %.2f\n", avg);
    return 0;
}