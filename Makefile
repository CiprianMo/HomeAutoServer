default:
	$(CXX) -g -Wall -std=c++11 src/webSocketServer.cpp -Isrc -o webSocketServer -lpthread -luWS -lssl -lcrypto -lz -luv -lbcm2835 -lcurl
