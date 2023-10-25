# Arduino Halloween Witch
Fun Halloween toy made in Arduino which detects human presence and plays an audio of a witch laughing. 

<img src="https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/c8869ce1-a40a-4559-9e07-06a2c4c21a3c" width="400">

## Video footage
Note: Before playing the video below, you must enable the sound by clicking on the toolbar button with a speaker icon:

[video.webm](https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/7db5073f-574d-4b5b-8d4f-bd07080acd24)

## Description
![ArduinoHalloween_bb](https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/438a9ba2-e9ba-4de0-9060-833ce816f3ac)

This is a [Platform IO IDE](https://platformio.org/platformio-ide) project coded in C++.

Once a person is detected, the Arduino will firstly open and close the witch's legs twice, and afterwards will play an audio of a witch laughing.

Note: when using 04 AAA batteries (1.5v each, total 6v), you should connect the positive cable to the "VIN" pin since it has a built-in voltage regulator. However, with 04 rechargeable batteries (1.3v each, total 5.5v) it is acceptable to place the cable in "5v" pin. See [Arduino docs](https://docs.arduino.cc/learn/electronics/power-pins#vin-pin).

## Components
* 01 - HC-SR04 Ultrasonic sensor
* 01 - Speaker (8Ohms - 0.5 to 1.0 Watts)
* 01 - Micro Servo Motor 9g SG90 (or similar)
* 01 - BC547 transistor
* 04 - AAA batteries (or any 5v source supply)
* 01 - AAA batteries support

## About PlatformIO IDE
Platform IO is a plugin for Microsoft Visual Studio Code. It is a more robust IDE compared to the official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

## About the "witch hat"
You may create your own hat or buy any that fits the arduino components. 

<img src="https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/3d2bae90-adba-412a-a531-2edcaf16ebcb" width="400">

<img src="https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/2732d0b2-0b27-4843-836f-034b7d2716b5" width="400">

Find below the components used to create the legs movement:

* 02 - Sticks (like chopsticks)
* 02 - Nylon clamps
* 01 - A mechanism which attaches to a servo motor and creates the movement of opening and closing the legs ([like this one](https://www.robocore.net/item-mecanico/garra-robotica-ant_v2))

<img src="https://github.com/vitorccs/arduino-halloween-witch/assets/9891961/7e9afe9d-1bbd-41a7-a874-06421414e791" width="200">

## Steps to change the audio sample
1) Download and install [Audacity](https://www.audacityteam.org/download/)
2) Import a MP3 file and export a new version in 8KHz in mono mode. The file should not exceed 30.000 bytes.
3) Download the encoder program for your operating system:
    * [EncodeAudio - Windows.zip](https://github.com/vitorccs/arduino-halloween-witch/files/13110714/EncodeAudio-windows.zip)
    * [EncodeAudio - MacoOSX.zip](https://github.com/vitorccs/arduino-halloween-witch/files/13110716/EncodeAudio-macosx.zip)
    * [EncodeAudio - Linux.zip](https://github.com/vitorccs/arduino-halloween-witch/files/13110717/EncodeAudio-linux.zip)
4) Unzip and run the application.
5) The application will prompt you to input an audio file. Select the audio file you have just created in the previous steps.
6) After a few seconds, the program will copy the encoded data to your clipboard
7) In the `main.cpp` file, delete the contents of `sample[]` array and paste the content from your clipboard. The data is a a very large sequence of numbers.

Sources:
* https://www.codrey.com/arduino-projects/arduino-pcm-audio-primer/
* https://highlowtech.org/?p=1963
* https://www.youtube.com/watch?v=aaqaAXlZbuc

## Fritzing file
The electronic schematic was created in the Fritzing software and can be downloaded at [ArduinoHalloween.zip](https://github.com/vitorccs/arduino-halloween-witch/files/13110614/ArduinoHalloween.zip)
