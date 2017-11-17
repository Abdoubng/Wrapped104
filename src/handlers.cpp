#include "handlers.hpp"
using namespace std;
using namespace json_spirit;

struct AsduConf
{
    int type_;
    int cot_;
    int ioa_;
    int value_;
    int quality_;
};
IEC60870_5_TypeID asduz[2]={M_ME_NB_1,
       			   M_SP_NA_1
			  };
ConnectionParameters connectionParameters;
handlers::handlers(){}

handlers::~handlers(){}
AsduConf read_configuration( const Object& obj ){
    AsduConf conf;

    for( Object::size_type i = 0; i != obj.size(); ++i )
    {
        const Pair& pair = obj[i];

        const string& name  = pair.name_;
        const Value&  value = pair.value_;

        if( name == "type" )
        {
            conf.type_ = value.get_int();
	    std::cout << conf.type_ << std::endl;
//            std::cout << M_SP_NA_1 << std::endl;
//	    std::cout << asduz[conf.type_] << std::endl;
	}
        else if( name == "ioa" )
        {
        	conf.ioa_ = value.get_int();
        }
        else if( name == "value" )
        {
       		conf.value_ = value.get_int();
	
        }
        else if( name == "quality" )
        {
        	conf.quality_ = value.get_int();
        }
        else
        {
        	assert( false );
        }
    }

    return conf;
}
vector< AsduConf > read_config( const char* file_name)
{
    ifstream is( file_name );

    Value value;

    read( is, value );

    const Array& addr_array = value.get_array();

    vector< AsduConf > conf;

    for( unsigned int i = 0; i < addr_array.size(); ++i )
    {
        conf.push_back( read_configuration( addr_array[i].get_obj() ) );
    }

    return conf;
}
/*** Get Connection Parameters **/
bool handlers::getConnectionParameters(Slave slave) {
	connectionParameters = Slave_getConnectionParameters(slave);
	return true;
}

/*** Interrogation Handler ***/
InterrogationHandler handlers::interrogationHandler(void* parameter, MasterConnection connection, ASDU asdu, uint8_t qoi) {
	std::cout<< "interro for groupe " << std::endl;
	const char* file_name("config.json");

	std::vector< AsduConf > new_conf = read_config(file_name) ;
	/*
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
*/
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
	std::cout << CP56Time2a_getHour(newTime)
	<< ":" << CP56Time2a_getMinute(newTime)
	<< ":" << CP56Time2a_getSecond(newTime)
	<< " " << CP56Time2a_getDayOfMonth(newTime)
	<< ":" << CP56Time2a_getMonth(newTime)
	<< ":" << CP56Time2a_getYear(newTime) + 2000 
	<< std::endl;
}

