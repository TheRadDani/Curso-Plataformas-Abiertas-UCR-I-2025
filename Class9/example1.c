/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Description: Calculate resistance using Ohm's Law (V = I*R).
* EE Application: Fundamental for circuit analysis.
*******************************************************************/
#include <stdio.h>

int main() {
    float voltage, current, resistance;

    printf("Enter current (A): ");
    scanf("%f", &current);
    printf("Enter resistance (Ω): ");
    scanf("%f", &resistance);

    voltage = current * resistance; // Ohm's Law
    printf("Voltage = %.2f V\n", voltage);

    return 0;
}