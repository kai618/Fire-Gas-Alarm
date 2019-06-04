/*
Code for ESP8266-01 Board
Station mode - Server
Identify DHCP IP first
IP Address at Home: 192.168.1.11
IP Address at School: 10.
Receives data from clients

ESP8266 - Project1 - THCNTT1
0 OFF mode
1 SAFE mode
2 GAS mode
3 FIRE mode
*/

#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

ESP8266WebServer server(80);

String modeStr = "0";
char modeChar = 0;
 
void setup() {
  Serial.begin(115200);
  delay(500); //needs this to print normally, 300 is enough
  //WiFi.begin("GHC_", "12356789");
  WiFi.begin("HSU_Students", "dhhs12cnvch");
  
  Serial.print("Waiting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println(WiFi.localIP());
  server.on("/", respondRoot);  
  server.on("/i", respondInfo);
  server.begin();
}
 
void loop() {
  modeChar = Serial.read();
  if(modeChar == '1') modeStr = "1"; 
  else if(modeChar == '2') modeStr = "2"; 
  else if(modeChar == '3') modeStr = "3"; 
  else if(modeChar == '0') modeStr = "0"; 
  if(modeChar == 'i') Serial.println(WiFi.localIP());
  server.handleClient(); 
}
 
void respondRoot() {
  server.send(200, "text/plain", modeStr);
}
void respondInfo() {
  server.send(200, "text/plain", "Hieu - 2170054");
}