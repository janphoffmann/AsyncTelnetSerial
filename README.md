# AsyncTelnetSerial
A Async Telnet to Serial connection library for ESP32 with Arduino IDE

This is a fully async Telnet to Serial library 
For basic usage there is not much to do, have a look at the example.

This work is basically a rewrite of https://github.com/LennartHennigs/ESPTelnet

Being an Async library everything is done in callbacks, there is no need to call anything in the loop() function

# dependencies
- ESP32 Core     - https://github.com/espressif/arduino-esp32/tree/master/cores/esp32
- WiFi           - https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi
- HardwareSerial - https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/HardwareSerial.h
- ESPmDNS        - https://github.com/espressif/arduino-esp32/tree/master/libraries/ESPmDNS
- AsyncTCP       - https://github.com/me-no-dev/AsyncTCP
- AsyncTelnet    - https://github.com/janphoffmann/AsyncTelnet

# usage
- include the library ->#include "AsyncTelnetSerial.h"
- create an instance  ->AsyncTelnetSerial TestInstance(&Serial); // <- link the HardwareSerial eg Serial or Serial1
- declare the callbackfunctions if need any
- in Setup() function 
- - setup your WiFi as usual,
- - then attatch the callback functions to the declared instance
- - then call the begin() function -> TestInstance.begin(baudrate, LinkTelnetToSerial, enableMDNS); 
- - - // default baudrate = 115200, default LinkTelnetToSerial = true, default mDNS = false!
Thats it.

To test this, you can use TeraTerm and connect to esp32.local over Telnet at port 23, open the serial monitor in the arduino IDE.
