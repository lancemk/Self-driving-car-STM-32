## Self-driving-car-STM-32

DISCLAIMER : This project is not as generic as the arduRover project and is not trying to achieve the same goals, although it was inspired by it. The goal for this project is to understand 

1) AHRS estimation, position estimation through EKFs
2) Driving dynamics of cars and trajectory planning and execution.

The car will not operate without a GCS. This is for safety purposes and not for the sake of functionality. If the car were to operate without a GCS connection and only be in control of the user via the on board Radio control-receiver, there would be a single point of failure in communications. Adding the GCS-compulsion gives the system 2 independent points of failure. This also compulsorily limits the range of operation (which depends on the kind of transceiver used. For xbee pros, this range is ~80 meters, which is more than enough for doing experiments with a 1/10 scale car.)

do not clone it yet! its a work in progress. Its an improved version of the self driving car. It runs on the stm32 bluepill (STM32F103C8T6) BUT it is not yet even in it's testing phase. I am still working on it.

## Building the project : 

(will update this as I build this project)

For the hardware specifications and 3d print files as well as 2 d drawings, go into the "hardware folder"

For the back end libraries, go into the "libraries folder".(surprise surprise).

You will have to clone the following repository : https://github.com/naughtyStark/Arduino_STM32 and follow the instructions in this video for setting up your arduino IDE :
https://www.youtube.com/watch?v=MLEQk73zJoU&t=295s (its pretty simple as arduino already supports it and does not affect your other stuff in arduino so chill)
