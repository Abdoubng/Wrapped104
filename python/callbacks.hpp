#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "../src/inc/api/iec60870_slave.h"


class Server {
	public:
			Server();
                        void init(this, int arg1,int arg2);
//                        void Start();
                        
//                        void setHandlers();
			~Server();		       	
	private: 
			int arg1, arg2;
			static ConnectionParameters connectionParameters;

};
       
#endif










