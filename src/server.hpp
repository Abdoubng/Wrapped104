#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <typeinfo>
#include "../lib104/iec60870_slave.h"
//}

class serverz {
	public:
			serverz();
			int arg1, arg2;

			void initial(int arg1, int arg2);
                        void Start();
                        void setHandlers();
//			ConnectionParameters connectionParameters;   
			void setConnection();			
			Slave slave;
			ASDU newAsdu;
			InformationObject io;
			~serverz();

	private:
		
};
#endif
