#pragma once

#include <util/generic/stroka.h>
#include <util/system/backtrace.h>
#include <contrib/libs/log4cpp/Category.hh>
#include <contrib/libs/log4cpp/Priority.hh>
#include <contrib/libs/log4cpp/PropertyConfigurator.hh>
#include <signal.h>
#include <cstdlib>
#include <cstring>

// DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < FATAL = EMERG

namespace ExceptionTrace{

    class CTracer{
    public:
        static void LogInit();

        static void WriteDebug(Stroka message);
        static void WriteDebug(char message[]);
        static void WriteDebug(std::string message);

        static void WriteInfo(Stroka message);
        static void WriteInfo(const char* message);
        static void WriteInfo(std::string message);

        static void WriteNotice(Stroka message);
        static void WriteNotice(const char* message);
        static void WriteNotice(std::string message);
        
        static void WriteWarning(Stroka message);
        static void WriteWarning(const char* message);
        static void WriteWarning(std::string message);

        static void WriteError(Stroka message);
        static void WriteError(const char* message);
        static void WriteError(std::string message);

        static void WriteCritical(Stroka message);
        static void WriteCritical(const char* message);
        static void WriteCritical(std::string message);

        static void WriteAlert(Stroka message);
        static void WriteAlert(const char* message);
        static void WriteAlert(std::string message);

        static void WriteFatal(Stroka message);
        static void WriteFatal(const char* message);
        static void WriteFatal(std::string message);
        
    private:
        static void signalCallbackHandler(int signum);
        static void WriteLog(Stroka message, log4cpp::Priority::PriorityLevel level);
    };
}