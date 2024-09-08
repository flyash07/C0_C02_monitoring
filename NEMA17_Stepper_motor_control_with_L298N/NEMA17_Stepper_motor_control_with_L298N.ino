// Include the Arduino Stepper Library
#include <Stepper.h>
 
// Define Constants
 
// Number of steps per output rotation
const int STEPS_PER_REV = 200;

// Initialize Stepper Motor
// Pins connected to L298N Motor Driver In1, In2, In3, In4 
Stepper stepper_NEMA17(STEPS_PER_REV, 3, 5, 6, 9);

void setup() {
  // Set a fixed motor speed to 20% of maximum speed (assuming max speed is 100 RPM)
  int motorSpeed = 20; // Set speed to 20 RPM (20% of 100 RPM max)
  stepper_NEMA17.setSpeed(motorSpeed);
  i=0;
  
}

void loop() {
  // Rotate the motor continuously at the set speed:
  for(int i = 0; i < 20; i++)
    r1();
  for(int i = 0; i < 20; i++)
    r2();
 
}


void r1(){
  stepper_NEMA17.step(STEPS_PER_REV / 10);
  
}

void r2(){
 stepper_NEMA17.step(-STEPS_PER_REV / 10); 
}
