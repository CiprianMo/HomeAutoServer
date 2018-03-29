#include<uWS/uWS.h>
#include<bcm2835.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstdint>
#include<curl/curl.h>
using namespace std;

CURL *curl;
CURLcode res;
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

size_t write_data(char* data, size_t size, size_t nmemb, std::string* str) {
        if(!str)
        {
                return 0;
        }
        str->append(data, size*nmemb); 
        return size * nmemb;
}

void GetUpdates()
{
        std::cout <<"Getting updates"<<std::endl;
        std::string buffer;
        curl_easy_setopt(curl,CURLOPT_URL,"10.0.0.68/R");
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << "CURL: " <<buffer<<std::endl;
        
}

void get_pin_status(string& status)
{
        //ostringstream stringStream;
        //stringStream << "Fan "<<unsigned(fan)<<",Lamp "<<unsigned(lamp)<<",High "<<unsigned(high)<<",Iron "<<unsigned(iron);
        status="To be a string ";
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
                std::cout <<dt<<std::endl;
                if(dt.find(" the ") != std::string::npos)
                {
                        urlParameters = dt.substr(dt.find("?")+6);
                }else
                        urlParameters = dt.substr(dt.find("?")+1);        
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
        uWS::Hub h;
        
        

        curl = curl_easy_init();

        if(!curl) return 1;
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
                            GetUpdates();
                            cout << "The message is "<<data.substr(0,length) <<endl;
                            }
                        });

      if(h.listen(3000)){
            h.run(); 
        }
}

