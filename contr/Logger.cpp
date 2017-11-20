/**
 * @file    Logger.cpp
 * @author  mat
 * @date    07 jan. 2014
 * @brief   brief
 * @details details
 */

//System includes
//Libraries includes
//Application includes
#include "Logger.h"


namespace LoggingModule {
    /*static */const std::string Logger::mscFatalLogLevel = "fatal";
    /*static */const std::string Logger::mscErrorLogLevel = "error";
    /*static */const std::string Logger::mscWarningLogLevel = "warning";
    /*static */const std::string Logger::mscInfoLogLevel = "info";
    /*static */const std::string Logger::mscDebugLogLevel = "debug";
    /*static */const std::string Logger::mscNoneLogLevel = "none";

    Logger::Logger(UtilitiesModule::Osal* apOsal)
    : mpOsal(NULL),
      msLogLevelFunctionArray({{
        [](int aPriority, const std::string& arContext, const std::string& arMessage){},
        [](int aPriority, const std::string& arContext, const std::string& arMessage){},
        [](int aPriority, const std::string& arContext, const std::string& arMessage){},
        [](int aPriority, const std::string& arContext, const std::string& arMessage){},
        [](int aPriority, const std::string& arContext, const std::string& arMessage){},
        [](int aPriority, const std::string& arContext, const std::string& arMessage){}
      }}),
      mCurrentLevel(eLogLevelType::LOG_LEVEL_NONE)
    {
        std::string wDefaultLevel = mscNoneLogLevel;
        // If NULL pointer is provided then no call to system command
        // Only in test
        if (NULL != apOsal)
        {
            mpOsal = apOsal;
        }
        Initialise();
        UpdateLogLevel(wDefaultLevel);
    }

    Logger::~Logger()
    {
        closelog ();
    }

    void Logger::log(int aPriority, const std::string& arContext, const std::string& arMessage)
    {
        syslog(aPriority, "%s %s", arContext.c_str(), arMessage.c_str());
    }

    void Logger::logDebug(const std::string& arMessage)
    {
        msLogLevelFunctionArray[eLogLevelType::LOG_LEVEL_DEBUG](LOG_DEBUG, "[debug]", arMessage);
    }

    void Logger::logInfo(const std::string& arMessage)
    {
        msLogLevelFunctionArray[eLogLevelType::LOG_LEVEL_INFO](LOG_NOTICE, "[info]", arMessage);
    }

    void Logger::logWarn(const std::string& arMessage)
    {
        msLogLevelFunctionArray[eLogLevelType::LOG_LEVEL_WARNING](LOG_WARNING, "[warning]", arMessage);
    }

    void Logger::logError(const std::string& arMessage)
    {
        msLogLevelFunctionArray[eLogLevelType::LOG_LEVEL_ERROR](LOG_ERR, "[error]", arMessage);
    }

    void Logger::logFatal(const std::string& arMessage)
    {
        msLogLevelFunctionArray[eLogLevelType::LOG_LEVEL_FATAL](LOG_CRIT, "[fatal]", arMessage);
    }

    void Logger::Initialise(void)
    {
        if (NULL != mpOsal)
        {
            // restart rsyslog service
            mpOsal->RunService("rsyslog", "force-reload");
        }
        // Create rsyslog handler
        openlog("HesController", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
        // Log init
        logInfo("[Log] Logger::initialize Program started by User " + std::to_string(getuid()));
    }

    void Logger::UpdateLogLevel(std::string& aNewLevel)
    {
        eLogLevelType wLogLevel = LogLevelTypeStringToEnum(aNewLevel);
        int wMinimumLogLevel = static_cast<int>(wLogLevel);
        mCurrentLevel = wLogLevel;
        msLogLevelFunctionArray = { {
                [](int aPriority, const std::string& arContext, const std::string& arMessage){},
                [](int aPriority, const std::string& arContext, const std::string& arMessage){},
                [](int aPriority, const std::string& arContext, const std::string& arMessage){},
                [](int aPriority, const std::string& arContext, const std::string& arMessage){},
                [](int aPriority, const std::string& arContext, const std::string& arMessage){},
                [](int aPriority, const std::string& arContext, const std::string& arMessage){}
        } };
        // Set log methods
        if ( static_cast<int>(eLogLevelType::LOG_LEVEL_DEBUG) >= wMinimumLogLevel )
        {
            msLogLevelFunctionArray[static_cast<int>(eLogLevelType::LOG_LEVEL_DEBUG)] = [this](int aPriority, const std::string& arContext, const std::string& arMessage){log(aPriority, arContext, arMessage); };
        }
        if ( static_cast<int>(eLogLevelType::LOG_LEVEL_INFO) >= wMinimumLogLevel )
        {
            msLogLevelFunctionArray[static_cast<int>(eLogLevelType::LOG_LEVEL_INFO)] = [this](int aPriority, const std::string& arContext, const std::string& arMessage){log(aPriority, arContext, arMessage); };
        }
        if ( static_cast<int>(eLogLevelType::LOG_LEVEL_WARNING) >= wMinimumLogLevel )
        {
            msLogLevelFunctionArray[static_cast<int>(eLogLevelType::LOG_LEVEL_WARNING)] = [this](int aPriority, const std::string& arContext, const std::string& arMessage){log(aPriority, arContext, arMessage); };
        }
        if ( static_cast<int>(eLogLevelType::LOG_LEVEL_ERROR) >= wMinimumLogLevel )
        {
            msLogLevelFunctionArray[static_cast<int>(eLogLevelType::LOG_LEVEL_ERROR)] = [this](int aPriority, const std::string& arContext, const std::string& arMessage){log(aPriority, arContext, arMessage); };
        }
        if ( static_cast<int>(eLogLevelType::LOG_LEVEL_FATAL) >= wMinimumLogLevel )
        {
            msLogLevelFunctionArray[static_cast<int>(eLogLevelType::LOG_LEVEL_FATAL)] = [this](int aPriority, const std::string& arContext, const std::string& arMessage){log(aPriority, arContext, arMessage); };
        }

        // Log new level set
        std::stringstream wMsg;
        wMsg << "[Log] LoggerManager::NewLogLevel, level: " << aNewLevel;
        logInfo(wMsg.str());
    }

}
