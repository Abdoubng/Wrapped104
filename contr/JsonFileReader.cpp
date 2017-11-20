/**
 * @file JsonFileReader.cpp
 * @author calligp
 * @date 08/03/2015
 * @brief File Json reader
 * @details File Json reader
 */

//System includes
//Libraries includes
//Application includes
#include "JsonFileReader.h"

namespace UtilitiesModule
{

    JsonFileReader::JsonFileReader(void)
    {
    }

    /*virtual */JsonFileReader::~JsonFileReader(void)
    {
    }

    bool JsonFileReader::RetrieveConfiguration(std::string& aConfigPath, std::string& aLogLevel, std::list<std::string>& aModuleList)
    {
        std::ifstream wStream(aConfigPath.c_str(), std::ifstream::in);
        json_spirit::mValue wValue;
        bool wReturn = false;
        bool wLevelFound = false;
        bool wModulesFound = false;

        try
        {
            json_spirit::read_stream(wStream, wValue);

            json_spirit::mObject& wConfig = wValue.get_obj();
            json_spirit::mObject::iterator wIterator;
            json_spirit::mArray wModuleList;
            json_spirit::mArray::iterator wModuleIterator;

            for (wIterator = wConfig.begin(); wIterator != wConfig.end(); ++wIterator)
            {
                if (wIterator->first.compare("level") == 0)
                {
                    wLevelFound = true;
                    aLogLevel = wIterator->second.get_str();
                }
                else if (wIterator->first.compare("modules") == 0)
                {
                    wModuleList = wIterator->second.get_array();
                    for (wModuleIterator = wModuleList.begin(); wModuleIterator != wModuleList.end(); ++wModuleIterator)
                    {
                        wModulesFound = true;
                        aModuleList.push_back(wModuleIterator->get_str().c_str());
                    }
                }
            }
        }
        catch( const std::exception& arException )
        {
            LOG_ERROR_MESSAGE(LoggingModule::LoggerManager::eLogModuleType::LOG_UTILITIES_MODULE, "Unable to read configuration");
        }

        if (true == wLevelFound && true == wModulesFound)
        {
            wReturn = true;
        }
        else
        {
            aLogLevel = "error";
            aModuleList.clear();
            aModuleList.push_back("all");
        }

        return wReturn;
    }
}
