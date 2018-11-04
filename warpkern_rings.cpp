#include "warpkern_rings.h"
#include "general.h"
#include <cstddef>
#include <iostream>
#include <cstdlib>

led_stripe::led_stripe (int LStartChannel, int LEndChannel, vector<int> list_addresses)
{
    unsigned int LNumberICs = 0;
	unsigned int LNumberChannels = 0;
    pca9685* ic_pca9685 = NULL;
    
    FStartChannel = LStartChannel;
    FEndChannel = LEndChannel;
    
	LNumberChannels = FEndChannel - FStartChannel + 1;
    FNumberRings = LNumberChannels / 3;
    if (LNumberChannels % 3 > 0)
    {
        FNumberRings++;
    }
    LNumberICs = LNumberChannels / PCA9685_PINS;
    if (LNumberChannels % PCA9685_PINS > 0)
    {
        LNumberICs++;
    }
    
    if (LNumberChannels > LNumberICs * PCA9685_PINS)
    {
        std::cout << "Problem: Number of channels (" << LNumberChannels << ") exceeds number PCA9685 pins (" << list_addresses.size() * PCA9685_PINS << ")" << std::endl;
		exit(2);
    }
    
    //for (unsigned int i = 0; i < LNumberICs && i < list_addresses.size(); i++)
	for (unsigned int i = 0; i < list_addresses.size(); i++)
    {
        ic_pca9685 = new pca9685(list_addresses[i]);
        FIC.push_back(ic_pca9685);
    }
    
    for (unsigned int i = 0; i < FNumberRings; i++)
    {
        FColors.push_back(ColorLEDOff);
    }
    alloff();
}

led_stripe::~led_stripe()
{
    alloff();
    
    while (FIC.size() > 0)
    {
        delete FIC.back();
        FIC.pop_back();
    }
}

void led_stripe::SetIntensity(unsigned int LRing, const RingColours* LColors)
{
    unsigned int LLEDStripe = LRing * 3 + FStartChannel;
    
    unsigned int ic_index_red = (LLEDStripe + 0) / PCA9685_PINS;
    unsigned int ic_index_green = (LLEDStripe + 1) / PCA9685_PINS;
    unsigned int ic_index_blue = (LLEDStripe + 2) / PCA9685_PINS;
    unsigned int ic_pin_red = (LLEDStripe + 0) % PCA9685_PINS;
    unsigned int ic_pin_green = (LLEDStripe + 1) % PCA9685_PINS;
    unsigned int ic_pin_blue = (LLEDStripe + 2) % PCA9685_PINS;
    
    if (LLEDStripe + 0 >= FStartChannel && LLEDStripe + 0 <= FEndChannel)
        if (FColors[LRing].red != LColors->red)
            FIC[ic_index_red]->set_intensity(ic_pin_red, LColors->red);
    
    if (LLEDStripe + 1 >= FStartChannel && LLEDStripe + 1 <= FEndChannel)
        if (FColors[LRing].green != LColors->green)
            FIC[ic_index_green]->set_intensity(ic_pin_green, LColors->green);
    
    if (LLEDStripe + 2 >= FStartChannel && LLEDStripe + 2 <= FEndChannel)
        if (FColors[LRing].blue != LColors->blue)
            FIC[ic_index_blue]->set_intensity(ic_pin_blue, LColors->blue);
    
    if (LRing < FColors.size())
        FColors[LRing] = *LColors;
}

void led_stripe::alloff(void)
{
    for (unsigned int i = 0; i < FNumberRings; i++)
    {
        SetIntensity(i, &(ColorLEDOff));
    }
}

unsigned int led_stripe::GetRingCount()
{
	return FNumberRings;
}