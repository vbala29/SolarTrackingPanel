#include <Stepper.h>
#define STEPS 2038

Stepper axesOne(STEPS, 2, 3, 4, 5);
String direction = "cw";

void setup() {
  Serial.begin(9600);   // initialize serial communication at 9600 BPS
  
  axesOne.setSpeed(60); //60 rpm
}


void loop() {

  int rightVal = analogRead(A0);
  int leftVal = analogRead(A1);
  float voltageRight = rightVal * (5.0 / 1023.0);
  float voltageLeft = leftVal * (5.0 / 1023.0);
  String debug = "Left value: " + String(voltageLeft) + "V, Right value: " + String(voltageRight) + "V";
  Serial.println(debug);


}

//
//String directionChange(String s) {
//  switch (s) {
//    case "cw":
//      return "ccw";
//    case "ccw":
//      return "cw";
//     default:
//      return "cw";
//  }
