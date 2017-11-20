/**
 * @file    LoggerManager.cpp
 * @author  menagec
 * @date    21 juil. 2014
 * @brief   brief
 * @details details
 */

//System includes
//Libraries includes
//Application includes
#include "LoggerManager.h"


namespace LoggingModule
{
    /*static */const std::string LoggerManager::mscAllModuleKeyword             = "all";
    /*static */const std::string LoggerManager::mscCoreModuleKeyword            = "core";
    /*static */const std::string LoggerManager::mscCommunicationModuleKeyword   = "communication";
    /*static */const std::string LoggerManager::mscEventModuleKeyword           = "event";
    /*static */const std::string LoggerManager::mscIoModuleKeyword              = "io";
    /*static */const std::string LoggerManager::mscLedModuleKeyword             = "led";
    /*static */const std::string LoggerManager::mscSupervisionModuleKeyword     = "supervision";
    /*static */const std::string LoggerManager::mscUtilitiesModuleKeyword       = "utilities";
    /*static */unsigned long LoggerManager::msModuleActivationMask = ULONG_MAX;
    /*static */Logger* LoggerManager::msLogger = NULL;
    /*static */UtilitiesModule::Osal* LoggerManager::mpOsal = NULL;


    LoggerManager::LoggerManager(std::string aLogLevel, std::list<std::string> aActiveList, UtilitiesModule::Osal* apOsal)
    {
        if (NULL != apOsal)
        {
            mpOsal = apOsal;
        }
        //  Instantiate logger
        GetLoggerInstance()->UpdateLogLevel(aLogLevel);

        // Configure logging
        NewModulesList(aActiveList);
    }

    LoggerManager::~LoggerManager()
    {
        if (NULL != msLogger)
        {
            delete msLogger;
            msLogger = NULL;
        }
    }

    /*static */Logger* LoggerManager::GetLoggerInstance(void)
    {
        if (NULL == msLogger)
        {
            msLogger = new Logger(mpOsal);
        }
        return msLogger;
    }

    void LoggerManager::NewModulesList(const std::list<std::string>& arModulesList)
    {
        msModuleActivationMask = 0;
        std::string wModuleList = "";
        for(std::list<std::string>::const_iterator wListItr = arModulesList.begin(); wListItr != arModulesList.end(); ++wListItr)
        {
            if (0 == wListItr->compare(mscAllModuleKeyword))
            {
                msModuleActivationMask = ULONG_MAX;
                wModuleList = mscAllModuleKeyword;
                break;
            }
            else
            {
                eLogModuleType wLogModuleType = LogModuleTypeStringToEnum(*wListItr);
                if (LOG_NO_MODULE != wLogModuleType)
                {
                    msModuleActivationMask |= (1 << (int)wLogModuleType);
                    wModuleList += *wListItr + ",";
                }
            }
        }

        // Log logging start because new configuration file has been detected
        GetLoggerInstance()->logInfo("LoggerManager::NewModulesList, modules: "+wModuleList);
    }

    bool LoggerManager::IsModuleLogActivated(eLogModuleType aModuletype)
    {
        bool wLogActivated = msModuleActivationMask & (1 << (int)aModuletype);
        return wLogActivated;
    }

    void LoggerManager::UpdateLogLevel(std::string& aNewLogLevel)
    {
        GetLoggerInstance()->UpdateLogLevel(aNewLogLevel);
    }
} /* namespace hbslogging */
