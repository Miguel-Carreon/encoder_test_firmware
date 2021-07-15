#include <ClickEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>

#define encoderCLK 15
#define encoderDT 14

ClickEncoder *encoder; //Variable representing the rotary encoder
int16_t last, value; //Variables for current and last rotation value

void timerIsr() {
  encoder->service();
}


void setup() {
  
  Serial.begin(9600);
  encoder = new ClickEncoder(encoderDT, encoderCLK); //Encoder pinout definitions
  
  Timer1.initialize(1000); //Initialize the timer
  Timer1.attachInterrupt(timerIsr);
  last = -1;

}

void loop() {

  static unsigned long lastIteration;
  unsigned long iterationTime = millis();
  
  value += encoder->getValue();

  if (value != last){

    if (iterationTime - lastIteration > 50){
      if (last < value){
        //CW function
        Keyboard.press(KEY_DOWN_ARROW);
        Keyboard.release(KEY_DOWN_ARROW);
      }

      else {
        //CCW function
        Keyboard.press(KEY_UP_ARROW);
        Keyboard.release(KEY_UP_ARROW);
      }

      lastIteration = iterationTime;
      
    }

    last = value;
    
  }

}
