/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Structures and File Handling
* Description: Store and read EE experiment data from a file.
* EE Application: Data logging in lab experiments.
*******************************************************************/
#include <stdio.h>
#include <string.h>

// Structure to hold sensor data
struct SensorData {
    char sensor_name[20];
    float value;
    int timestamp;
};

int main() {
    struct SensorData data;

    // Write to file
    FILE *file = fopen("sensor_log.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    strcpy(data.sensor_name, "Thermocouple");
    data.value = 27.5;
    data.timestamp = 1626300000;
    fprintf(file, "%s %f %d\n", data.sensor_name, data.value, data.timestamp);
    fclose(file);

    strcpy(data.sensor_name, "Memristor");
    data.value = 77.5;
    data.timestamp = 1626300001;

    // Read from file
    file = fopen("sensor_log.txt", "r");
    fscanf(file, "%s %f %d", data.sensor_name, &data.value, &data.timestamp);
    printf("Sensor: %s\nValue: %.2f\nTimestamp: %d\n", 
           data.sensor_name, data.value, data.timestamp);
    fclose(file);

    return 0;
}