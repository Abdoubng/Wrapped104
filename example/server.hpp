#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <typeinfo>
#include "../lib104/iec60870_slave.h"
#include "handlers.hpp"

class serverz {
	public:
			serverz();
			int arg1, arg2;

			void initial(int arg1, int arg2);
                        void Start();
                        void setHandlers(ClockSynchronizationHandler clockSynchandler, InterrogationHandler interrogationHandler, ASDUHandler asduHandler);
			ConnectionParameters connectionParameters;   
			void setConnection(ConnectionRequestHandler connectionHandler);
			Slave slave;
			ASDU newAsdu;
			InformationObject io;
			~serverz();

	private:
		
};
#endif
