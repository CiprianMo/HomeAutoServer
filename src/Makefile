default:
	$(CXX) -g -Wall -O0 -o HomeAutoServer HomeAutoServer.cpp speech.cpp -I/usr/local/include -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx -I/usr/local/include -I/usr/local/include/sphinxbase -L/usr/local/lib -lpocketsphinx -lsphinxbase -lsphinxad -lasound -lpthread -lm  -std=c++11 -lbcm2835

test:
	$(CXX) -g -Wall -O0 -o speechTest speechTest.cpp speech.cpp -I/usr/local/include -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx -I/usr/local/include -I/usr/local/include/sphinxbase -L/usr/local/lib -lpocketsphinx -lsphinxbase -lsphinxad -lasound -lpthread -lm  -std=c++11 -fno-inline



