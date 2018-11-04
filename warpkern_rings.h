#ifndef WARPKERN_RINGS_H
#define WARPKERN_RINGS_H

#include <vector>

#include "pca9685.h"
#include "ringcoulors.h"

using std::vector;

class led_stripe
{
private:
    unsigned int FNumberRings;
    unsigned int FStartChannel;
    unsigned int FEndChannel;
    vector <pca9685*> FIC;
    vector <RingColours> FColors;
public:
    led_stripe (int LStartChannel, int LEndChannel, vector<int> list_addresses);
    ~led_stripe();
    void SetIntensity(unsigned int LRing, const RingColours* LColors);
    void alloff(void);
	unsigned int GetRingCount();
};
 
#endif //WARPKERN_RINGS_H