#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_64KHZ);    // Electrodes on Motor 1
AF_DCMotor pump(2, MOTOR12_2KHZ);      // Pump on Motor 2 at 2kHz

unsigned long startTime;
bool ecDone = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Electrocoagulation...");

  motor.setSpeed(255);  // Electrodes full power
  pump.setSpeed(155);   // Pump full power

  startTime = millis(); // Record start time
}

void loop() {
  unsigned long currentTime = millis();

  if (!ecDone) {
    if (currentTime - startTime < 1800000) {  // 20 minutes = 900000 milliseconds
      // Alternate electrode direction every 20 seconds
      motor.run(FORWARD);
      Serial.println("Electrodes FORWARD");
      delay(20000);

      motor.run(BACKWARD);
      Serial.println("Electrodes BACKWARD");
      delay(20000);
    } else {
      motor.run(RELEASE);    // Stop electrodes
      ecDone = true;
      Serial.println("Electrocoagulation Done. Starting Pump...");
      pump.run(FORWARD);      // Turn on the pump permanently
    }
  } 
  else {
    // Pump keeps running, nothing else needed
    pump.run(FORWARD);
  }
}