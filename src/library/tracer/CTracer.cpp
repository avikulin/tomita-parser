
#include <library/tracer/CTracer.h>

using namespace ExceptionTrace;

//---Public functions-------------------------------------------------------
void CTracer::LogInit(){
    //---Init of log4cpp faramework
    std::string initFileName = "logSettings.properties";
    log4cpp::PropertyConfigurator::configure(initFileName);

    //---Init unhendled execptions trap
    signal(SIGINT,      signalCallbackHandler);
    signal(SIGHUP,      signalCallbackHandler);
    signal(SIGINT,      signalCallbackHandler);
    signal(SIGQUIT,     signalCallbackHandler);
    signal(SIGILL,      signalCallbackHandler);
    signal(SIGTRAP,     signalCallbackHandler);
    signal(SIGABRT,     signalCallbackHandler);
    signal(SIGIOT,      signalCallbackHandler);
    signal(SIGBUS,      signalCallbackHandler);
    signal(SIGFPE,      signalCallbackHandler);
    signal(SIGKILL,     signalCallbackHandler);
    signal(SIGUSR1,     signalCallbackHandler);
    signal(SIGSEGV,     signalCallbackHandler);
    signal(SIGUSR2,     signalCallbackHandler);
    signal(SIGPIPE,     signalCallbackHandler);
    signal(SIGALRM,     signalCallbackHandler);
    signal(SIGTERM,     signalCallbackHandler);
    signal(SIGSTKFLT,   signalCallbackHandler);
    signal(SIGCHLD,     signalCallbackHandler);
    signal(SIGCLD,      signalCallbackHandler);
    signal(SIGCONT,     signalCallbackHandler);
    signal(SIGSTOP,     signalCallbackHandler);
    signal(SIGTSTP,     signalCallbackHandler);
    signal(SIGTTIN,     signalCallbackHandler);
    signal(SIGTTOU,     signalCallbackHandler);
    signal(SIGURG,      signalCallbackHandler);
    signal(SIGXCPU,     signalCallbackHandler);
    signal(SIGXFSZ,     signalCallbackHandler);
    signal(SIGVTALRM,   signalCallbackHandler);
    signal(SIGPROF,     signalCallbackHandler);
    signal(SIGWINCH,    signalCallbackHandler);
    signal(SIGIO,       signalCallbackHandler);
    signal(SIGPOLL,     signalCallbackHandler);
    signal(SIGPWR,      signalCallbackHandler);
    signal(SIGSYS,      signalCallbackHandler);
}   

//---DEBUG---
void CTracer::WriteDebug(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::DEBUG);
}

void CTracer::WriteDebug(char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::DEBUG);
}

void CTracer::WriteDebug(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::DEBUG);
}

//---INFO---
void CTracer::WriteInfo(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::INFO);
}

void CTracer::WriteInfo(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::INFO);
}

void CTracer::WriteInfo(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::INFO);
}

//---NOTICE---

void CTracer::WriteNotice(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::NOTICE);
}

void CTracer::WriteNotice(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::NOTICE);
}

void CTracer::WriteNotice(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::NOTICE);
}

//---WARN---

void CTracer::WriteWarning (Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::WARN);
}

void CTracer::WriteWarning(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::WARN);
}

void CTracer::WriteWarning(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::WARN);
}

//---ERROR---

void CTracer::WriteError(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::ERROR);
}

void CTracer::WriteError(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::ERROR);
}

void CTracer::WriteError(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::ERROR);
}

//---CRIT---

void CTracer::WriteCritical(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::CRIT);
}

void CTracer::WriteCritical(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::CRIT);
}

void CTracer::WriteCritical(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::CRIT);
}

//---ALERT---

void CTracer::WriteAlert(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::ALERT);
}

void CTracer::WriteAlert(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::ALERT);
}

void CTracer::WriteAlert(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::ALERT);
}

//---FATAL---

void CTracer::WriteFatal(Stroka message){
    WriteLog(message, log4cpp::Priority::PriorityLevel::FATAL);
}

void CTracer::WriteFatal(const char* message){
    WriteLog(Stroka(message), log4cpp::Priority::PriorityLevel::FATAL);
}

void CTracer::WriteFatal(std::string message){
    WriteLog(Stroka(message.c_str()),log4cpp::Priority::PriorityLevel::FATAL);
}

///---- Private functions------------------------------------------
///< ERROR < CRIT < ALERT < FATAL
void CTracer::WriteLog(Stroka message, log4cpp::Priority::PriorityLevel level){
    switch(level){
        case log4cpp::Priority::PriorityLevel::DEBUG :
        case log4cpp::Priority::PriorityLevel::INFO  :
        case log4cpp::Priority::PriorityLevel::NOTICE:
        case log4cpp::Priority::PriorityLevel::WARN  :{
                                        log4cpp::Category& rootStream   = log4cpp::Category::getRoot();
                                        rootStream<<level<<message.c_str();
                                        break;
                                        }
        case log4cpp::Priority::PriorityLevel::ERROR :
        case log4cpp::Priority::PriorityLevel::CRIT  :
        case log4cpp::Priority::PriorityLevel::ALERT :
        case log4cpp::Priority::PriorityLevel::FATAL :{
                                        log4cpp::Category& errorStream = log4cpp::Category::getInstance("errorsOnly");
                                        errorStream<<level<<message.c_str();
                                        break;
                                        }
    }
}

void CTracer::signalCallbackHandler(int signum) {
    Stroka msg_str;
    switch (signum){
        case  1 :  msg_str = "SIGHUP [1] - Hangup (POSIX). Report that user's terminal is disconnected. Signal used to report the termination of the controlling process."; break;
        case  2 :  msg_str = "SIGINT [2] - Interrupt (ANSI). Program interrupt. (ctrl-c)."; break;
        case  3 :  msg_str = "SIGQUIT [3] - Quit (POSIX). Terminate process and generate core dump."; break;
        case  4 :  msg_str = "SIGILL [4] - Illegal Instruction (ANSI). Generally indicates that the executable file is corrupted or use of data where a pointer to a function was expected."; break;
        case  5 :  msg_str = "SIGTRAP [5] - Trace trap (POSIX)."; break;
        case  6 :  msg_str = "SIGABRT/SIGIOT [6] - Abort (ANSI). IOT trap (4.2 BSD). Process detects error and reports by calling abort"; break;
        case  7 :  msg_str = "SIGBUS [7] - BUS error (4.2 BSD). Indicates an access to an invalid address."; break;
        case  8 :  msg_str = "SIGFPE [8] - Floating-Point arithmetic Exception (ANSI). This includes division by zero and overflow.The IEEE Standard for Binary Floating-Point Arithmetic (ANSI/IEEE Std 754-1985) defines various floating-point exceptions."; break;
        case  9 :  msg_str = "SIGKILL [9] - Kill, unblockable (POSIX). Cause immediate program termination.Can not be handled, blocked or ignored."; break;
        case  10:  msg_str = "SIGUSR1 [10] - User-defined signal 1."; break;
        case  11:  msg_str = "SIGSEGV [11] - Segmentation Violation (ANSI). Occurs when a program tries to read or write outside the memory that is allocated for it by the operating system, dereferencing a bad or NULL pointer. Indicates an invalid access to valid memory."; break;
        case  12:  msg_str = "SIGUSR2 [12] - User-defined signal 2."; break;
        case  13:  msg_str = "SIGPIPE [13] - Broken pipe (POSIX). Error condition like trying to write to a socket which is not connected."; break;
        case  14:  msg_str = "SIGALRM [14] - Alarm clock (POSIX). Indicates expiration of a timer. Used by the alarm() function."; break;
        case  15:  msg_str = "SIGTERM [15] - Termination (ANSI). This signal can be blocked, handled, and ignored. Generated by \"kill\" command."; break;
        case  16:  msg_str = "SIGSTKFLT [16] - Stack fault"; break;
        case  17:  msg_str = "SIGCHLD/SIGCLD [17] - Child status has changed (POSIX). Signal sent to parent process whenever one of its child processes terminates or stops."; break;
        case  18:  msg_str = "SIGCONT [18] - Continue (POSIX). Signal sent to process to make it continue."; break;
        case  19:  msg_str = "SIGSTOP [19] - Stop, unblockable (POSIX). Stop a process. This signal cannot be handled, ignored, or blocked."; break;
        case  20:  msg_str = "SIGTSTP [20] - Keyboard stop (POSIX). Interactive stop signal. This signal can be handled and ignored. (ctrl-z)."; break;
        case  21:  msg_str = "SIGTTIN [21] - Background read from tty (POSIX)."; break;
        case  22:  msg_str = "SIGTTOU [22] - Background write to tty (POSIX)"; break;
        case  23:  msg_str = "SIGURG [23] - Urgent condition on socket (4.2 BSD). Signal sent when \"urgent\" or out-of-band data arrives on a socket."; break;
        case  24:  msg_str = "SIGXCPU [24] - CPU limit exceeded (4.2 BSD)."; break;
        case  25:  msg_str = "SIGXFSZ [25] - File size limit exceeded (4.2 BSD)."; break;
        case  26:  msg_str = "SIGVTALRM [26] - Virtual Time Alarm (4.2 BSD). Indicates expiration of a timer."; break;
        case  27:  msg_str = "SIGPROF [27] - Profiling alarm clock (4.2 BSD). Indicates expiration of a timer. Use for code profiling facilities."; break;
        case  28:  msg_str = "SIGWINCH [28] - Window size change (4.3 BSD, Sun)"; break;
        case  29:  msg_str = "SIGIO/SIGPOLL [29] - I/O now possible (4.2 BSD). Pollable event occurred (System V). Signal sent when file descriptor is ready to perform I/O (generated by sockets)."; break;
        case  30:  msg_str = "SIGPWR [30] - Power failure restart (System V)."; break;
        case  31:  msg_str = "SIGSYS [31] - Bad system call."; break;
        default :  msg_str = "Unknown signal."; 
    }
    
    CTracer::WriteError(msg_str);
    
    // Terminate program + signal propagation.
    exit(signum);
}