//To compile this project:
//g++ commandline.cpp general.cpp gpio.cpp ./jsoncpp.cpp program.cpp pca9685.cpp socket_server.cpp presets.cpp running_leds.cpp warpkern_rings.cpp -o program -lwiringPi -lboost_thread-mt -lboost_system

#include <sys/resource.h> //For setpriority/ setting niceness
#include "general.h"
#include "program.h"
#include "socket_server.h"
#include "commandline.h"
#include "gpio.h"
#include "running_leds.h"
#include "json/json.h"

extern unsigned long int starttime;

int main (int argc, char *argv[])
{
    //usage: ./program --channel_start=0 --channel_end=59 --port=54321 --list_addresses=0x4C,0x4D,0x4E,0x4F --path_preset=/usbstick/warpkern2/presets.json &
    
	bool shutdown_flag = false;
    led_stripe* Lled_stripes = NULL;
    presets* preset_list = NULL;
    option_values arguments;
    socket_server* tcp_server = NULL;
    running_leds* running_ledstrips = NULL;
	Json::Value commands;
    
    starttime = myGetTickCount();
    
    commandline_options(argc, argv, &arguments);
  
    DEBUG_MSG("Set Nice-Value to -16");
    setpriority(0, 0, -16);
    
    init_wiringpi();
    
    //setup access to GPIO pins
    init_gpio();
    
	//Set Active Enable
    enable_ics();
	
    Lled_stripes = new led_stripe (arguments.channel_start, arguments.channel_end, arguments.list_addresses);
    preset_list = new presets(Lled_stripes->GetRingCount(), arguments.path_preset);
    preset_list->read_file(&commands);
    
    running_ledstrips = new running_leds(Lled_stripes, preset_list);
    running_ledstrips->AnalyzeCmd(commands);
    tcp_server = new socket_server(arguments.port, preset_list, running_ledstrips);

    while (running_ledstrips->GetExit() == false)
    {
        //sleep for 100ms
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
    
	shutdown_flag = running_ledstrips->GetShutdown();
    running_ledstrips->ledthread->join();
    tcp_server->tcp_server->join();
	
    delete tcp_server;
    delete running_ledstrips;
    
    //Set Active Disable
    disable_ics();
    
    delete Lled_stripes;
    
	cout << "Exiting..." << endl;
	if (shutdown_flag == true)
	{
		cout << "Shutdown..." << endl;
		std::system("shutdown -h now");
	}
    return 0;
}

