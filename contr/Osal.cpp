/**
 * @file    Osal.cpp
 * @author  calligp
 * @date    03/09/2015
 * @brief   brief
 * @details details
 */

//System includes
//Libraries includes
//Application includes
#include <UtilitiesModule/Osal.h>

// WARNING !
// Can not log error because of cyclic dependencies between logger and osal
// Responsability to the caller to trace error
namespace UtilitiesModule
{
    Osal::Osal(void)
    {
    }

    /* virtual */ Osal::~Osal()
    {
    }

    bool Osal::RunCommand(const char* aCommand)
    {
        int wResult = 0;
        bool wReturn = false;

        wResult = system(aCommand);
        if (0 == wResult)
        {
            wReturn = true;
        }
        return wReturn;
    }

    /* virtual */ bool Osal::StartService(const char* aServiceName)
    {
        char wCommand[100] = INIT_DIR;

        strcat(wCommand, aServiceName);
        strcat(wCommand, " start");

        return RunCommand(wCommand);
    }

    /* virtual */ bool Osal::RunService(const char* aServiceName, const char* aOption)
    {
        char wCommand[100] = INIT_DIR;

        strcat(wCommand, aServiceName);
        strcat(wCommand, " ");
        strcat(wCommand, aOption);

        return RunCommand(wCommand);
    }

    /* virtual */ bool Osal::ReadFile(const std::string aFilePath, const std::string aFileName, std::string* apBuffer)
    {
        std::string wLine;
        std::stringstream wStream;
        std::ifstream wFile(aFilePath + "/" + aFileName);
        if (wFile.is_open())
        {
            while (getline(wFile, wLine))
            {
                wStream << wLine;
            }
            wFile.close();
            *apBuffer = wStream.str();
            return true;
        }
        else
        {
            return false;
        }
    }

    /* virtual */ bool Osal::TestDBConnection(const char* apHost, int aPort)
    {
        int wSockFD = -1;
        sockaddr_in wServer;
        bool wReturn = false;

        wSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (-1 != wSockFD)
        {
            // Configure socket connection
            wServer.sin_family = AF_INET;
            wServer.sin_port = htons(aPort);
            // /!\ Should be IP adresse, not a DNS name
            inet_pton(AF_INET, apHost, &wServer.sin_addr.s_addr);
            wServer.sin_zero[0] = 0;

            // Open DB socket
            if (-1 != connect(wSockFD, (sockaddr *)&wServer, sizeof(wServer)))
            {
                // Close DB socket
                close(wSockFD);
                wReturn = true;
            }
        }

        return wReturn;
    }

    /* virtual */ bool Osal::WriteFile(const std::string aFilePath, const std::string aFileName, const std::string aValue)
    {
        bool wReturn = false;

        // Open file
        std::stringstream wFilePath;
        wFilePath << aFilePath << aFileName;
        std::ofstream wFile(wFilePath.str());

        // Check if file is open, then write new value
        if (true == wFile.is_open())
        {
            wFile << aValue;
            wFile.close();
            wReturn = true;
        }
        return wReturn;
    }

    bool Osal::CheckDirectoryIsWritable(const std::string aDirPath)
    {
        bool wReturn = false;
        struct stat wPathState;

        if (0 == stat(aDirPath.c_str(), &wPathState))
        {
            if (true == S_ISDIR(wPathState.st_mode))
            {
                wReturn = WriteFile(aDirPath, "/test_fs", "it is a test to write FS");
            }
            // Else: it is not a directory, link on directory are not same than directory.
        }
        // Else: the path refer to noting on the file system.

        return wReturn;
    }

    /* virtual */ double Osal::GetCpuLoadPercent(void)
    {
        static const char fmt[] = "cpu  %llu %llu %llu %llu %llu %llu %llu %llu";
        int wRet;
        sCpuFreq wStats;
        std::string wLine;

        std::ifstream wStatFile(STAT_FILE);
        getline(wStatFile, wLine);
        wStatFile.close();

        wRet = sscanf(wLine.c_str(), fmt,
                &wStats.usr,
                &wStats.nic,
                &wStats.sys,
                &wStats.idle,
                &wStats.iowait,
                &wStats.irq,
                &wStats.softirq,
                &wStats.steal);
        /* Linux 2.4.x has only first four */
        if (wRet >= 4) {
            wStats.total = wStats.usr + wStats.nic + wStats.sys + wStats.idle
                + wStats.iowait + wStats.irq + wStats.softirq + wStats.steal;
            /* procps 2.x does not count iowait as busy time */
            wStats.busy = wStats.total - wStats.idle - wStats.iowait;

            return ((wStats.busy * 100.0) / wStats.total);
        }
        else
        {
            return -1;
        }
    }

    /* virtual */ double Osal::GetRamFreePercent(void)
    {
        // Thanks to HTOP sources for this solution !
        unsigned long long int wTotalMem = 0;
        unsigned long long int wTotFreeMem = 0;
        unsigned long long int wFreeMem = 0;
        unsigned long long int wBuffersMem = 0;
        unsigned long long int wCachedMem = 0;
        char buffer[128];

        FILE* file = fopen(MEMINFO_FILE, "r");
        if (file != NULL) {
            while (fgets(buffer, 128, file)) {
                switch (buffer[0]) {
                case 'M':
                    if (String_startsWith(buffer, "MemTotal:"))
                    {
                        sscanf(buffer, "MemTotal: %llu kB", &wTotalMem);
                    }
                    else if (String_startsWith(buffer, "MemFree:"))
                    {
                        sscanf(buffer, "MemFree: %llu kB", &wFreeMem);
                    }
                    break;
                case 'B':
                    if (String_startsWith(buffer, "Buffers:"))
                    {
                        sscanf(buffer, "Buffers: %llu kB", &wBuffersMem);
                    }
                    break;
                case 'C':
                    if (String_startsWith(buffer, "Cached:"))
                    {
                        sscanf(buffer, "Cached: %llu kB", &wCachedMem);
                    }
                    break;
                }
            }

            wTotFreeMem = wFreeMem + wCachedMem + wBuffersMem;
            fclose(file);

            return (wTotFreeMem * 100.0) / wTotalMem;
        }
        else
        {
            return -1;
        }
    }

    /* virtual */ double Osal::GetFreeSpacePercent(const char* aPath)
    {
        struct statvfs wStats;
        // -1 say the information is not available from Unix System
        if (-1 != statvfs(aPath, &wStats))
        {
            return ((wStats.f_bfree * 100) / wStats.f_blocks);
        }
        else
        {
            return -1;
        }
    }

    /* virtual */ double Osal::GetCpuTemperature(void)
    {
        std::string wTempStr;
        if (ReadFile(CPU_TEMP_DIR, CPU_TEMP_FILE, &wTempStr) && false == wTempStr.empty())
        {
            return std::stod(wTempStr);
        }
        else
        {
            return -1;
        }
    }

    bool Osal::GetCpuTemperatureRange(double* aHot, double* aCritical)
    {
        std::string wTempStr;
        if (ReadFile(CPU_TEMP_DIR, CPU_TEMP_HOT_FILE, &wTempStr) && false == wTempStr.empty())
        {
            *aHot = std::stod(wTempStr);
        }
        else
        {
            return false;
        }
        if (ReadFile(CPU_TEMP_DIR, CPU_TEMP_CRIT_FILE, &wTempStr) && false == wTempStr.empty())
        {
            *aCritical = std::stod(wTempStr);
        }
        else
        {
            return false;
        }
        return true;
    }
}
