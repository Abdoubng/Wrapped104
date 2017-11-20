/**
 * @file JsonFileReader.h
 * @author calligp
 * @date 08/03/2015
 * @brief File Json reader
 * @details File Json reader
 */

#ifndef SRC_UTILITIESMODULE_JSONFILEREADER_H_
#define SRC_UTILITIESMODULE_JSONFILEREADER_H_

//System includes
#include <list>
#include <fstream>
#include <iostream>
//Libraries includes
#include <json_spirit_reader_template.h>
//Application includes
#include "LoggerManager.h"

namespace UtilitiesModule
{
    class JsonFileReader
    {
    public:
        /**
         * @brief Constructor.
         */
        JsonFileReader(void);
        /**
         * @brief Destructor.
         */
        virtual ~JsonFileReader(void);
        /**
         * @brief Parse file to extract log level and module list name.
         * @param aConfigPath The path to the configuration path.
         * @param aLogLevel
         * @param aModuleList
         */
        bool RetrieveConfiguration(std::string& aConfigPath, std::string& aLogLevel, std::list<std::string>& aModuleList);
    };
}

#endif // SRC_UTILITIESMODULE_JSONFILEREADER_H_
