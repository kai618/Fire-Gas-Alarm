/*
 * Arduio2 receives data from Arduino1, alerts then sends it to ESP01
*/

//Pin
const int redLed = 7;
const int grnLed = 5;
const int bluLed = 6;
const int buzzer = 4;

//State
bool mainState = false;

//Gas Mode
bool alertStateGas = true;  //true = unmuted; false = muted
unsigned long spacingGas = 400;

//Fire Mode
bool alertStateFire = true;  //true = unmuted; false = muted
unsigned long spacingFire = 200;

unsigned long alertTime = 0;

//Mode
const char OffMode = '0';
const char SafeMode = '1';
const char GasMode = '2';
const char FireMode = '3';

char nowMode = OffMode;
char newMode = OffMode;

void setup() {
  Serial.begin(115200);
  delay(100);
  setupLEDpin();
  pinMode(buzzer, OUTPUT);
}
void loop() {
  detectMode();
  changeMode();
}

void detectMode() {
  if(Serial.available()) newMode = Serial.read();
  if(newMode != nowMode) {
    if(newMode == OffMode || newMode == SafeMode 
    || newMode == GasMode || newMode == FireMode) {
      nowMode = newMode;
      Serial.println(nowMode);      
    }
  }
}
void changeMode() {
  switch(nowMode) {
    case OffMode : setOffMode(); break;
    case SafeMode : setSafeMode(); break;
    case GasMode : setGasMode(); break;
    case FireMode : setFireMode(); break;
  }
}
void setOffMode(){  
  setColor(0,0,0);
  if(mainState) {
    mainState = false;
    beepOff();
  }
}
void setSafeMode() {
  setColor(0,255,0);
  if(!mainState) {
    mainState = true;
    beepOn();    
  }  
}
void setGasMode() {  
  delay(15);
  mainState = true;
  if(alertTime == 0) alertTime = millis();
  if(millis() - alertTime > spacingGas) {
    switchAlertGas();
    alertTime = 0;
  }
}
void setFireMode() {  
  delay(15);
  mainState = true;
  if(alertTime == 0) alertTime = millis();
  if(millis() - alertTime > spacingFire) {
    switchAlertFire();
    alertTime = 0;
  }
}
void switchAlertGas() {
  if(alertStateGas) setAlertONGas();
  else setAlertOFF();
  alertStateGas = !alertStateGas;
}
void switchAlertFire() {
  if(alertStateFire) setAlertONFire();
  else setAlertOFF();
  alertStateFire = !alertStateFire;
}
void setAlertONGas() {  
  setColor(255,255,0);
  tone(buzzer,500, spacingGas);
}
void setAlertONFire() {
  setColor(255,0,0);
  tone(buzzer, 1000, spacingFire);
}
void setAlertOFF() {
  setColor(0,0,0);
}
void beepOn(){
  tone(buzzer,700,100);
}
void beepOff(){
  tone(buzzer,200,500);
}
void setColor(int redVal, int grnVal, int bluVal) {
  analogWrite(redLed, redVal);
  analogWrite(grnLed, grnVal); 
  analogWrite(bluLed, bluVal); 
}
void setupLEDpin() {
  pinMode(redLed, OUTPUT);
  pinMode(grnLed, OUTPUT);
  pinMode(bluLed, OUTPUT);
}