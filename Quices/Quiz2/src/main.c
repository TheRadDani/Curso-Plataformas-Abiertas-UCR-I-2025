/**
 * @file main.c
 * @brief This file demonstrates a basic program for Doxygen documentation.
 * @author Luis
 * @date 2025-03-21
 */

 #include <stdio.h>
 #include "sum.h"
/** 
  * @brief Main function.
  * 
  * The entry point of the program that demonstrates the `add` function.
  * 
  * @return 0 on success.
  */
 int main() {
     int result = add(5, 3);
     printf("The sum is: %d\n", result);
     return 0;
 }