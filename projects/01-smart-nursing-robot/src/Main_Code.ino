#include <AFMotor.h>    // Adafruit Motor Shield Library
#include <QTRSensors.h> // Pololu QTR Sensor Library
#include <Servo.h>      // Servo Library for the medicine box

// ================================================================
//                        PIN CONFIGURATIONS
// ================================================================
#define SERVO_PIN 10      
#define SENSOR_PIN A5     
#define EMITTER_PIN 2     

// ================================================================
//                        TUNING PARAMETERS
// ================================================================
#define KP 0.06 
#define KD 2    
#define M1_minumum_speed 90  
#define M2_minumum_speed 90  
#define M1_maksimum_speed 170 
#define M2_maksimum_speed 170 

#define NUM_SENSORS 5         
#define TIMEOUT 2500          
#define DEBUG 0  

// Stop Confirmation: 60 loops (approx 1 second)
#define STOP_CONFIRMATION_COUNT 60

// ================================================================
//                        OBJECTS & VARIABLES
// ================================================================

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor buzzer(3, MOTOR12_1KHZ); // Buzzer on M3

QTRSensorsRC qtrrc((unsigned char[]) { A4,A3,A2,A1,A0} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

Servo boxServo;
int closedPosition = 90;  
int openPosition = 180;   
bool isBoxOpen = false;   
int lastSensorState = LOW; 

int lastError = 0;
int blackLineCounter = 0; 

// ================================================================
//                          SETUP
// ================================================================
void setup()
{
  Serial.begin(9600);
  
  boxServo.attach(SERVO_PIN);
  boxServo.write(closedPosition); 
  pinMode(SENSOR_PIN, INPUT);
  
  buzzer.run(RELEASE); // Ensure buzzer is off

  delay(1500); 
  manual_calibration(); 
  set_motors(0,0); 
}

// ================================================================
//                          MAIN LOOP
// ================================================================
void loop()
{
  // 1. Check Box (Always Active)
  checkBoxSystem();

  // 2. Read Sensors
  unsigned int sensors[5];
  int position = qtrrc.readLine(sensors); 

  // ========================================
  //           STABLE STOP LOGIC (BLACK LINE)
  // ========================================
  
  if (sensors[0] > 600 && sensors[1] > 600 && sensors[2] > 600 && sensors[3] > 600 && sensors[4] > 600) 
  {
      blackLineCounter++;

      // If we see Black Line for long enough -> STOP
      if (blackLineCounter > STOP_CONFIRMATION_COUNT) {
          
          set_motors(0, 0); // STOP MOTORS
          Serial.println("DESTINATION REACHED.");
          
          bool alarmActive = true; // Flag to verify if we should beep

          // Infinite loop: Robot stays here forever
          while(1) {
            set_motors(0, 0);
            checkBoxSystem(); // Keep touch sensor working
            
            // If patient opens the box, DISABLE the alarm permanently
            if (isBoxOpen) {
               alarmActive = false;
            }

            // --- SMART ALARM LOGIC ---
            // Only beep if alarm is still active AND box is currently closed
            if (alarmActive && !isBoxOpen) {
               // We use millis() to beep every 500ms without blocking the sensor
               if ((millis() / 500) % 2 == 0) {
                 buzzer.setSpeed(255);
                 buzzer.run(FORWARD); // Beep ON
               } else {
                 buzzer.run(RELEASE); // Beep OFF
               }
            } 
            else {
               // If alarm was disabled (box opened once) OR box is currently open -> SILENCE
               buzzer.run(RELEASE); 
            }
          }
      }
  }
  else 
  {
      blackLineCounter = 0;
  }
  
  // ========================================
  //            PID CONTROL
  // ========================================
  int error = position - 2000;
  int motorSpeed = KP * error + KD * (error - lastError);
  lastError = error;
  
  int leftMotorSpeed = M1_minumum_speed + motorSpeed;
  int rightMotorSpeed = M2_minumum_speed - motorSpeed;
  
  set_motors(leftMotorSpeed, rightMotorSpeed);
}

// ================================================================
//                        HELPER FUNCTIONS
// ================================================================

void checkBoxSystem() {
  int currentSensorState = digitalRead(SENSOR_PIN);

  if (lastSensorState == LOW && currentSensorState == HIGH) {
    isBoxOpen = !isBoxOpen; 

    if (isBoxOpen) {
      boxServo.write(openPosition); 
    } else {
      boxServo.write(closedPosition); 
    }
    
    delay(200); 
  }
  lastSensorState = currentSensorState;
}

void set_motors(int motor1speed, int motor2speed)
{
  if (motor1speed > M1_maksimum_speed ) motor1speed = M1_maksimum_speed;
  if (motor2speed > M2_maksimum_speed ) motor2speed = M2_maksimum_speed;
  if (motor1speed < 0) motor1speed = 0; 
  if (motor2speed < 0) motor2speed = 0; 
  
  motor1.setSpeed(motor1speed); 
  motor2.setSpeed(motor2speed); 
  motor1.run(FORWARD); 
  motor2.run(FORWARD); 
}

void manual_calibration() {
  int i;
  for (i = 0; i < 250; i++)
  {
    qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(20);
  }
}
