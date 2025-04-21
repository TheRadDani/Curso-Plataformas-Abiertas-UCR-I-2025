/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Characters and Strings
* Description: Manipulate characters and strings using pointers.
* EE Application: Parsing sensor data (e.g., UART serial communication).
*******************************************************************/
#include <stdio.h>
#include <string.h> // For string functions

int main() {
    // Character (ASCII value)
    char c = 'A';
    printf("Character: %c (ASCII: %d)\n", c, c); // Output: A (65)

    // Strings are arrays of characters ending with '\0'
    char name[] = "Purdue"; // Automatically null-terminated
    char *ptr = name;       // Pointer to first character

    // Print using pointer arithmetic
    while (*ptr != '\0') {
        printf("%c ", *ptr);
        ptr++; // Move to next character
    }
    printf("\n"); // Output: P u r d u e

    // String functions
    char buffer[20];
    strcpy(buffer, "EE ");   // Copy "EE " into buffer
    strcat(buffer, "2024");  // Append "2024" to buffer
    printf("%s\n", buffer);  // Output: EE 2024

    return 0;
}