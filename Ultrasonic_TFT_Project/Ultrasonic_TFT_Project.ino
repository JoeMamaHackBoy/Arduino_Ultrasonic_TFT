
// By BobWithTech at Instructables.com
// All Involved Library setup are included from the library below:
#include "Variable_Setup.h" //All function and library in there just to make it neat

void setup() {
  //Initialise the Serial Monitor for Debugging Purpose or etc
  Serial.begin(9600);
  //Pin Mode Setup
  pinMode(buzzerPin, OUTPUT);
  pinMode(bPin, OUTPUT), pinMode(gPin, OUTPUT), pinMode(rPin, OUTPUT);
  pinMode(trigPin, OUTPUT), pinMode(echoPin, INPUT);

  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.begin(ID);
  tft.setRotation(5); //Set Directinal Rotation Display Of The Intended Display
  
  Serial.println(tft.width()); //print the maximum width dimension
  Serial.println(tft.height()); //print the maximum height dimension
  
  //Preparing the background display and clearing the previous display
  startupDisplay(); //setting up the display
}

void loop() {
  // put your main code here, to run repeatedly:
  final_result();
  delay(70);
}
