#include <uWS/uWS.h>
#include <iostream>

using namespace std;

int main()
{
    uWS::Hub h;
    
    h.onConnection([&h](uWS::WebSocket<uWS::SERVER>* ws, uWS::HttpRequest req)
                   {
                      cout << "Connected to a client"<< endl;
                   });

    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        ws->send(message, length, opCode);
        cout << "the message is " << message<<endl;
    });

    h.listen(3000);
    h.run();
}
