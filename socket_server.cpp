#include "socket_server.h"
#include "general.h"
#include <netinet/in.h>

using namespace std;

void print_error(const char *msg)
{
    perror(msg);
}

void socket_server::run_socketserver (void)
{
	const int buffer_size = 256;
    socklen_t clilen;
    int newsockfd;
    char buffer[buffer_size];
    struct sockaddr_in cli_addr;
    int n;
	Json::Reader reader;
	Json::Value Received_Data;
	Json::Value Commands;
	Json::Value Answer;
	bool parsingSuccessful = false;
    
    communication_stopped = false;
    clilen = sizeof(cli_addr);
    std::string text_str, tcp_message;
	while(FRunning_LEDs->GetExit() == false)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            print_error("ERROR on accept");
        }
		tcp_message.clear();
		Received_Data.clear();
		
		do
		{
			bzero(buffer,buffer_size);
			n = read(newsockfd,buffer,buffer_size);
			if (n < 0)
			{
			   print_error("ERROR reading from socket");
			}
			tcp_message = tcp_message.append(buffer, n);
		} while (strlen(buffer) >= buffer_size);
		
		Received_Data.clear();
		parsingSuccessful = reader.parse(tcp_message, Received_Data, true);
		if (Received_Data.size() > 0 && parsingSuccessful == true)
		{
			Commands.clear();
			Answer.clear();
			//reader.parse(tcp_message, Received_Data, true);
			FPreset_list->update_data(Received_Data["presets"]);
			Commands = Received_Data["commands"];
			cout << "Commands: " << Commands << endl;
			text_str.clear();
			Answer = FRunning_LEDs->AnalyzeCmd(Commands);
			
			text_str = Answer.toStyledString() + (char)NULL;
			cout << "Answer: " << text_str << "Länge: "<< text_str.length() << endl;
			n = write(newsockfd,text_str.c_str(),text_str.length());
			if (n < 0)
			{
			   print_error("ERROR writing to socket");
			}
			close(newsockfd);
		}
	}
    communication_stopped = true;
}

void socket_server::start_server(int portno)
{
    struct sockaddr_in serv_addr;
    
    communication_stopped = true;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        print_error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        print_error("ERROR on binding");
    }
    listen(sockfd,5);
}

socket_server::socket_server(int port, presets* Preset_list, running_leds* Running_LEDs)
{
	FRunning_LEDs = Running_LEDs;
	FPreset_list = Preset_list;
	
    start_server(port);
    tcp_server = new boost::thread(&socket_server::run_socketserver, this);
}

socket_server::~socket_server (void)
{
    tcp_server->join();
    
    close(sockfd);
}