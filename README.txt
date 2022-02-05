--- DESCRIPTION ---
This project is designed to receive commands from OpenHab over WiFi and to then parse through the command to execute the proper LED light pattern.


--- INSTRUCTIONS ---
Make sure to move the libraries folder to whichever directory you have set as your library folder in Arduino.

The LEDLightsAtmega file was written for the Arduino Atmega 2560 board and the UDPforLEDS was written for the Arduino ESP8266 Wifi Module. However, they may work with other boards; the former works with the Arduino UNO board.


--- WORK IN PROGRESS ---
This project is not complete! 

1. After writing the libraries and LEDLightsAtmega file, I have realized that they work rather poorly when it comes to presets that require a repeated pattern. This is because the LEDLightsAtmega file calls the functions in the ColoursFade library, for example, in a loop repeatedly, and the function in the library itself also loops repeatedly. The loop doesn't function properly this way and jumps around between colours. 

Currently, I'm implementing a stateful version of this project to fix this issue.

2. I haven't made the OpenHab part yet.

3. Only two presets have been added to the project so far, ColoursFade and FillSolid. I plan to add many more.


--- CONTACT ME ---
If you have any questions or suggestions, please feel free to contact me at elena@scobici.com.