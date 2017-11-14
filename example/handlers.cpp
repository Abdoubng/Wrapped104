#include "handlers.hpp"

handlers::handlers(){}

/*** Interrogation Handler ***/
InterrogationHandler handlers::interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi) {
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



}


/*** Connection Request Handler ***/
ConnectionRequestHandler handlers::connectionHandler(void* parameter, const char* ipAddress)
{
	std::cout << "Connected to: " << ipAddress << std::endl;

}


/*** ASDU Handler ***/
ASDUHandler handlers::asduHandler(void* parameter, MasterConnection connection, ASDU asdu){
	std::cout << "asdu" << std::endl;
}



/*** Clock Synchronization Handler ***/
ClockSynchronizationHandler handlers::clockSynchandler(void* parameter, MasterConnection connection, ASDU asdun, CP56Time2a newTime){
std::cout << ":" << CP56Time2a_getHour(newTime)
<< ":" << CP56Time2a_getMinute(newTime)
<< ":" << CP56Time2a_getSecond(newTime)
<< ":" << CP56Time2a_getDayOfMonth(newTime)
<< ":" << CP56Time2a_getMinute(newTime)
<< ":" << CP56Time2a_getYear(newTime) + 200 
<< std::endl;
}
handlers::~handlers(){}
