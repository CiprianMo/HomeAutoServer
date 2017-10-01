#include<iostream>
#include"speech.h"
#include<string>
int main(int argc, char* argv[])
{
        Speech speech("");
        while(1)
        {
        auto data = speech.contin_recog();
        
        if(data !="")
            std::cout << "phrase is "<<data<<std::endl;
        }
        return 0;
}
