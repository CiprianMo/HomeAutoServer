default:
	$(CXX) -g -Wall -std=c++11 webSocketServer.cpp -Isrc -o webSocketServer -lpthread -luWS -lssl -lcrypto -lz -luv
