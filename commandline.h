#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <string>
#include <getopt.h>
#include <vector>

using namespace std;

const struct option long_options[] =
{
    {"port",           required_argument, 0, 0},
    {"channel_start",  required_argument, 0, 0},
    {"channel_end",    required_argument, 0, 0},
    {"path_preset",    required_argument, 0, 0},
    {"list_addresses", required_argument, 0, 0},
    {0,                0,                 0, 0}
};

typedef struct
{
    int port;
    int channel_start;
    int channel_end;
    string path_preset;
    vector<int> list_addresses;
} option_values;

void commandline_options(int argc, char* const argv[], option_values* values);

#endif //COMMANDLINE_H
