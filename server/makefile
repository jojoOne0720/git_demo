CC = g++

server: main.cpp buffer.o connectObj.o network.o networkBuffer.o networkListen.o recvNetworkBuffer.o serverMgr.o
	g++ main.cpp buffer.o connectObj.o network.o networkBuffer.o networkListen.o recvNetworkBuffer.o serverMgr.o -o server1.0

buffer: buffer.cpp
	g++ -c buffer.cpp 

connectObj: connectObj.cpp
	g++ -c connectObj.cpp

network: network.cpp
	g++ -c network.cpp

networkBuffer: networkBuffer.cpp
	g++ -c networkBuffer.cpp

networkListen: networkListen.cpp
	g++ -c networkListen.cpp

recvNetworkBuffer: recvNetworkBuffer.cpp
	g++ -c recvNetworkBuffer.cpp

serverMgr: serverMgr.cpp
	g++ -c serverMgr.cpp

clean:
	rm *.o 