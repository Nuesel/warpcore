#include "running_leds.h"
#include "general.h"
#include <sstream>

#define CURRENT_STEP current_preset.preset_steps
#define pca9685_RESOLUTION 4096
#define ROUND_SHORT(x) ((unsigned short)(floor(x)))

running_leds::running_leds(led_stripe* Lled_stripes, presets* preset_data)
{
	Fpreset_data = preset_data;
    Fled_stripes = Lled_stripes;
	
	FRingCount = Fled_stripes->GetRingCount();
	FRingColors.clear();
	for (unsigned int i = 0; i < FRingCount; i++)
	{
		FRingColors.push_back(ColorLEDOff);
	}
	Fled_stripes->alloff();
	
	current_preset.id = 0;
	current_preset.Name = "";
	current_preset.Speed = 1;
	current_preset.ambient_sound = "";
	current_preset.Default_Color = ColorLEDOff;
	current_preset.preset_steps.resize(0);
	warpkern_running = false;
	FExit_flag = false;
	FShutdown_flag = false;
	
    ledthread = new boost::thread(&running_leds::run_led, this);
}
running_leds::~running_leds(void)
{
	FExit_flag = true;
    ledthread->join();
}

bool running_leds::ExtractColourJSON(Json::Value RGBData, RingColours* rgb_data)
{
	bool result = false;
	
	if (RGBData["red"].isUInt())
	{
		rgb_data->red = ConvertColorToPCA(RGBData.get("red", 0).asUInt());
		result = true;
	}
	if (RGBData["green"].isUInt())
	{
		rgb_data->green = ConvertColorToPCA(RGBData.get("green", 0).asUInt());
		result = true;
	}
	if (RGBData["red"].isUInt())
	{
		rgb_data->blue = ConvertColorToPCA(RGBData.get("blue", 0).asUInt());
		result = true;
	}
	
	return result;
}

bool running_leds::ExtractColour(std::string color_data, RingColours* rgb_data)
{
	float red = 0;
	float green = 0;
	float blue = 0;
	bool result = false;
	
	*rgb_data = ColorLEDOff;
	if (sscanf(color_data.c_str(), "%f:%f:%f", &red, &green, &blue) == 3)
	{
		if ((red >= 0 && red <= MAX_VALUE) && (green >= 0 && green <= MAX_VALUE) && (blue >= 0 && blue <= MAX_VALUE))
		{
			rgb_data->red = ConvertColorToPCA(red);
			rgb_data->green = ConvertColorToPCA(green);
			rgb_data->blue = ConvertColorToPCA(blue);
			result = true;
		}
	}
	
	return result;
}

/*RingColours running_leds::ExtractColour(std::string color_data)
{
	RingColours rgb_data;
	float red = 0;
	float green = 0;
	float blue = 0;
	
	rgb_data = ColorLEDOff;
	if (sscanf(color_data.c_str(), "%f:%f:%f", &red, &green, &blue) == 3)
	{
		if ((red >= 0 && red <= MAX_VALUE) && (green >= 0 && green <= MAX_VALUE) && (blue >= 0 && blue <= MAX_VALUE))
		{
			rgb_data.red = ConvertColorToPCA(red);
			rgb_data.green = ConvertColorToPCA(green);
			rgb_data.blue = ConvertColorToPCA(blue);
		}
	}
	
	return rgb_data;
}*/

static std::string NumberToString (unsigned int number)
{
 std::ostringstream ss;
 ss << number;
 return ss.str();
}

unsigned short running_leds::ConvertColorToPCA(float percentage)
{
	return (ROUND_SHORT((percentage * (pca9685_RESOLUTION - 1)) / MAX_VALUE));
}

bool running_leds::start_preset(unsigned int id)
{
	int DefaultDuration = 0;
	Json::Value removed;
	Json::Value ExtractPreset;
	bool preset_found = false;
	RingColours ExtractedColor;
	std::string ExtrColor = "";
	std::string sound_file = "";
	
	disable();
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	
	preset_found = Fpreset_data->get_preset_from_id(id, &ExtractPreset);
	if (preset_found == true)
	{
		current_preset.id = id;
		current_preset.Name = ExtractPreset.get("name", "").asString();
		
		current_preset.Default_Color = ColorLEDOff;
		ExtractColourJSON(ExtractPreset["defaultcolor"], &current_preset.Default_Color);
		
		current_preset.ambient_sound = ExtractPreset.get("ambient", "").asString();
		current_preset.Speed = ExtractPreset.get("speed", 1).asFloat();
		DefaultDuration = ExtractPreset.get("duration", 0).asFloat();
		current_preset.preset_steps.resize(ExtractPreset["steps"].size());
		for (unsigned int i = 0; i < ExtractPreset["steps"].size(); i++)
		{
			current_preset.preset_steps[i].Color.resize(FRingCount);
			for (unsigned int j = 0; j < FRingCount; j++)
			{
				//ExtrColor = ExtractPreset["steps"][i].get("r" + NumberToString(j), "0:0:0").asString();
				//ExtractColour(ExtrColor, &ExtractedColor);
				ExtractedColor = current_preset.Default_Color;
				ExtractColourJSON(ExtractPreset["steps"][i]["ring" + NumberToString(j)], &ExtractedColor);
				current_preset.preset_steps[i].Color[j] = ExtractedColor;
			}
			current_preset.preset_steps[i].duration = ExtractPreset["steps"][i].get("duration", DefaultDuration).asUInt();
			current_preset.preset_steps[i].sound_file = ExtractPreset["steps"][i].get("sound", "").asString();
		}
		if (! (current_preset.ambient_sound.empty()))
		{
			sound_file = "/opt/led-program/sound_loop.sh /usbstick/presets/" + current_preset.ambient_sound + " &";
			DEBUG_MSG("Ambient sound file: " << sound_file);
			std::system(sound_file.c_str());
		}
		warpkern_running = true;
	}
	return preset_found;
}

unsigned int running_leds::get_preset_id(void)
{
	if (warpkern_running == true)
	{
		return current_preset.id;
	}
	else
	{
		return 0;
	}
}

void running_leds::disable(void)
{
	std::string sound_file = "";
	
	warpkern_running = false;
	Fled_stripes->alloff();
	alloff();
	current_preset.id = 0;
	
	sound_file = "killall sound_loop.sh > /dev/null 2>&1";
	std::system(sound_file.c_str());
	sound_file = "killall lame > /dev/null 2>&1";;
	std::system(sound_file.c_str());
}

bool running_leds::is_running(void)
{
	return warpkern_running;
}

void running_leds::alloff(void)
{
	unsigned int i = 0;
	for (i = 0; i < FRingCount; i++)
	{
		FRingColors[i] = ColorLEDOff;
	}
	
}

void running_leds::run_led (void)
{
	std::string sound_file = "";
	unsigned int delay_time = 0;
	
    while (FExit_flag == false)
    {
		if (is_running() == true)
		{
			for (unsigned int i = 0; i < CURRENT_STEP.size(); i++)
			{
				if (! (CURRENT_STEP[i].sound_file.empty()))
				{
					sound_file = "lame --quiet --decode /usbstick/presets/" + CURRENT_STEP[i].sound_file + " - -| aplay -q &";
					DEBUG_MSG("Sound file: " << sound_file);
					std::system(sound_file.c_str());
				}
					
				for (unsigned int ring = 0; (ring < FRingCount) && (is_running() == true); ring++)
				{
					//Setze definierte Farbe oder Hintergrund?
					if (FRingColors[ring].red != CURRENT_STEP[i].Color[ring].red || FRingColors[ring].green != CURRENT_STEP[i].Color[ring].green || FRingColors[ring].blue != CURRENT_STEP[i].Color[ring].blue)
					{
						DEBUG_MSG("Ring: " << ring << "; color: " << (int)(CURRENT_STEP[i].Color[ring].red) << ":" << (int)(CURRENT_STEP[i].Color[ring].green) << ":" << (int)(CURRENT_STEP[i].Color[ring].blue));
						Fled_stripes->SetIntensity(ring, &(CURRENT_STEP[i].Color[ring]));
						FRingColors[ring] = CURRENT_STEP[i].Color[ring];
					}
				}
				delay_time = (unsigned int)(((float)CURRENT_STEP[i].duration) / ((float)current_preset.Speed));
				boost::this_thread::sleep(boost::posix_time::milliseconds(delay_time));
			}
		}
		else
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		}
    }
}

bool running_leds::GetShutdown(void)
{
	return FShutdown_flag;
}

bool running_leds::GetExit(void)
{
	return FExit_flag;
}

Json::Value running_leds::AnalyzeCmd(Json::Value Commands)
{
	Json::Value Answer;
	unsigned int preset_id = 0;
	
	if (Commands.isMember("delete_preset"))
	{
		if (Commands["delete_preset"].isUInt() == true)
		{
			if (Fpreset_data->remove_preset(Commands["delete_preset"].asUInt()) == true)
			{
				Answer["commands"]["delete_preset"] = Commands["delete_preset"].asUInt();
			}
		}
	}
	if (Commands.isMember("run_preset"))
	{
		if (Commands["run_preset"].isUInt() == true)
		{
			preset_id = Commands["run_preset"].asUInt();
			if (start_preset(preset_id) == true)
			{
				Answer["commands"]["run_preset"] = preset_id;
			}
			else
			{
				Answer["commands"]["run_preset"] = 0;
			}
		}
	}
	if (Commands.isMember("get_current_preset"))
	{
		Answer["commands"]["get_current_preset"] = get_preset_id();
	}
	if (Commands.isMember("set_next_preset"))
	{
		preset_id = Fpreset_data->get_next_preset_id(get_preset_id());
		if (start_preset(preset_id) == true)
		{
			Answer["commands"]["set_next_preset"] = preset_id;
		}
		else
		{
			disable();
			Answer["commands"]["set_next_preset"] = 0;
		}
	}
	if (Commands.isMember("stop_preset"))
	{
		if (Commands["stop_preset"].asBool() == true)
		{
			disable();
			Answer["commands"]["stop_preset"] = true;
		}
		else
		{
			Answer["commands"]["stop_preset"] = false;
		}
	}
	if (Commands.isMember("get_presets"))
	{
		Answer["commands"]["get_presets"];
		Answer["presets"] = Fpreset_data->get_preset_list();
	}
	if (Commands.isMember("reload_presetfile"))
	{
		if (Commands["reload_presetfile"].asBool() == true)
		{
			disable();
			ReadPresetFile();
		}
	}
	
	if (Commands.isMember("exit"))
	{
		if (Commands["exit"].asBool() == true)
		{
			disable();
			Answer["commands"]["exit"] = true;
			FExit_flag = true;
		}
		else
		{
			Answer["commands"]["exit"] = false;
		}
	}
	if (Commands.isMember("shutdown"))
	{
		if (Commands["shutdown"].asBool() == true)
		{
			disable();
			Answer["commands"]["shutdown"] = true;
			Answer["commands"]["exit"] = true;
			FShutdown_flag = true;
			FExit_flag = true;
		}
		else
		{
			Answer["commands"]["shutdown"] = false;
		}
	}
	
	return Answer;
}

void running_leds::ReadPresetFile(void)
{
	Json::Value Commands;
	Fpreset_data->read_file(&Commands);
	AnalyzeCmd(Commands);
}