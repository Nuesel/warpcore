# warpcore
To compile, type:
g++ commandline.cpp general.cpp gpio.cpp ./jsoncpp.cpp program.cpp pca9685.cpp socket_server.cpp presets.cpp running_leds.cpp warpkern_rings.cpp -o program -lwiringPi -lboost_thread-mt -lboost_system
WiringPi library (http://wiringpi.com/) as well as boost libaries for threads and system are needed.

To start program, e.g. type:
program --channel_start=0 --channel_end=49 --port=54321 --list_addresses=0x4C,0x4D,0x4E,0x4F --path_preset=/usbstick/warpkern/presets.json
