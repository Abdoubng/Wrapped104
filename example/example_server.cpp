#include "unistd.h"

#include "server.hpp"
#include "../lib104/iec60870_slave.h"
using namespace std;
int main(){
	serverz myserver;
	handlers myhandlers;
	std::cout << "my server instanciated" << std::endl;

	myserver.initial(100, 102);

	std::cout << "slave created" << std::endl;
//	usleep(3000000);
	myserver.setHandlers((ClockSynchronizationHandler) myhandlers.clockSynchandler, (InterrogationHandler) myhandlers.interrogationHandler, (ASDUHandler) myhandlers.asduHandler);
	myserver.setConnection((ConnectionRequestHandler) myhandlers.connectionHandler);
	myserver.Start();	
	std::cout << myserver.slave << std::endl;	

	

	
	
while (true){
	sleep(3);
	
	};
}

