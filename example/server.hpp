#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <typeinfo>
#include "../lib104/iec60870_slave.h"
#include "handlers.hpp"

class serverz {
	public:
			serverz();
			~serverz();
			int arg1, arg2;

			void initial(const char* file_name);
                        void Start();
                        void setHandlers(ClockSynchronizationHandler clockSynchandler, InterrogationHandler interrogationHandler, ASDUHandler asduHandler, ConnectionRequestHandler connectionHandler);
			Slave slave;

	private:
		
};
#endif
