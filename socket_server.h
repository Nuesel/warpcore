#include <boost/thread.hpp>
#include <string>
#include "presets.h"
#include "running_leds.h"
#include "json/json.h"

class socket_server {
private:
   presets* FPreset_list;
   running_leds* FRunning_LEDs;
   bool communication_stopped;
   int sockfd;
   void run_socketserver(void);
   
   void start_server (int portno);
public:
    socket_server(int port, presets* Preset_list, running_leds* Running_LEDs);
    ~socket_server(void);
	
    boost::thread *tcp_server;
};
