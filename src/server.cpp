#include "server.hpp"
//#include "handlers.hpp"
#include <iostream>
#include "../lib104/iec60870_slave.h"
#include "../lib104/hal_time.h"

/************************ C FUNCTION DECLARATION **************************/
static ClockSynchronizationHandler clockSynchandler(void* parameter, MasterConnection connection, ASDU asdu, CP56Time2a newTime);

static ConnectionRequestHandler connectionHandler(void* parameter, const char* ipAddress);

static InterrogationHandler interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi);

static ASDUHandler asduHandler(void* parameter, MasterConnection connection, ASDU asdu);

ConnectionParameters connectionParameters;
/************************ SERVER FUNCTION DEFINITION **********************/

/* constructor */
serverz::serverz(){}

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

void serverz::initial(int Arg1, int Arg2){
     
        slave= T104Slave_create(nullptr, Arg1, Arg2);
   	T104Slave_setLocalAddress(slave, "0.0.0.0");
	std::cout << "initialized" << std::endl;

}

void serverz::setHandlers(){
	Slave_setClockSyncHandler(slave, (ClockSynchronizationHandler) handlers.clockSynchandler, nullptr);
	std::cout<< "interro handler set "<< std::endl;
	connectionParameters= Slave_getConnectionParameters(slave);
	
	Slave_setInterrogationHandler(slave, (InterrogationHandler) handlers.interrogationHandler, nullptr);
	Slave_setASDUHandler(slave, (ASDUHandler) handlers.asduHandler, nullptr);



}
void serverz::setConnection(){
	T104Slave_setConnectionRequestHandler(slave, (ConnectionRequestHandler) handlers.connectionHandler, nullptr);
	std::cout << "connection handler set" << std::endl;
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
	std::cout<< "interro for groupe " << std::endl;


   ASDU newAsdu = ASDU_create(connectionParameters, M_SP_NA_1, true, INTERROGATED_BY_STATION,
            0, 1, false, false);
    InformationObject io = (InformationObject) SinglePointInformation_create(nullptr, 300, true, IEC60870_QUALITY_GOOD);
    ASDU_addInformationObject(newAsdu, io);
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



    struct sCP56Time2a timestamp;

    CP56Time2a_createFromMsTimestamp(&timestamp, Hal_getTimeInMs());

    MasterConnection_sendACT_CON(connection, asdu, false);

    newAsdu = ASDU_create(connectionParameters, M_ME_NB_1, false, INTERROGATED_BY_STATION,
            0, 1, false, false);

    io = (InformationObject) MeasuredValueScaled_create(NULL, 100, -1, IEC60870_QUALITY_GOOD);

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


serverz::~serverz(){}
