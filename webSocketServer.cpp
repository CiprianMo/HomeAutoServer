#include<uWS/uWS.h>
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

void get_pin_status(&string)
{
        uint8_t fan = bcm2835_gpio_lev(Fan);
        uint8_t lamp = bcm2835_gpio_lev(Lamp);
        uint8_t high = bcm2835_gpio_lev(High);
        uint8_t iron = bcm2835_gpio_lev(Iron);
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
        uWS::Hub h;

        h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
                        {
                            cout << "Connected to a client" << endl;
                            });
        h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data,size_t length, size_t remainingBytes)
                        {
                            uWS::Header url = req.getUrl();
                            auto buffer = getRequestFile(url.toString());
                            res->end(&buffer[0],buffer.size());
                            });
        h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode)
                        {
                        if(message != NULL)
                            cout << "The message is"<<string(message) <<endl;

                        });

        h.listen(3000);
        h.run();
}

