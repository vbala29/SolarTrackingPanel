#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper elevateMotor(STEPS, 8, 10, 9, 11);
Stepper aziMotor(STEPS, 4, 6, 5, 7);
const double stepPerDeg = 5.6611;

int currAzimuth = 0;
int currElevation = 90;

void setup() {
  Serial.begin(9600);
}

void loop() {
  elevateMotor.setSpeed(10); // 1 rpm
  aziMotor.setSpeed(10); // 1 rpm

  if (Serial.available() > 0) {

    String incoming = Serial.readString();
    int ind1 = incoming.indexOf(',');
    double azi = incoming.substring(0, ind1).toDouble();
    int ind2 = incoming.indexOf(',', ind1 + 1);
    double ele = incoming.substring(ind1 + 1, ind2).toDouble();

    updatePosition(azi, ele);
  }
}

void updatePosition(double azimuth, double elevation) {
  int toTurnAzi = currAzimuth - azimuth;
  int toTurnElevation = currElevation - elevation;

  elevateMotor.step((int) toTurnElevation * stepPerDeg);
  aziMotor.step((int) toTurnAzi * stepPerDeg);
  //aziMotor.step(toTurnAzi * stepPerDeg);
  
  currElevation = elevation;
  currAzimuth = azimuth;
  Serial.print("Stepped elevation: "); Serial.println((int) toTurnElevation * stepPerDeg);
  Serial.print("Stepped azi: "); Serial.println((int) toTurnAzi * stepPerDeg);
  Serial.print("New Azimuth: "); Serial.print(currAzimuth); Serial.print("º, new elevation: ");
  Serial.print(currElevation); Serial.println("º");
}
