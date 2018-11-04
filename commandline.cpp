#include "commandline.h"
#include "general.h"

#include <ctype.h>
#include <stdlib.h>     // exit, EXIT_FAILURE
#include <string.h>
#include <iostream>

const int cPort = 1;
const int cChannelStart = 2;
const int cChannelEnd = 4;
const int cPresetsPath = 8;
const int cAddressList = 16;

extern char *optarg;

void CheckChar(int option_index, char optarg[])
{
    if (!isdigit(optarg[0]))
    {
        cout << "No valid argument \"" << optarg << "\" for option \"" << long_options[option_index].name << "\"" << endl;
        exit(EXIT_FAILURE);
    }
}

void Extract_List(char *optarg, option_values* values)
{
    string current_opt = "";
    
    for (unsigned int i = 0; i <= strlen(optarg); i++)
    {
        if (optarg[i] == 0 || optarg[i] == ',')
        {
            if (isdigit(current_opt[0]))
            {
                values->list_addresses.push_back(strtol(current_opt.c_str(), NULL, 0));
            }
            else
            {
                exit(EXIT_FAILURE);
            }
            current_opt.clear();
        }
        else
        {
            current_opt.append(&optarg[i], 1);
        }
    }
}

void commandline_options(int argc, char* const argv[], option_values* values)
{
    int option_index = 0;
    int args_found = 0;
    
    values->port = 0;
    values->channel_start = 0;
    values->channel_end = 0;
    values->path_preset.clear();
    values->list_addresses.clear();
    
    while (getopt_long_only(argc, argv, "", long_options, &option_index) != -1)
    {
        switch (option_index)
        {
            case 0:
                CheckChar(option_index, optarg);
                values->port = atoi (optarg);
                args_found |= cPort;
                break;
            case 1:
                CheckChar(option_index, optarg);
                values->channel_start = atoi (optarg);
                args_found |= cChannelStart;
                break;
            case 2:
                CheckChar(option_index, optarg);
                values->channel_end = atoi (optarg);
                args_found |= cChannelEnd;
                break;
            case 3:
                values->path_preset.assign(optarg);
                args_found |= cPresetsPath;
                break;
            case 4:
                CheckChar(option_index, optarg);
                Extract_List(optarg, values);
                args_found |= cAddressList;
                break;
            default:
                cout << "Invalid option index " << option_index << " with arg "<< optarg << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
    if ((args_found | cPresetsPath) != (cPort | cChannelStart | cChannelEnd | cPresetsPath | cAddressList))
    {
        cout << "usage: " << argv[0] << " --port=x --channel_start=x --channel_end=x --path_preset=x --list_addresses=x,y,z,..." << endl;
        args_found = ~args_found & 31;
        if ((args_found & cPort) > 0)
        {
            cout << "port missed" << endl;
        }
        if ((args_found & cChannelStart) > 0)
        {
            cout << "channel_start missed" << endl;
        }
        if ((args_found & cChannelEnd) > 0)
        {
            cout << "channel_end missed" << endl;
        }
        if ((args_found & cPresetsPath) > 0)
        {
            cout << "path_preset missed" << endl;
        }
        if ((args_found & cAddressList) > 0)
        {
            cout << "list_addresses missed" << endl;
        }
        exit(EXIT_FAILURE);
    }
    
    cout << "IC addresses extracted: ";
    for (unsigned int i = 0; i < values->list_addresses.size(); i++)
    {
        cout << values->list_addresses[i];
        if (i + 1 < values->list_addresses.size())
        {
            cout << ", ";
        }
    }
    cout << endl;
}