#include "presets.h"
#include <string.h> //memcmp
#include <iostream> //cout
#include <ctype.h> //isdigit
#include <stdlib.h>
#include <stdio.h>
#include <list>

#include "general.h"
#include "ringcoulors.h"

presets::presets(unsigned int numer_rings, std::string filename)
{
	PresetFilename = filename;
	preset_data = Json::Value(Json::arrayValue);
}

presets::~presets(void)
{
    
}

bool presets::check_bom_isutf8(std::ifstream *filestream, int *p_bomsize)
{
    const char UTF_32BE[] = {0x00, 0x00, char(0xfe), char(0xff)};
    const char UTF_32LE[] = {char(0xff), char(0xfe), 0x00, 0x00};
    const char UTF_16BE[] = {char(0xfe), char(0xff)};
    const char UTF_16LE[] = {char(0xff), char(0xfe)};
    const char UTF_8[] = {char(0xef), char(0xbb), char(0xbf)};
    
    char bom_data[4];
    filestream->seekg(0);
    filestream->read(bom_data, 4);
    filestream->seekg(0);
    
    if (memcmp(bom_data, UTF_32BE, sizeof(UTF_32BE)) == 0)
    {
        std::cout << "Presets file is 32-bit big endian." << std::endl;
        *p_bomsize = sizeof(UTF_32BE);
        return false;
    }
    else if (memcmp(bom_data, UTF_32LE, sizeof(UTF_32LE)) == 0)
    {
        std::cout << "Presets file is 32-bit little endian." << std::endl;
        *p_bomsize = sizeof(UTF_32LE);
        return false;
    }
    else if (memcmp(bom_data, UTF_16BE, sizeof(UTF_16BE)) == 0)
    {
        std::cout << "Presets file is 16-bit big endian." << std::endl;
        *p_bomsize = sizeof(UTF_16BE);
        return false;
    }
    else if (memcmp(bom_data, UTF_16LE, sizeof(UTF_16LE)) == 0)
    {
        std::cout << "Presets file is 16-bit little endian." << std::endl;
        *p_bomsize = sizeof(UTF_16LE);
        return false;
    }
    else if (memcmp(bom_data, UTF_8, sizeof(UTF_8)) == 0)
    {
        std::cout << "Presets file is ASCII." << std::endl;
        *p_bomsize = sizeof(UTF_8);
        return true;
    }
    else
    {
        *p_bomsize = 0;
        return true;
    }
}

void presets::read_file (Json::Value* commands)
{
    Json::Value newpresetdata;   // will contains the root value after parsing.
    Json::Value newpreset;
    Json::Reader reader;
    bool parsingSuccessful = false;
    std::ifstream config_file (PresetFilename.c_str(), std::ifstream::in);
    int bomsize = 0;
    int filesize = 0;
    char *contents = NULL;

    if (!(config_file.is_open()))
    {
        std::cout << "Unable to open presets file." << std::endl;
        std::cout << "Ignore presets file." << std::endl;
        return;
    }
    if (check_bom_isutf8(&config_file, &bomsize) != true)
    {
        std::cout << "Ignore presets file." << std::endl;
        return;
    }
    
    config_file.seekg(0, std::ios::end);
    filesize = int(config_file.tellg()) - bomsize;
    contents = new char [filesize];
    config_file.seekg(bomsize, std::ios::beg);
    config_file.read(contents, filesize);
    config_file.close();
    
    parsingSuccessful = reader.parse(contents, contents + filesize - 1, newpresetdata, true);
    if (!parsingSuccessful)
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse JSON presets file." << std::endl << reader.getFormattedErrorMessages() << std::endl;
        return;
    }
    std::cout << "Presets file loaded." << std::endl;
    
    const Json::Value newpresets = newpresetdata["presets"];
    update_data(newpresets);
	if (newpresetdata.isMember("commands"))
	{
		(*commands) = newpresetdata["commands"];
		//AnalyzeCmd(newpresetdata["commands"]);
	}
}

bool IsRingData(std::string name)
{
	//Is first char a 'r' followed by a digit
	unsigned int i = 0;
	bool result = false;
	if (name[0] == 'r')
	{
		result = true;
		for (i = 1; i < name.size(); i++)
		{
			result = result && isdigit(name[i]);
		}
	}
	return result;
}

unsigned int presets::get_next_preset_id(unsigned int this_preset_id)
{
	std::list<unsigned int> preset_ids;
	bool Found = false;
	std::list<unsigned int>::iterator myIterator;
	std::list<unsigned int>::iterator Result;
	
	for (unsigned int i = 0; i < preset_data.size(); i++)  // Iterates over the sequence elements.
    {
		preset_ids.push_back(preset_data[i].get("id", 0).asUInt());
    }
	preset_ids.sort();
	
	myIterator = preset_ids.begin();
	for (unsigned int i = 0; i < preset_data.size(); i++)  // Iterates over the sequence elements.
    {
		if (*myIterator == this_preset_id)
		{
			Found = true;
			Result = myIterator;
		}
		else
		{
			myIterator++;
		}
    }
	
	if (Found == true)
	{
		Result++;
		if (Result == preset_ids.end())
		{
			Result = preset_ids.begin();
		}
	}
	else
	{
		Result = preset_ids.begin();
	}
	return *Result;
}

static std::string NumberToString (unsigned int number)
{
 std::ostringstream ss;
 ss << number;
 return ss.str();
}

bool presets::ExtractRingString(std::string color_data, unsigned int* RingNr)
{
	bool result = false;
	
	if (sscanf(color_data.c_str(), "r%u", RingNr) == 1)
	{
		result = true;
	}
	return result;
}

bool presets::ExtractColourString(std::string color_data, float *red, float *green, float *blue)
{
	bool result = false;
	
	if (sscanf(color_data.c_str(), "%f:%f:%f", red, green, blue) == 3)
	{
		if ((*red >= 0 && *red <= MAX_VALUE) && (*green >= 0 && *green <= MAX_VALUE) && (*blue >= 0 && *blue <= MAX_VALUE))
		{
			result = true;
		}
	}
	return result;
}

Json::Value presets::ExtractColourFromString(Json::Value PresetData)
{
	float red = 0;
	float green = 0;
	float blue = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int RingNumber = 0;
	std::string ExtrColor = "";
	std::string RingNr = "";
	std::vector<std::string> Rings;
	
	if (ExtractColourString(PresetData.get("default", "").asString(), &red, &green, &blue) == true)
	{
		PresetData["defaultcolor"]["red"] = red;
		PresetData["defaultcolor"]["green"] = green;
		PresetData["defaultcolor"]["blue"] = blue;
	}
	for (i = 0; i < PresetData["steps"].size(); i++)
	{
		Rings = PresetData["steps"][i].getMemberNames();	
		for (j = 0; j < Rings.size(); j++)
		{
			if (ExtractRingString(Rings[j], &RingNumber) == true)
			{
				RingNr = "ring" + NumberToString(RingNumber);
				ExtrColor = PresetData["steps"][i].get(Rings[j], "").asString();
				if(ExtractColourString(ExtrColor, &red, &green, &blue) == true)
				{
					if (PresetData["steps"][i][RingNr].isMember("red") == false)
					{
						if (PresetData["steps"][i][RingNr].isMember("green") == false)
						{
							if (PresetData["steps"][i][RingNr].isMember("blue") == false)
							{
								PresetData["steps"][i][RingNr]["red"] = red;
								PresetData["steps"][i][RingNr]["green"] = green;
								PresetData["steps"][i][RingNr]["blue"] = blue;
							}
						}
					}
				}
			}
		}
	}
	return PresetData;
}

void presets::update_data(Json::Value newdata)
{
    unsigned int new_preset_id = 0;
    unsigned int old_preset_id = 0;
	Json::Value removed;
	Json::Value NewPresetData;
    
    for (unsigned int i = 0; i < newdata.size(); i++)
    {
        new_preset_id = newdata[i].get("id", 0).asUInt();
        if (new_preset_id != 0)
        {
            for (unsigned int j = 0; j < preset_data.size(); j++)
            {
                old_preset_id = preset_data[j].get("id", 0).asUInt();
                if (old_preset_id == new_preset_id)
                {
					preset_data.removeIndex(j, &removed);
                }
            }
			NewPresetData = newdata[i];
			NewPresetData = ExtractColourFromString(NewPresetData);
			preset_data.append(NewPresetData);
        }
    }
}

bool presets::remove_preset(unsigned int preset_id)
{
	unsigned int i = 0;
	Json::Value removed;
	bool preset_found = false;
	
	for (i = 0; i < preset_data.size(); ++i)  // Iterates over the sequence elements.
    {
        if (preset_id == preset_data[i].get("id", 0).asUInt())
		{
			preset_data.removeIndex(i, &removed);
			preset_found = true;
		}
    }
	return preset_found;
}



bool presets::get_preset_from_id(unsigned int id, Json::Value* preset)
{
	bool PresetFound = false;
	for (unsigned int i = 0; i < preset_data.size(); ++i)  // Iterates over the sequence elements.
    {
        if (id == preset_data[i].get("id", 0).asUInt())
		{
			*preset = preset_data[i];
			PresetFound = true;
		}
    }
	return PresetFound;
}

/*void presets::get_preset(Json::Value* preset)
{
	*preset = preset_data[current_preset_index];
}

void presets::set_preset_index(unsigned int preset_index)
{
	current_preset_index = int(preset_index);
}*/



Json::Value presets::get_preset_list(void)
{
	return preset_data;
}

