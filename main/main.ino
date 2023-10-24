#include <AccelStepper.h> //accelstepper library
AccelStepper Rstepper(1, 2, 38); //pulses Digital 2 (CLK), direction Digital 38 
AccelStepper S1stepper(1, 3, 40); //pulses Digital 10 (CLK), direction Digital 11 
AccelStepper S2stepper(1, 4, 42); //pulses Digital 10 (CLK), direction Digital 11 

//Pins
const byte Analog_R_pin = A1; //r - 'rotation'-axis readings
const byte Analog_S_pin = A2; //s - 'shoulder'-axis readings
// const byte Analog_E_pin = A2; //e - 'elbow'-axis readings
// const byte LED_pin = 3; //PWM output for LED

//Variables
int Analog_R = 0; //x-axis value
int Analog_S = 0; //y-axis value
// int Analog_R = 0; //r-axis value

int Analog_R_AVG = 0; //x-axis value average
int Analog_S_AVG = 0; //y-axis value average
// int Analog_R_AVG = 0; //r-axis value average

//int Analog_R_Value = 0; //this is used for the PWM value
const long interval = 500;  // ms
unsigned long prevMillis = 0;  // ms 

void setup()
{
  // Schedule sampling interval
  //SERIAL
  Serial.begin(9600);
  //----------------------------------------------------------------------------    
  //PINS
  pinMode(Analog_R_pin, INPUT);
  // pinMode(Analog_Y_pin, INPUT);  
  // pinMode(Analog_R_pin, INPUT); 
  // pinMode(LED_pin, OUTPUT);
  //----------------------------------------------------------------------------  
  InitialValues(); //averaging the values of the 3 analog pins (values from potmeters)
  //----------------------------------------------------------------------------  
  //Stepper parameters
  //setting up some default values for maximum speed and maximum acceleration
  Rstepper.setMaxSpeed(200); //SPEED = Steps / second  
  Rstepper.setAcceleration(100); //ACCELERATION = Steps /(second)^2    
  Rstepper.setSpeed(50);
  delay(500);
  //----------------------------------------------------------------------------
  S1stepper.setMaxSpeed(200); //SPEED = Steps / second  
  S1stepper.setAcceleration(10); //ACCELERATION = Steps /(second)^2    
  S1stepper.setSpeed(10);
  delay(500);  
  S2stepper.setMaxSpeed(200); //SPEED = Steps / second  
  S2stepper.setAcceleration(10); //ACCELERATION = Steps /(second)^2    
  S2stepper.setSpeed(10);

}

void loop()
{
  //commented out for testing
  if (millis() - prevMillis >= interval) {
   ReadAnalog();
  }   
  
  Rstepper.runSpeed(); //step the motor (this will step the motor by 1 step at each loop indefinitely)
  S1stepper.runSpeed();
  S2stepper.runSpeed();

  // Serial.println("clockwise");
  // stepper.setSpeed(100);
  // stepper.move(100);
  // stepper.runToPosition();
  // delay(500);

  // // step one revolution in the other direction:
  // Serial.println("counterclockwise");
  // stepper.move(-100);
  // stepper.
  // stepper.runToPosition();
  // delay(500);
}

void ReadAnalog()
{
  //Reading the 3 potentiometers in the joystick: x, y and r.
  Analog_R = analogRead(Analog_R_pin);  
  Analog_S = analogRead(Analog_S_pin);    
  // Analog_R = analogRead(Analog_R_pin); 
  //Serial.println(Analog_X);  

  Rstepper.setSpeed(-80); 
  S1stepper.setSpeed(1);
  S2stepper.setSpeed(-1);

  //if the value is 25 "value away" from the average (midpoint), we allow the update of the speed
  //This is a sort of a filter for the inaccuracy of the reading
  // if(abs(Analog_R-Analog_R_AVG)>25) 
  // {
  //   int setSpeed = 7*(Analog_R-Analog_R_AVG);
  //   Rstepper.setSpeed(setSpeed);  
  //   //Serial.println(setSpeed);     
  // }
  // else
  // {
  //   Rstepper.setSpeed(0);
  // }
  
  //Here we will flip the direction of 1 of the motors.  
  // if(abs(Analog_S-Analog_S_AVG)>25) 
  // {
  //   S1stepper.setSpeed(5*(Analog_S-Analog_S_AVG));  
  //   S2stepper.setSpeed(-5*(Analog_S-Analog_S_AVG));  
  // }
  // else
  // {
  //   S1stepper.setSpeed(0);
  //   S2stepper.setSpeed(0);
  // }
}

void InitialValues()
{
  //Set the values to zero before averaging
  float tempR = 0;
  float tempS = 0;
  // float tempR = 0;
  //----------------------------------------------------------------------------  
  //read the analog 50x, then calculate an average. 
  //they will be the reference values
  for(int i = 0; i<50; i++)
  {
    tempR += analogRead(Analog_R_pin);  
    delay(10); //allowing a little time between two readings
    tempS += analogRead(Analog_S_AVG);        
    delay(10);
    //  tempR += analogRead(Analog_R_pin);
    //  delay(10);
  }
  //----------------------------------------------------------------------------  
  Analog_R_AVG = tempR/50; 
  Analog_S_AVG = tempS/50;
  // Analog_Y_AVG = tempY/50; 
  // Analog_R_AVG = tempR/50; 
  //----------------------------------------------------------------------------  
  Serial.print("AVG_R (Rotation): ");
  Serial.println(Analog_R_AVG);
  Serial.print("AVG_S (Shoulder): ");
  Serial.println(Analog_S_AVG);
  // Serial.print("AVG_R: ");
  // Serial.println(Analog_R_AVG);
  Serial.println("Calibration finished");  
}