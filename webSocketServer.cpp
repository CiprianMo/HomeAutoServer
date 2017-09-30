#include<uWS/uWS.h>
#include<bcm2835.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstdint>
using namespace std;

enum class Pin : std::uint8_t
{
        Lamp = 21,
        Fan = 20,
        High = 26,
        Iron = 19
};

struct Command 
{
        string item;
        char* operation;
};

void get_pin_status(string& status)
{
        auto fan = bcm2835_gpio_lev((uint8_t)Pin::Fan);
        auto lamp = bcm2835_gpio_lev((uint8_t)Pin::Lamp);
        auto high = bcm2835_gpio_lev((uint8_t)Pin::High);
        auto iron = bcm2835_gpio_lev((uint8_t)Pin::Iron);
        ostringstream stringStream;
        stringStream << "Fan "<<unsigned(fan)<<",Lamp "<<unsigned(lamp)<<",High "<<unsigned(high)<<",Iron "<<unsigned(iron);
        status=stringStream.str();
}

string getRequestFile(string fileName)
{
        string fname = fileName=="/"?"index.html":&fileName[1];
        ifstream file(fname,ios::in| ios::binary);

        if(file)
        {
                 std::ostringstream ss{};
                 ss<<file.rdbuf();
                 file.close();
                 return ss.str();
         }
         throw(errno);

}

int main()
{
        if(!bcm2835_init()) return 1;
        uWS::Hub h;

        h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
                        {
                            cout << "Connected to a client" << endl;
                            string status ="";
                            get_pin_status(status);
                            cout << "the string is "<<status.size()<<" "<<status<<endl;
                            ws->send(status.c_str(),status.size(),uWS::OpCode::TEXT); 
                            });
        h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data,size_t length, size_t remainingBytes)
                        {
                            cout << "Requesting "<<req.getUrl().toString()<<endl;
                            });
                            uWS::Header url = req.getUrl();
                            auto buffer = getRequestFile(url.toString());
                            res->end(&buffer[0],buffer.size());
                            });
        h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode)
                        {
                        if(message != NULL)
                        {
                            string data(message);
                            cout << "The message is"<<data.substr(0,length) <<endl;
                            }
                        });

        h.listen(3000);
        h.run();
}

