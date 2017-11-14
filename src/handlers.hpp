
#include "../lib104/iec60870_slave.h"
#include <iostream>






class handlers{
			public :
				handlers(){};
static InterrogationHandler interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi){}
static ASDUHandler asduHandler(void* parameter, MasterConnection connection, ASDU asdu);
static ConnectionRequestHandler connectionHandler(void* parameter, const char* ipAddress);
static ClockSynchronizationHandler clockSynchandler(void* parameter, MasterConnection connection, ASDU asdu, CP56Time2a newTime);
ConnectionParameters connectionParameters;
InformationObject io;
ASDU asdu;
ASDU newAsdu;
~handlers(){};
}

