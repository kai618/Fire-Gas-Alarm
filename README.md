# Fire Gas Alarm
This Arduino project uses 2 Arduino UNO and 1 ESP01 to work as a fire gas detector.  
It was the final project of the course THCNTT1.

## Updates
Version 2: [Smart Home Project](https://github.com/kai618/smart-home-project)  
Version 3: OmniCare (Updating)

## Demo
[A short video on YouTube]( https://youtu.be/Pv0fgiOIsCE)  
In the video, I utilised AsyncTask in my Android app.

## Descriptions
#### Arduino 1
- Gets signals from the flame sensor, gas sensor, IR remote and button.
- Turns them into data then transmits it to Arduino 2. 
#### Arduino 2
- Receives data from Arduino 1.
- Adjusts LEDs and buzzer according to the data.
- Forwards that data to ESP01.
#### ESP01
- Receives data from Arduino 2.
- Connects to an access point via SSID.
- Plays a role as a web server to respond resquests from wifi clients.


