/**
 * @file    Logger.h
 * @author  mat
 * @date    07 jan. 2014
 * @brief   brief
 * @details details
 */
#ifndef _LOGGER_H_
#define _LOGGER_H_

//System includes
#include <string>
#include <array>
#include <functional>
//Libraries includes
#include <syslog.h>
//Application includes
#include "Osal.h"

namespace LoggingModule {

    class Logger
    {
    public:
        typedef enum eLogLevelType
        {
            LOG_LEVEL_DEBUG     = 0,
            LOG_LEVEL_INFO      = 1,
            LOG_LEVEL_WARNING   = 2,
            LOG_LEVEL_ERROR     = 3,
            LOG_LEVEL_FATAL     = 4,
            LOG_LEVEL_NONE      = 5,
        } eLogLevelType;
        #define LOG_LEVEL_NB 6

        /// @brief Function prototype definition for logging.
        typedef std::function<void(int aPriority, const std::string& arContext, const std::string& arMessage)> LogFunctionType;
        /// @brief Structure to store log functions depending on log level.
        typedef std::array<LogFunctionType, LOG_LEVEL_NB> LogLevelFunctionArrayType;

        /**
         * @brief Default constructor.
         */
        Logger(UtilitiesModule::Osal* apOsal);
        /**
         * @brief Copy constructor inhibited.
         */
        Logger(Logger const&) = delete;
        /**
         * @brief Copy assignment inhibited.
         */
        Logger& operator=(Logger const&) = delete;
        /**
         * @brief Destructor.
         */
        virtual ~Logger();

        /**
         * @brief Update array of log function pointer.
         * @param aNewLevel Level to apply on current logger instance.
         */
        void UpdateLogLevel(std::string& aNewLevel);

        /**
         * @brief Log information message.
         * @param[in] arMessage Message.
         */
        void logInfo(const std::string& arMessage);
        /**
         * @brief Log debug message.
         * @param[in] arMessage Message.
         */
        void logDebug(const std::string& arMessage);
        /**
         * @brief Log warning message.
         * @param[in] arMessage Message.
         */
        void logWarn(const std::string& arMessage);
        /**
         * @brief Log error message.
         * @param[in] arMessage Message.
         */
        void logError(const std::string& arMessage);
        /**
         * @brief Log fatal error message.
         * @param[in] arMessage Message.
         */
        void logFatal(const std::string& arMessage);
        /**
         * @brief Generic function to interface with external logger.
         * @param aPriority The log level to use.
         * @param arContext
         * @param arMessage The message to log.
         */
        void log(int aPriority, const std::string& arContext, const std::string& arMessage);

#if defined(RUN_TEST)
    public:
#else // defined(RUN_TEST)
    private:
#endif //defined(RUN_TEST)
        /** @brief Initialize logger. */
        void Initialise(void);
        /** @brief Operating System Abstraction Layer */
        UtilitiesModule::Osal* mpOsal;
        /** @brief Array of log functions depending on log level. */
        LogLevelFunctionArrayType msLogLevelFunctionArray;
        /** @brief Current log level */
        eLogLevelType mCurrentLevel;

        // Log level identifier strings
        static const std::string mscNoneLogLevel;
        static const std::string mscFatalLogLevel;
        static const std::string mscErrorLogLevel;
        static const std::string mscWarningLogLevel;
        static const std::string mscInfoLogLevel;
        static const std::string mscDebugLogLevel;

        /**
         * @brief inline function to convert string log level to enum value.
         * @param arLogLevel The log level.
         */
        static inline eLogLevelType LogLevelTypeStringToEnum( const std::string& arLogLevel )
        {
            eLogLevelType wLogLevelType = LOG_LEVEL_NONE;
            if      (0 == arLogLevel.compare( mscDebugLogLevel  )) wLogLevelType = LOG_LEVEL_DEBUG;
            else if (0 == arLogLevel.compare( mscInfoLogLevel   )) wLogLevelType = LOG_LEVEL_INFO;
            else if (0 == arLogLevel.compare( mscWarningLogLevel)) wLogLevelType = LOG_LEVEL_WARNING;
            else if (0 == arLogLevel.compare( mscErrorLogLevel  )) wLogLevelType = LOG_LEVEL_ERROR;
            else if (0 == arLogLevel.compare( mscFatalLogLevel  )) wLogLevelType = LOG_LEVEL_FATAL;
            return wLogLevelType;
        }

    };
}
#endif /* _LOGGER_H_ */



