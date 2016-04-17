
const int LatchPin = 2;  
const int ClockPin = 3;  
const int DataPin1 = 5;   
const int DataPin2 = 6;
// Controller Buttons
#define UP          8     // 00001000
#define DOWN        4     // 00000100
#define LEFT        2     // 00000010
#define RIGHT       1     // 00000001

#define latchHigh digitalWrite(LatchPin, HIGH)
#define latchLow digitalWrite(LatchPin, LOW)
#define clockHigh digitalWrite(ClockPin, HIGH)
#define clockLow digitalWrite(ClockPin, LOW)
#define wait delayMicroseconds(6)
#define read1 digitalRead(DataPin1)
#define read2 digitalRead(DataPin2)
// Current Controller Data
byte controllerData1 = 0;
byte controllerData2 = 0;

// Joystick State
JoyState_t JoySt;


// Setup Controller
void setup() {
  JoySt.XAxis = 127;
  JoySt.YAxis = 255;
  JoySt.Buttons = 0;

  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  //Set inputs to pullup to stop noise if
  //the controller is unpluged
  pinMode(DataPin1, INPUT_PULLUP);
  pinMode(DataPin2, INPUT_PULLUP);
}
void ControllerRead() {
  //http://www.mit.edu/~tarvizo/nes-controller.html
  //save button states in controllers
  latchHigh;
  wait;
  wait;
  latchLow;
  wait;
  //save state of first button on controller
  controllerData1 = read1;
  controllerData2 = read2;

  for (int i = 0; i < 7; i++) { //save states on next 7 buttons
    clockHigh;
    wait;
    //shift bits left for incoming bit
    controllerData1 = controllerData1 << 1;
    controllerData1 += read1;
    controllerData2 = controllerData2 << 1;
    controllerData2 += read2;
    wait;
    clockLow;

  }
  //Invert bits, as controller reports +5v for unpressed button
  controllerData1 = ~controllerData1;
  controllerData2 = ~controllerData2;

}

void loop() {
  ControllerRead(); // save button states of both controllers

  if (controllerData1 & UP)
    JoySt.YAxis = 0;
  else if (controllerData1 & DOWN)
    JoySt.YAxis = 255;
  else //if neither up or down are pressed, center Y axis
    JoySt.YAxis = 127;

  if (controllerData1 & LEFT)
    JoySt.XAxis = 0;
  else if (controllerData1 & RIGHT)
    JoySt.XAxis = 255;
  else //if neither lefr or right are pressed, center X axis
    JoySt.XAxis = 127;

  //Shift bits right by 4
  //4 most LSBs are now the button states
  controllerData1 = controllerData1 >> 4;
  JoySt.Buttons = controllerData1;

  if (controllerData2 & UP)
    JoySt.YAxis2 = 0;
  else if (controllerData2 & DOWN)
    JoySt.YAxis2 = 255;
  else //if neither up or down are pressed, center Y axis
    JoySt.YAxis2 = 127;

  if (controllerData2 & LEFT)
    JoySt.XAxis2 = 0;
  else if (controllerData2 & RIGHT)
    JoySt.XAxis2 = 255;
  else //if neither lefr or right are pressed, center X axis
    JoySt.XAxis2 = 127;
    
  //Shift bits right by 4
  //4 most LSBs are now the button states
  controllerData2 = controllerData2 >> 4;
  JoySt.Buttons2 = controllerData2;


  Joystick.setState(&JoySt);


}


