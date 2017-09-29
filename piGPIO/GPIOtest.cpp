#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include"GPIOClass.h"

using namespace std;

int main(void)
{
        string inputstate;
    //  GPIOClass* gpio20 = new GPIOClass("20");
        GPIOClass* gpio21 = new GPIOClass("21");

   //   gpio20->export_gpio();
        gpio21->export_gpio();

        cout <<"GPIO pins exported"<<endl;

  //      gpio20->setdir_gpio("in");
      //  gpio21->setdir_gpio("in");

       // cout <<"GPIO pin directoins set" <<endl;
        
        gpio20->getval_gpio(inputstate);
        cout << "Lamp is: "<<inputstate<<endl;
        
        //gpio20->setval_gpio("0");
        
//        usleep(5000000);

 //       gpio21->setval_gpio("1");
        gpio21->unexport_gpio();
        return 0;
}




