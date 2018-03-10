#include<iostream>
#include<string>
#include<unordered_map>
#include<bcm2835.h>
#include"speech.h"
#include<vector>
#include<iterator>
#include<sstream>
enum class Pin : std::uint8_t
{
        Lamp = 21,
        Fan = 20,
        High = 19,
        Iron = 26,
};

std::unordered_map<std::string,void(*)(uint8_t)> operations = 
        {
                {"ON", &bcm2835_gpio_clr},
                {"OFF", &bcm2835_gpio_set}
        };

std::unordered_map<std::string,Pin> Pins =
        {
                {"FAN",Pin::Fan},
                {"LAMP",Pin::Lamp},
                {"HIGH",Pin::High},
                {"IRON",Pin::Iron}
        };
template<typename Out>
void split(const std::string& s, char delim,Out result)
{
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while(std::getline(ss,item,delim))
        {
                *(result++) = item;
        }
}

std::vector<std::string> split(const std::string& data,char delim)
{
        std::vector<std::string> elements;
        split(data, delim, std::back_inserter(elements));
        return elements;
}

int main()
{

    if(!bcm2835_init()) return 1;
   
    Speech speech("");
    
    while(true)
    {
            auto data = speech.contin_recog();
            if(data != "")
            {
                    std::cout << data<<std::endl;

                    auto elements = split(data,' ');
                    for (auto element : elements)
                    {
                            auto itr = Pins.find(element);
                            if(itr != Pins.end())
                            {
                                    auto pin = itr->second;
                                    for(auto e : elements)
                                    {
                                            auto it = operations.find(e);
                                            if(it != operations.end())
                                            {
                                                    auto operation = it->second;
                                                    operation((uint8_t)pin);
                                            }
                                    }
                            }
                    }
            }
    }
}
