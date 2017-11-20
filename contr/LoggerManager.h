/**
 * @file    LoggerManager.h
 * @author  menagec
 * @date    21 juil. 2014
 * @brief   brief
 * @details details
 */

#ifndef LOGGERMANAGER_H_
#define LOGGERMANAGER_H_

//System includes
#include <climits>
#include <list>
#include <string>
#include <typeinfo>
//Libraries includes
//Application includes
#include "Logger.h"

// Activate NO_LOG define to deactivate completely logs at compile time. */
//#define NO_LOG

// Logging macros
#ifdef NO_LOG
#define LOG_INFORMATION_OBJECT_METHOD(module)
#define LOG_INFORMATION_MESSAGE(module,msg)
#define LOG_DEBUG_MESSAGE(module,msg)
#define LOG_WARN_MESSAGE(module,msg)
#define LOG_ERROR_MESSAGE(module,msg)
#define LOG_FATAL_MESSAGE(module,msg)
#else // NO_LOG
// NOTE: Test module activation is tested directly in macro so that parameters passed for 'msg' are not evaluated uselessly in case module is not activated (for minimized cpu usage)
#define LOG_INFORMATION_OBJECT_METHOD(module)   if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logInfo ("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__));};
#define LOG_INFORMATION_MESSAGE(module,msg)     if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logInfo ("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__)+", "+msg);};
#define LOG_DEBUG_MESSAGE(module,msg)           if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logDebug("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__)+", "+msg);};
#define LOG_WARN_MESSAGE(module,msg)            if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logWarn ("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__)+", "+msg);};
#define LOG_ERROR_MESSAGE(module,msg)           if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logError("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__)+", "+msg);};
#define LOG_FATAL_MESSAGE(module,msg)           if(LoggingModule::LoggerManager::IsModuleLogActivated(module)){LoggingModule::LoggerManager::GetLoggerInstance()->logFatal("["+LoggingModule::LoggerManager::LogModuleTypeEnumToString(module)+"] "+std::string(typeid(this).name())+"::"+std::string(__FUNCTION__)+", "+msg);};
#endif // NO_LOG

namespace LoggingModule
{

    class LoggerManager
    {
    public:
        static const std::string mscAllModuleKeyword;
        static const std::string mscCoreModuleKeyword;
        static const std::string mscCommunicationModuleKeyword;
        static const std::string mscEventModuleKeyword;
        static const std::string mscIoModuleKeyword;
        static const std::string mscLedModuleKeyword;
        static const std::string mscSupervisionModuleKeyword;
        static const std::string mscUtilitiesModuleKeyword;

        typedef enum eLogModuleType
        {
            LOG_NO_MODULE               = -1,
            LOG_CORE_MODULE             = 0,
            LOG_COMMUNICATION_MODULE    = 1,
            LOG_EVENT_MODULE            = 2,
            LOG_IO_MODULE               = 3,
            LOG_LED_MODULE              = 4,
            LOG_SUPERVISION_MODULE      = 5,
            LOG_UTILITIES_MODULE        = 6,
        } eLogModuleType;

        static inline eLogModuleType LogModuleTypeStringToEnum(const std::string& arModuleName)
        {
            eLogModuleType wLogModuleType = LOG_NO_MODULE;
            if      (0 == arModuleName.compare(mscCoreModuleKeyword         ))  wLogModuleType = LOG_CORE_MODULE;
            else if (0 == arModuleName.compare(mscCommunicationModuleKeyword))  wLogModuleType = LOG_COMMUNICATION_MODULE;
            else if (0 == arModuleName.compare(mscEventModuleKeyword        ))  wLogModuleType = LOG_EVENT_MODULE;
            else if (0 == arModuleName.compare(mscIoModuleKeyword           ))  wLogModuleType = LOG_IO_MODULE;
            else if (0 == arModuleName.compare(mscLedModuleKeyword          ))  wLogModuleType = LOG_LED_MODULE;
            else if (0 == arModuleName.compare(mscSupervisionModuleKeyword  ))  wLogModuleType = LOG_SUPERVISION_MODULE;
            else if (0 == arModuleName.compare(mscUtilitiesModuleKeyword    ))  wLogModuleType = LOG_UTILITIES_MODULE;
            return wLogModuleType;
        }

        static inline std::string LogModuleTypeEnumToString(eLogModuleType aLogModuleType)
        {
            std::string wLogModuleString = "";
            switch(aLogModuleType)
            {
            case LOG_NO_MODULE              :       break;
            case LOG_CORE_MODULE            :       wLogModuleString = mscCoreModuleKeyword;                 break;
            case LOG_COMMUNICATION_MODULE   :       wLogModuleString = mscCommunicationModuleKeyword;        break;
            case LOG_EVENT_MODULE           :       wLogModuleString = mscEventModuleKeyword;                break;
            case LOG_IO_MODULE              :       wLogModuleString = mscIoModuleKeyword;                   break;
            case LOG_LED_MODULE             :       wLogModuleString = mscLedModuleKeyword;                  break;
            case LOG_SUPERVISION_MODULE     :       wLogModuleString = mscSupervisionModuleKeyword;          break;
            case LOG_UTILITIES_MODULE       :       wLogModuleString = mscUtilitiesModuleKeyword;            break;
            default                         :       break;
            }
            return wLogModuleString;
        }

    public:
        /** @brief Constructor */
        LoggerManager(std::string aLogLevel, std::list<std::string> aActiveList, UtilitiesModule::Osal* apOsal);
        /** @brief Constructor from instance */
        LoggerManager(const LoggerManager&) = delete;
        /** @brief Constructor from affectation. */
        LoggerManager& operator=(LoggerManager const&) = delete;
        /** @brief Destructor */
        virtual ~LoggerManager();

        /**
         * @brief Get logger instances for given module name.
         * @return Pointer to logger instance.
         */
        static Logger* GetLoggerInstance(void);
        /**
         * @brief Indicates if module logs are activated.
         * @param[in] arModule Module name string.
         * @return True if module logging is activated, else false.
         */
        static bool IsModuleLogActivated(eLogModuleType aModuletype);
        /**
         * @brief Set new module logging activation set.
         * @param[in] arModulesList Set of modules for which logging is activated.
         */
        static void NewModulesList(const std::list<std::string>& arModulesList);
        /**
         * @brief Update registered logger to affect correct level.
         * @param aNewLogLevel The new log level.
         */
        void UpdateLogLevel(std::string& aNewLogLevel);

#if defined(RUN_TEST)
    public:
#else // defined(RUN_TEST)
    private:
#endif //defined(RUN_TEST)
        /** @brief Set of modules for which logs are activated. */
        static unsigned long msModuleActivationMask;
        /** @brief Singleton logger instance. */
        static Logger* msLogger; // singleton instance
        /** @brief Operating System Abstraction Layer */
        static UtilitiesModule::Osal* mpOsal;
    };
} /* namespace LoggingModule */

#endif /* LOGGERMANAGER_H_ */
