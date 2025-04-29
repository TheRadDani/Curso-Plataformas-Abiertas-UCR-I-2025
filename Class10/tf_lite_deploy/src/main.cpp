#include <Arduino.h>
#include <TensorFlowLite.h>

#include "model.h"  // Your generated model header

void setup() {
  Serial.begin(9600);
  while (!Serial);

  

  Serial.println("Model loaded successfully!");
}

void loop() {


  // Get and print result
  Serial.print("sin(");
  Serial.print(") ≈ ");

  delay(2000);
}