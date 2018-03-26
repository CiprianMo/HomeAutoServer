#include<uWS/uWS.h>
#include<bcm2835.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstdint>
#include<curl/curl.h>
using namespace std;

enum class Pin : std::uint8_t
{
        lamp = 21,
        fan = 20,
        high = 26,
        iron = 19
};

struct Command 
{
        string item;
        char* operation;
};

void get_pin_status(string& status)
{
        auto fan = bcm2835_gpio_lev((uint8_t)Pin::fan);
        auto lamp = bcm2835_gpio_lev((uint8_t)Pin::lamp);
        auto high = bcm2835_gpio_lev((uint8_t)Pin::high);
        auto iron = bcm2835_gpio_lev((uint8_t)Pin::iron);
        ostringstream stringStream;
        stringStream << "Fan "<<unsigned(fan)<<",Lamp "<<unsigned(lamp)<<",High "<<unsigned(high)<<",Iron "<<unsigned(iron);
        status=stringStream.str();
}

void getRequestFile(string fileName,std::string& fileContent, std::string& urlParameters)
{
        int decodedLength;
        char* decoded = curl_easy_unescape(nullptr,fileName.c_str(),0,&decodedLength);
        auto dt=std::string(decoded,decodedLength);
        curl_free(decoded);
        std::string fname;
        if(dt=="/")
        {
            fname="index.html";
        }
        else
        {
                fname = dt.substr(1,dt.find("?")-1);
                urlParameters = dt.substr(dt.find("?")+6);        
                std::cout <<"url params: "<<urlParameters<<std::endl;              
        }
        ifstream file(fname,ios::in| ios::binary);

        if(file)
        {
                 std::ostringstream ss{};
                 ss<<file.rdbuf();
                 file.close();
                 fileContent= ss.str();
         } 

}

int main()
{
        if(!bcm2835_init()) return 1;
        uWS::Hub h;
        std::string urlParameters = "";
        h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
                        {
                            cout << "Connected to a client" << endl;
                            string status ="";
                            get_pin_status(status);
                            cout << "the string is "<<status.size()<<" "<<status<<endl;
                            ws->send(status.c_str(),status.size(),uWS::OpCode::TEXT); 
                            });
        h.onHttpRequest([&](uWS::HttpResponse *res, uWS::HttpRequest req, char *data,size_t length, size_t remainingBytes)
                        {
                            cout << "Requesting "<<req.getUrl().toString()<<endl;
                            
                            uWS::Header url = req.getUrl();
                            std::string buffer = "";
                            getRequestFile(url.toString(),buffer,urlParameters);
                            res->end(&buffer[0],buffer.size());
                            });
        h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode)
                        {
                        if(message != NULL)
                        {
                            string data(message);
                            cout << "The message is "<<data.substr(0,length) <<endl;
                            }
                        });

      if(h.listen(3000)){
            h.run(); 
        }
}

