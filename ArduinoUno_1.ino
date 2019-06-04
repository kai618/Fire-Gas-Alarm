/*
 * Arduio1 gets data from sensors, IR remote and transmits it to Arduino2
*/


#include <Servo.h>
#include <IRremote.h>

//pin
const int servo = 2;
const int button = 3;
const int ir = 4;
const int gasSen = A1; 
const int flameSen = A0;

//Threshold
const int gasLimit = 220;
const int flameLimit = 100;

//State
bool mainState = false;  //true = on, false = off
bool butState = false;  //true = pressed, false = unpressed
unsigned long pressTime = 0;
const unsigned long waitTime = 500;

//Servo
Servo sv;
int angle = 0;
int svStep = 1;

//IR receiver
IRrecv irrecv(ir);
decode_results result; 
bool check1 = false, check2 = false;

//Mode
const char OffMode = '0';
const char SafeMode = '1';
const char GasMode = '2';
const char FireMode = '3';
char nowMode = '0';

void setup() {
  Serial.begin(115200);
  delay(100);  
  irrecv.enableIRIn();
  setupServo();
}

void loop() {
  checkButton();
  if(mainState) setOnMode();
  else setOffMode();
}

void checkButton() {
  if(mainState == false) {
    if(isButtonPressed() || isInfraredPressed()) mainState = true;
  }
   else {
    if(isButtonHeld() || isInfraredPressed()) mainState = false;
   }
}
bool isButtonPressed() {
  if(digitalRead(button) == HIGH) butState = true;  
  if(butState && digitalRead(button) == LOW) {
    butState = false;
    return true;
  }
  return false;
}
bool isButtonHeld() {
  if(digitalRead(button) == LOW) pressTime = 0;  
  if(digitalRead(button) == HIGH && pressTime == 0) pressTime = millis();
  if(pressTime != 0 && digitalRead(button) == HIGH && millis() - pressTime >= waitTime) butState = true;
  if(butState && digitalRead(button) == LOW) {
    butState = false;
    pressTime = 0;
    return true;
  }
  return false;
}
bool isInfraredPressed() {
  bool x = false;
  if (irrecv.decode(&result)) {
    if(result.value == 0XFF38C7) x = true;
    //Serial.println(result.value, HEX);
    result.value = 0XFFFFFFFF;
    irrecv.resume();
  }
  return x;
}
//bool isInfraredHeld() {
//  if (check1 == false && irrecv.decode(&result)) {
//    if(result.value == 0XFF38C7) check1 = true;
//    irrecv.resume();
//  }
//  if(check1 == true && irrecv.decode(&result)) {
//    if(result.value == 0XFFFFFFFF) check2 = true;
//    irrecv.resume();
//  }
//  if(!irrecv.decode(&result)) {
//    check1 = false; check2 = false;
//    irrecv.resume();
//  }
//  if(check1 && check2) {
//    check1 = false; check2 = false;
//    return true;
//  }       
//  return false;
//}
void setOnMode() {
  setDetectMode(chooseDetectMode());
}
void setOffMode(){
  if(nowMode != OffMode) {
    Serial.println(OffMode);
    nowMode = OffMode;
  }
  getHandBack();
}
void setDetectMode(int i) {
  switch(i) {
    case 1: setSafeMode(); break;
    case 2: setGasMode(); break;
    case 3: setFireMode(); break;
  }
}
int chooseDetectMode() {
  if(detectFlame()) return 3;
  else if(detectGas()) return 2;
  else return 1;
}
void setSafeMode() {
  if(nowMode != SafeMode) {
    Serial.println(SafeMode);
    nowMode = SafeMode;
  }
  scoutArea(30);
}
void setGasMode() {
  if(nowMode != GasMode) {
    Serial.println(GasMode);
    nowMode = GasMode;
  }
  scoutArea(10);
}
void setFireMode() {  
  if(nowMode != FireMode) {
    Serial.println(FireMode);
    nowMode = FireMode;
  }
  delay(15);
}
void scoutArea(int slowness) {    
  angle += svStep;
  sv.write(angle);
  if(angle < 0 || angle > 180) svStep = -svStep;
  delay(slowness);
}
void getHandBack() {
  if(angle > 0){
    sv.write(angle--);
    delay(20);
  }
}
bool detectGas() {
  //Serial.println(analogRead(gasSen));
  if(analogRead(gasSen) > gasLimit) return true;
  return false;
}
bool detectFlame() {
  //Serial.println(analogRead(flameSen));
  if(analogRead(flameSen) > flameLimit) return true;
  return false;
}
void setupServo() {
  sv.attach(servo);
  angle = sv.read();
}