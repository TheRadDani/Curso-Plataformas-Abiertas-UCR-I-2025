/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Description: Calculate resistance using Ohm's Law (V = I*R).
* EE Application: Fundamental for circuit analysis.
*******************************************************************/
#include <stdio.h>
#include <float.h>

int main() {
    double voltage, current, resistance;

    float a = FLT_MAX;
    printf("a = %f\n", a);

    voltage, current, resistance = 0.0f; // Initialize variables

    printf("Enter current (A): ");
    scanf("%lf", &current);
    printf("Enter resistance (Ω): ");
    scanf("%lf", &resistance);

    voltage = current * resistance * (double)a; // Ohm's Law
    printf("Voltage = %.2lf V\n", voltage);

    return 0;
}