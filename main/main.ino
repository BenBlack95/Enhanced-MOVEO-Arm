#include <AccelStepper.h> //accelstepper library
#include <Sharer.h>
#include <ContinuousStepper.h>

//AccelStepper Rstepper(1, 2, 38); //pulses Digital 2 (CLK), direction Digital 38 
//AccelStepper S1stepper(1, 3, 40); //pulses Digital 3 (CLK), direction Digital 40 
//AccelStepper S2stepper(1, 4, 42); //pulses Digital 4 (CLK), direction Digital 42 

//Pins
//int Analog_R_Value = 0; //this is used for the PWM value
const long interval = 100;  // ms
unsigned long prevMillis = 0;  // ms 

float leftXInput = 1;
float leftYInput = 1;

ContinuousStepper<StepperDriver> continousStepper;
//Rstepper.setAcceleration(3.0f)
void setup()
{
  // Schedule sampling interval
  //SERIAL
  Serial.begin(115200);
  //pinMode(Analog_R_pin, INPUT);

  continousStepper.begin(/*step=*/2, /*dir=*/38);
  continousStepper.setAcceleration(160.0f);
  //stepper.spin(100);

  Sharer_ShareVariable(float, leftXInput);
  Sharer_ShareVariable(float, leftYInput);
}

void loop()
{
  Sharer.run();
  //commented out for testing
  if (millis() - prevMillis >= interval) {
    //Rstepper.setSpeed(150);
    continousStepper.spin((leftXInput - 1) * -85);
    
    //S1stepper.setSpeed((leftYInput - 1) * -100);
    //S2stepper.setSpeed((leftYInput - 1) * 100);
    //Serial2.println("testing...");
  }   
  //continousStepper.spin(88);
  // Rstepper.runSpeed(); //step the motor (this will step the motor by 1 step at each loop indefinitely)
  // S1stepper.runSpeed();
  // S2stepper.runSpeed();
  continousStepper.loop();
}



