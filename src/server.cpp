#include <iostream>

#include "server.hpp"
#include "../lib104/iec60870_slave.h"
#include "../lib104/hal_time.h"
using namespace json_spirit;
using namespace std;

/************************ C FUNCTION DECLARATION **************************
static ClockSynchronizationHandler clockSynchandler(void* parameter, MasterConnection connection, ASDU asdu, CP56Time2a newTime);

static ConnectionRequestHandler connectionHandler(void* parameter, const char* ipAddress);

static InterrogationHandler interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi);

static ASDUHandler asduHandler(void* parameter, MasterConnection connection, ASDU asdu);

ConnectionParameters connectionParameters;
************************ SERVER FUNCTION DEFINITION **********************/

/* constructor */
serverz::serverz(){}

serverz::~serverz(){}
/* start the server*/

void serverz::Start(){

	std::cout << (typeid(slave)==typeid(Slave)) << std::endl;

	Slave_start(this->slave);
	

	if (!Slave_isRunning(slave)){

		std::cout << "error" << std::endl;
	}
	else {
	std::cout << "server started" << std::endl;
	};
}

void serverz::initial(const char* file_name){
       ifstream is(file_name);
       Value val;
       std::cout << "here" << std::endl;
       read(is, val); //read the json file to the value
       Object obj = val.get_obj();
       std::string ip;
       int port, highlimit, lowlimit;
       uint32_t size;

    for(Object::size_type i = 0; i != obj.size(); ++i) {   
        const Pair& pair = obj[i];
        const string& name  = pair.name_;
        const Value&  value = pair.value_;
	std::cout << "1st for" << std::endl;
	Object network, asduz;	
	if( name == "network" ) {
		std::cout << "in network if" << std::endl;
		network = value.get_obj();
		for(Object::size_type l = 0; l != network.size(); ++l) {   
			std::cout << "2nd for" << std::endl;
			const Pair& pair1 = network[l];
		        const string& name1  = pair1.name_;
		        const Value&  value1 = pair1.value_;
		        if( name1 == "ip" ){
				std::cout << "getting ip" << std::endl;
			       	ip  = value1.get_str();
				std::cout << ip << std::endl;
			}
			
			else if( name1 == "port" ) port = value1.get_int();
			else if( name1 == "highlimit"){
			       	highlimit = value1.get_int();
				std::cout <<highlimit << std::endl;
			}
			else {
				std::cout << "no highlimit" << std::endl;
			};
			if( name1 == "lowlimit") lowlimit = value1.get_int();
			std::cout << lowlimit << std::endl;
	}; 
	}
	else if ( name == "asduz") {
		std::cout << "i'm in asduz" << std::endl;
		asduz = value.get_obj();
		for(Object::size_type m = 0; m != asduz.size(); ++m) {
			const Pair& pair2 = asduz[m];
			const string& name2 = pair2.name_;
			const Value& value2 = pair2.value_;
			if(name2 == "type") {
				int type = value2.get_int();
				
				std::cout<<"here is type"<<type<<std::endl;
				}
			else {
				std::cout << "no type" << std::endl;
			}
		};
		
    }
	else {
		std::cout << "no asduz" << std::endl;
	};

	const char* ipAddress = ip.c_str();
	slave=T104Slave_create(nullptr, lowlimit, highlimit);
	T104Slave_setLocalAddress(slave, ipAddress);
	std::cout << "Initialized"<<highlimit<< std::endl;;

}

}

void serverz::setHandlers(ClockSynchronizationHandler clockSynchandler, InterrogationHandler interrogationHandler, ASDUHandler asduHandler, ConnectionRequestHandler connectionHandler){

	Slave_setClockSyncHandler(slave, (ClockSynchronizationHandler) clockSynchandler, nullptr);
	std::cout<< "clock handler set "<< std::endl;
//	connectionParameters= Slave_getConnectionParameters(slave);
	
	Slave_setInterrogationHandler(slave, (InterrogationHandler) interrogationHandler, nullptr);
	std::cout<< "interro handler set "<< std::endl;
	Slave_setASDUHandler(slave, (ASDUHandler) asduHandler, nullptr);

	T104Slave_setConnectionRequestHandler(slave, (ConnectionRequestHandler) connectionHandler, nullptr);
	std::cout << "connection handler set" << std::endl;
}

/*void serverz::setConnection(ConnectionRequestHandler connectionHandler){
}

ClockSynchronizationHandler clockSynchandler(void* parameter, MasterConnection connection, ASDU asdu, 
		CP56Time2a newTime ){
		std::cout << CP56Time2a_getHour(newTime)
		<< ":" << CP56Time2a_getMinute(newTime)
		<< ":" << CP56Time2a_getSecond(newTime)
		<< " " << CP56Time2a_getDayOfMonth(newTime)
		<< ":" << CP56Time2a_getMonth(newTime) 
		<< ":" << CP56Time2a_getYear(newTime) + 2000
		<< std::endl;
}


ConnectionRequestHandler connectionHandler(void* parameter, const char* ipAddress)
{
	std::cout << "Connected to: " << ipAddress << std::endl;

}

ASDUHandler asduHandler(void* parameter, MasterConnection connection, ASDU asdu){
	std::cout << "asdu" << std::endl;
}

InterrogationHandler interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi) {

    struct sCP56Time2a timestamp;

    CP56Time2a_createFromMsTimestamp(&timestamp, Hal_getTimeInMs());

    MasterConnection_sendACT_CON(connection, asdu, false);

    ASDU newAsdu = ASDU_create(connectionParameters, M_ME_NB_1, false, INTERROGATED_BY_STATION,
            0, 1, false, false);

    InformationObject io = (InformationObject) MeasuredValueScaled_create(NULL, 100, -1, IEC60870_QUALITY_GOOD);

    ASDU_addInformationObject(newAsdu, io);

    ASDU_addInformationObject(newAsdu, (InformationObject)
		MeasuredValueScaled_create((MeasuredValueScaled) io, 101, 23, IEC60870_QUALITY_GOOD));

    ASDU_addInformationObject(newAsdu, (InformationObject)
		MeasuredValueScaled_create((MeasuredValueScaled) io, 102, 2300, IEC60870_QUALITY_GOOD));

    InformationObject_destroy(io);

    MasterConnection_sendASDU(connection, newAsdu);

    newAsdu = ASDU_create(connectionParameters, M_SP_TB_1, false, INTERROGATED_BY_STATION,
                0, 1, false, false);

    io = (InformationObject) SinglePointWithCP56Time2a_create(NULL, 104, true, IEC60870_QUALITY_GOOD, &timestamp);

    ASDU_addInformationObject(newAsdu, io);

    ASDU_addInformationObject(newAsdu, (InformationObject)
		SinglePointWithCP56Time2a_create((SinglePointWithCP56Time2a) io, 105, false, IEC60870_QUALITY_GOOD, &timestamp));

    InformationObject_destroy(io);

    MasterConnection_sendASDU(connection, newAsdu);


    newAsdu = ASDU_create(connectionParameters, M_IT_TB_1, false, INTERROGATED_BY_STATION,
                0, 1, false, false);

    BinaryCounterReading bcr = BinaryCounterReading_create(NULL, 12345678, 0, false, false, true);

    io = (InformationObject) IntegratedTotalsWithCP56Time2a_create(NULL, 200, bcr, &timestamp);

    ASDU_addInformationObject(newAsdu, io);

    BinaryCounterReading_destroy(bcr);

    InformationObject_destroy(io);

    MasterConnection_sendASDU(connection, newAsdu);

    newAsdu = ASDU_create(connectionParameters, M_SP_NA_1, true, INTERROGATED_BY_STATION,
            0, 1, false, false);

    ASDU_addInformationObject(newAsdu, io = (InformationObject) SinglePointInformation_create(NULL, 300, true, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 301, false, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 302, true, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 303, false, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 304, true, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 305, false, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 306, true, IEC60870_QUALITY_GOOD));
    ASDU_addInformationObject(newAsdu, (InformationObject) SinglePointInformation_create((SinglePointInformation) io, 307, false, IEC60870_QUALITY_GOOD));

    InformationObject_destroy(io);

    MasterConnection_sendASDU(connection, newAsdu);

    MasterConnection_sendACT_TERM(connection, asdu);


}
*/

