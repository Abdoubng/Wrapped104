#include "../lib104/iec60870_slave.h"
#include "../json_spirit/json_spirit.h"
#include <iostream>
#include <cassert>
#include <fstream>


class handlers{
	public :
		handlers();
		
		/*** Handlers functions ***/
		static InterrogationHandler interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi);
		static ASDUHandler asduHandler(void* parameter, MasterConnection connection, ASDU asdu);
		static ConnectionRequestHandler connectionHandler(void* parameter, const char* ipAddress);
		static ClockSynchronizationHandler clockSynchandler(void* parameter, MasterConnection connection, ASDU asdu, CP56Time2a newTime);
		bool getConnectionParameters(Slave slave);
		/*** Handlers parameters ***/
//		ConnectionParameters connectionParameters;
		void jzon();	
		ASDU asdu;
		~handlers();
					
};

