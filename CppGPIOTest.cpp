#include<cppgpio.hpp>
#include<chrono>
#include<iostream>

using namespace GPIO;
using namespace std;
int main()
{
       //j DigitalOut out(20);
        GPIOBase base;
        DigitalOut fan(21);
        fan.off();
        base.mode(21,GPIO_MODE::GPIO_OUTPUT);
       // base.set(21); 
        cout << "pin status is "<<base.read(21) <<endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        
        //out.off();

        return 0;
}

