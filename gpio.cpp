#include "gpio.h"
#include "general.h"
#include <iostream>
#include <stdlib.h>
#include <errno.h>     // error
#include <string.h>    // error string
#ifndef PCA9685_DUMMY
    #include <wiringPi.h>
#endif

#define enable_pin 7

void init_wiringpi(void)
{
    //setup access to GPIO pins
    int LWiringPi = 0;
    #ifndef PCA9685_DUMMY
        LWiringPi = wiringPiSetup();
    #endif
    if (LWiringPi < 0)
    {
        std::cout << "Unable to setup wiringPi: " << strerror (errno) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void init_gpio(void)
{
    #ifndef PCA9685_DUMMY
    //DEBUG_MSG("Init Enable-Pin");
    pinMode (enable_pin, OUTPUT);
    #endif
}

void enable_ics(void)
{
    //DEBUG_MSG("Set Enable-Pin to HIGH");
    #ifndef PCA9685_DUMMY
    digitalWrite (enable_pin, HIGH);
    #endif
}

void disable_ics(void)
{
    //DEBUG_MSG("Set Enable-Pin to LOW");
    #ifndef PCA9685_DUMMY
    digitalWrite (enable_pin, LOW);
    #endif
}
