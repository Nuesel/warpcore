#ifndef PRESETS_H
#define PRESETS_H

#include "json/json.h"
#include <string>
#include <fstream>
#include <vector>
#include "ringcoulors.h"

class presets {
private:
    Json::Value preset_data;
	std::string PresetFilename;
    bool check_bom_isutf8(std::ifstream *filestream, int *p_bomsize);
    void add_data(const Json::Value newdata);
	bool ExtractColourString(std::string color_data, float *red, float* green, float* blue);
	Json::Value ExtractColourFromString(Json::Value PresetData);
	bool ExtractRingString(std::string color_data, unsigned int* RingNr);
public:
    presets(unsigned int numer_rings, std::string filename);
    ~presets();
    void read_file (Json::Value* commands);
	void update_data(Json::Value newdata);
	bool remove_preset(unsigned int preset_id);
	bool get_preset_from_id(unsigned int id, Json::Value* preset);
	Json::Value get_preset_list(void);
	unsigned int get_next_preset_id(unsigned int this_preset_id);
};


#endif //COMMANDLINE_H
