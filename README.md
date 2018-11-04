# warpcore
A warpcore, consisting of multiple RGB LED stripes piled on each other. Each LED stripe is addressed by several PCA9685 via I2C (PWM each LED color). The warpcore server is controlled via a TCP connection using JSON.

To compile, type:
g++ commandline.cpp general.cpp gpio.cpp ./jsoncpp.cpp program.cpp pca9685.cpp socket_server.cpp presets.cpp running_leds.cpp warpkern_rings.cpp -o program -lwiringPi -lboost_thread-mt -lboost_system

WiringPi library (http://wiringpi.com/download-and-install/) as well as boost libaries for threads and system are needed.
Amalgamated source of JsonCpp is also needed (https://github.com/open-source-parsers/jsoncpp/wiki/Amalgamated).

To start program, e.g. type:
program --channel_start=0 --channel_end=49 --port=54321 --list_addresses=0x4C,0x4D,0x4E,0x4F --path_preset=/usbstick/warpkern/presets.json
