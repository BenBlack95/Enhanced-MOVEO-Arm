
#include <AccelStepper.h> //accelstepper library
#include <Sharer.h>
#include <ContinuousStepper.h>
#include <SPI.h>
#include <Wire.h>

//AccelStepper BaseStepper(1, 2, 38); //pulses Digital 2 (CLK), direction Digital 38 
//AccelStepper S1Stepper(1, 3, 40); //pulses Digital 3 (CLK), direction Digital 40 
//AccelStepper S2Stepper(1, 5, 42); //pulses Digital 5 (CLK), direction Digital 42 
//AccelStepper LowerStepper(1, 6, 44); //pulses Digital 6 (CLK), direction Digital 44 
//AccelStepper UpperStepper(1, 9, 46); //pulses Digital 9 (CLK), direction Digital 46 
//AccelStepper WristStepper(1, 10, 48); //pulses Digital 10 (CLK), direction Digital 48 

// const int Relay_Output1 = 4;
// const int Relay_Output2 = 7;
// const int Relay_Output3 = 8;
// const int Relay_Output4 = 12;

//Pins
//int Analog_R_Value = 0; //this is used for the PWM value
const long interval = 100;  // ms
unsigned long prevMillis = 0;  // ms 

float leftXInput = 1;
float leftYInput = 1;

ContinuousStepper<StepperDriver> BaseStepper;
ContinuousStepper<StepperDriver> S1Stepper;
ContinuousStepper<StepperDriver> S2Stepper;
//BaseStepper.setAcceleration(3.0f)

void setup() {
  // Schedule sampling interval
  //SERIAL
  Serial.begin(115200); // Port 0 - Mega Primary Serial Output
  Serial1.begin(9600);  // Port 1 - Uno R4 Serial Link For Ethernet & Wifi 
  Serial2.begin(9600);  // Port 2 - TTL to RS485 Serial Datalogging Output
  //pinMode(Analog_R_pin, INPUT);
  //pinMode(Relay_Output1, OUTPUT);
  //pinMode(Relay_Output2, OUTPUT);
  //pinMode(Relay_Output3, OUTPUT);
  //pinMode(Relay_Output4, OUTPUT);

  //continousStepper.begin(/*step=*/3, /*dir=*/40);
  BaseStepper.begin(/*step=*/2, /*dir=*/38);
  BaseStepper.setAcceleration(160.0f);
  S1Stepper.begin(/*step=*/3, /*dir=*/40);
  S1Stepper.setAcceleration(160.0f);
  S2Stepper.begin(/*step=*/4, /*dir=*/42);
  S2Stepper.setAcceleration(160.0f);
  //stepper.spin(100);

  Sharer_ShareVariable(float, leftXInput);
  Sharer_ShareVariable(float, leftYInput);

}

void loop() {

  if (Serial1.available()) {
    int ComInByte = Serial1.read();
    Serial.write(ComInByte);  // Read & Write Any Incoming Data From Uno R4
  }
  while (Serial.available()) {       
    Serial1.write(Serial.read()); // Data Output From Mega To Uno R4
    Serial2.write(Serial.read()); // Data Output To TTL-RS485 Converter
  }

  Sharer.run();
  //commented out for testing
  if (millis() - prevMillis >= interval) {
    //BaseStepper.setSpeed(150);
    BaseStepper.spin((leftXInput - 1) * -1285);
    S1Stepper.spin((leftYInput - 1) * -1285);
    S2Stepper.spin((leftYInput - 1) * 1285);
    
    //S1stepper.setSpeed((leftYInput - 1) * -100);
    //S2stepper.setSpeed((leftYInput - 1) * 100);
    //Serial2.println("testing...");
  }   
  //continousStepper.spin(88);
  // Basestepper.runSpeed(); //step the motor (this will step the motor by 1 step at each loop indefinitely)
  // S1Stepper.runSpeed();
  // S2Stepper.runSpeed();
  BaseStepper.loop();
  S1Stepper.loop();
  S2Stepper.loop();

}
