# Fire-Gas-Alarm
An Arduino project using 2 Arduino UNO and 1 ESP01 as a fire gas detector.

[A short demo on YouTube]( https://youtu.be/Pv0fgiOIsCE)

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

In the video, I use AsyncTask for my android app.
