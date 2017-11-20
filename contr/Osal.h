/**
 * @file    Osal.h
 * @author  calligp
 * @date    03/09/2015
 * @brief   Operating System Abstraction Layer
 * @details Expose interface to interact with Operating System
 */

#ifndef SRC_UTILITIESMODULE_OSAL_H_
#define SRC_UTILITIESMODULE_OSAL_H_

// System includes
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>
// Libraries includes
// Application includes

namespace UtilitiesModule
{
    #define INIT_DIR "/etc/init.d/"
    #define PROC_DIR "/proc"
    #define MEMINFO_FILE PROC_DIR "/meminfo"
    #define STAT_FILE PROC_DIR "/stat"
    #define CPU_TEMP_DIR "/sys/devices/virtual/thermal/thermal_zone0"
    #define CPU_TEMP_FILE "temp"
    #define CPU_TEMP_HOT_FILE "trip_point_1_temp"
    #define CPU_TEMP_CRIT_FILE "trip_point_0_temp"
    #define String_startsWith(s, match) (strstr((s), (match)) == (s))

    typedef struct sCpuFreq {
        /* Linux 2.4.x has only first four */
        unsigned long long usr;
        unsigned long long nic;
        unsigned long long sys;
        unsigned long long idle;
        unsigned long long iowait;
        unsigned long long irq;
        unsigned long long softirq;
        unsigned long long steal;
        unsigned long long total;
        unsigned long long busy;
    } sCpuFreq;

    class Osal
    {
    public:
        /**
         * @brief Constructor.
         */
        Osal(void);
        /**
         * @brief Destructor.
         */
        virtual ~Osal(void);
        /**
         * @brief Start service.
         * @param [in] aServiceName The name of the service to start.
         * @return Boolean
         */
        virtual bool StartService(const char* aServiceName);
        /**
         * @brief Execute a service with given option.
         * @param [in] aServiceName The name of the service to start.
         * @param [in] aOption The service option to use. See service file for available value.
         * @return Boolean
         */
        virtual bool RunService(const char* aServiceName, const char* aOption);
        /**
         * @brief Read file content
         * @param [in] aFilePath The absolute path to the file to read.
         * @param [out] apBuffer The buffer to set file content.
         * @return Boolean
         */
        virtual bool ReadFile(const std::string aFilePath, const std::string aFileName, std::string* apBuffer);
        /**
         * @brief Test the connection with Database using TCP socket.
         * @param [in] aHost The hostname to connect the socket.
         * @param [in] aPort The port to connect the socket.
         * @return Boolean
         */
        virtual bool TestDBConnection(const char* aHost, int aPort);
        /**
         * @brief Write a file content.
         * @param [in] aFilePath The absolute path of the file to write.
         * @param [in] aFileName The name of the file to write.
         * @param [in] aValue The value to write in file.
         * @return Boolean
         */
        virtual bool WriteFile(const std::string aFilePath, const std::string aFileName, const std::string aValue);
        /**
         * @brief Check if the path exist and is a directory, Write a file on it.
         * @param [in] aDirPath The absolute path to check
         * @return Boolean
         */
        virtual bool CheckDirectoryIsWritable(const std::string aDirPath);
        /**
         * @brief Retrieve Cpu load from Operating System and compute current percentage.
         * @return The current Cpu Load Percentage (Taking into account multi-core). Or -1 if the stats are not
         * available.
         */
        virtual double GetCpuLoadPercent(void);
        /**
         * @brief Retrieve Current Ram Free Percentage
         * @attetion This RAM percentage take into account shared memory even if it is not really used.
         * @return The current Ram Free space percentage. Or -1 if the stats are not available.
         */
        virtual double GetRamFreePercent(void);
        /**
         * @brief Retrieve Current Free space percentage regarding a give path.
         * @param aPath The partition path to analyse.
         * @return The current Free space percentage. Or -1 if the stats are not available.
         */
        virtual double GetFreeSpacePercent(const char* aPath);
        /**
         * @brief Retrieve CPU temperature from system file
         */
        virtual double GetCpuTemperature(void);
        /**
         * @brief Retrieve CPU temperature range (hot and critical) from system file
         */
        virtual bool GetCpuTemperatureRange(double* aHot, double* aCritical);
        /**
         * @brief Execute a command.
         * @param [in] aCommand The command to execute.
         * @return Boolean
         */
        virtual bool RunCommand(const char* aServiceName);
    };
}

#endif /* SRC_UTILITIESMODULE_OSAL_H_ */
