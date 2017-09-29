#include<iostream>
#include<bcm2835.h>
using namespace std;
int main ()
{
        if(!bcm2835_init())
                return 1;
        bcm2835_gpio_fsel(21,BCM2835_GPIO_FSEL_OUTP);
                auto v = bcm2835_gpio_lev(21);
                cout<<"pin is "<<unsigned(v)<<endl;
}
