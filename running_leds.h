#ifndef RUNNING_LEDS_H
#define RUNNING_LEDS_H

#include <boost/thread.hpp>
#include "presets.h"
#include "warpkern_rings.h"
#include "ringcoulors.h"
#include <vector>

typedef struct{
	std::vector<RingColours> Color;
	std::string sound_file;
	unsigned int duration;
} preset_step;

typedef struct {
	std::string ambient_sound;
	RingColours Default_Color;
	float Speed;
	std::string Name;
	unsigned int id;
	std::vector<preset_step> preset_steps;
} preset_struct;

class running_leds {
private:
	led_stripe* Fled_stripes;
	presets* Fpreset_data;
	bool FExit_flag;
	bool FShutdown_flag;
	std::vector<RingColours> FRingColors;
	unsigned int FRingCount;
	preset_struct current_preset;
	bool warpkern_running;
	
	void run_led (void);
	void alloff(void);
	unsigned short ConvertColorToPCA(float percentage);
	bool ExtractColour(std::string color_data, RingColours* rgb_data);
	bool ExtractColourJSON(Json::Value RGBData, RingColours* rgb_data);
public:
    running_leds(led_stripe* Lled_stripes, presets* preset_data);
    ~running_leds(void);
    
	unsigned int get_preset_id(void);
    boost::thread *ledthread;
	bool start_preset(unsigned int id);
	void disable(void);
	Json::Value AnalyzeCmd(Json::Value Commands);
	bool is_running(void);
	bool GetShutdown(void);
	bool GetExit(void);
	void ReadPresetFile(void);
};

#endif //RUNNING_LEDS_H
