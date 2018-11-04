#include <errno.h>     // error
#include <string.h>    // error string
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "general.h"
#include "program.h"
#include "pca9685.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#ifndef PCA9685_DUMMY
#include <wiringPi.h>
#include <wiringPiI2C.h>
#endif

#define RESOLUTION 4096

//#include <vector>
//#include <boost/thread.hpp>
//#include <boost/algorithm/string.hpp>
//extern std::vector<int> zeit;

using namespace std;

void pca9685::write_i2c (int ic_register, int value)
{
    int ergebnis = 0;
    #ifndef PCA9685_DUMMY
        ergebnis = wiringPiI2CWriteReg8(FFileDescriptor, ic_register, value);
    #endif
    if (ergebnis < 0)
    {
        cout << "Unable to write to device: " << strerror (errno) << endl;
        exit(EXIT_FAILURE);
    }
}

int pca9685::select_register (int channel)
{
    int start_register = 0;
    switch (channel)
    {
        case 0: 
            start_register = 6;
            break;
        case 1:
            start_register = 10;
            break;
        case 2:
            start_register = 14;
            break;
        case 3:
            start_register = 18;
            break;
        case 4:
            start_register = 22;
            break;
        case 5:
            start_register = 26;
            break;
        case 6:
            start_register = 30;
            break;
        case 7:
            start_register = 34;
            break;
        case 8:
            start_register = 38;
            break;
        case 9:
            start_register = 42;
            break;
        case 10:
            start_register = 46;
            break;
        case 11:
            start_register = 50;
            break;
        case 12:
            start_register = 54;
            break;
        case 13:
            start_register = 58;
            break;
        case 14:
            start_register = 62;
            break;
        case 15:
            start_register = 66;
            break;
        default:
            start_register = 6;
    }
    return start_register;
}

pca9685::pca9685 (int address)
{
    #ifndef PCA9685_DUMMY
        FFileDescriptor = wiringPiI2CSetup (address);
		if (FFileDescriptor < 0)
		{
			cout << "Unable to setup I2C: " << strerror (errno) << endl;
			exit(EXIT_FAILURE);
		}
	#endif
    
    //Register 0x00:
    //0x00: All Off
    //0x20: Auto Increment
    #ifndef PCA9685_DUMMY
    write_i2c (0x00, 0x00);
    #endif

    //Register 0x01:
    //0x04: Totem Pole
    //0x10: invert
    //0x0C: Change duty cycle after writing ALL 4 registers + Totem Pole
    #ifndef PCA9685_DUMMY
    write_i2c (0x01, 0x0C);
    #endif
    
    #ifndef PCA9685_DUMMY
    //Set PWM frequency to 1kHz
    set_frequency(1000);
    #endif
}

void pca9685::alloff()
{
    //Switch off all LEDs
//    DEBUG_MSG("Switch off all LEDs");
    #ifndef PCA9685_DUMMY
    write_i2c (0xFA, 0x00);
    write_i2c (0xFB, 0x00);
    write_i2c (0xFC, 0x00);
    write_i2c (0xFD, 0x10);
    #endif
}

pca9685::~pca9685 ()
{
    //alloff();
}

void pca9685::set_frequency (double frequency)
{
    int prescale = ((int)round(25000000 / 4096 / frequency)) - 1;
    #ifndef PCA9685_DUMMY
    write_i2c (0x00, 0x10); // set to sleep
    write_i2c (0xFE, prescale);
    write_i2c (0x00, 0x00);
    #else
    UNUSED(prescale);
    #endif
}

void pca9685::set_intensity (int channel, int intensity)
{
    int int_zwischen = 0;
    int ic_register = 0;
    int led_on_low = 0;
    int led_on_high = 0;
    int led_off_high = 0;
    int led_off_low = 0;
    int offset = (channel * 250) % RESOLUTION;
    
    ic_register = select_register (channel);
    if ((0 < intensity) && (intensity < (RESOLUTION - 1)))
	{
        led_on_high = (int)(offset / 0x100);
        led_on_low = offset - (led_on_high * 0x100);
        int_zwischen = (intensity + offset) % RESOLUTION;
        led_off_high = ((int) (int_zwischen / 0x100));
        led_off_low = int_zwischen - (led_off_high * 0x100);
    }
    else if (intensity >= (RESOLUTION - 1))
	{
		//all full on
        led_on_low = 0x00;
        led_on_high = 0x10;
        led_off_low = 0x00;
        led_off_high = 0x00;
    }
    else
	{
		//all off
        led_on_low = 0x00;
        led_on_high = 0x00;
        led_off_low = 0x00;
        led_off_high = 0x10;
    }
    DEBUG_MSG("Channel: " << channel << ", Intensity: " << intensity);
    #ifndef PCA9685_DUMMY
    write_i2c (ic_register + 0, led_on_low);
    write_i2c (ic_register + 1, led_on_high);
    write_i2c (ic_register + 2, led_off_low);
    write_i2c (ic_register + 3, led_off_high);
    #else
    UNUSED(ic_register);
    UNUSED(led_on_low);
    UNUSED(led_on_high);
    UNUSED(led_off_low);
    UNUSED(led_off_high);
    #endif
}

