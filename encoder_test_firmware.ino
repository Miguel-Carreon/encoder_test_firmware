#include <ClickEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>

// Pinout definitions //
#define encoderCLK 15
#define encoderDT 14
#define encoder2CLK A1
#define encoder2DT A0

ClickEncoder *encoder; //Variable representing the rotary encoder
ClickEncoder *encoder2; //Variable representing the seccond rotary encoder
int16_t last, value; //Variables for current and last rotation value
int16_t last2, value2; //Variables for current and last rotation value for the seccond encoder

void timerIsr() {
  encoder->service(); //Service method from the library for the encoder
  encoder2->service(); //Service method from the library for the seccond encoder
}


void setup() {
  
  Serial.begin(115200); //Increased baud rate
  
  encoder = new ClickEncoder(encoderDT, encoderCLK); //Encoder pinout definitions
  encoder2 = new ClickEncoder(encoder2DT, encoder2CLK); //Encoder2 pinout definitions
  
  Timer1.initialize(1000); //Initialize the timer
  Timer1.attachInterrupt(timerIsr); //Attaches the timer sub-routine with the Timer 1 interruption
  
  last = -1; //Stores last value of the encoder's position
  last2 = -1; //Stores last value of the seccond encoder's position

}

void loop() {

  //Debounce timing variables
  static unsigned long lastIteration; //Stores the time elapsed in the las iteration
  static unsigned long lastIteration2;
  unsigned long iterationTime = millis(); //Stores the time elapsed until the current iteration
  unsigned long iterationTime2 = millis();
  
  value += encoder->getValue();
  value2 += encoder2->getValue();

  // Debounced encoder 1 funtion (50 ms debounce) //
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

      lastIteration = iterationTime; //Store last iteration's time value
      
    }

    last = value; //Store last position
    
  }

  // Debounced encoder 2 function (50 ms debounce) //
  if (value2 != last2){

    if (iterationTime2 - lastIteration2 > 50){
      if (last2 < value2){
        //CW function
        Keyboard.press(KEY_RIGHT_ARROW);
        Keyboard.release(KEY_RIGHT_ARROW);
      }

      else {
        //CCW function
        Keyboard.press(KEY_LEFT_ARROW);
        Keyboard.release(KEY_LEFT_ARROW);
      }

      lastIteration2 = iterationTime2; //Store last iteration's time value
      
    }

    last2 = value2; //Store last position
    
  }

}
