#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include<string>

using namespace std;

class GPIOClass
{
        public:
                GPIOClass();
                GPIOClass(string x);

                int export_gpio();
                int unexport_gpio();
                int setdir_gpio(string dir);
                int setval_gpio(string val);
                int getval_gpio(string& val);
                string get_gpionum();

        private:
                string gpionum;

};

#endif
