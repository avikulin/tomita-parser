//---avikulin-- add dependancy to log4cpp logging framework
#include <library/tracer/CTracer.h>

//---avikulin-- original dependancies--
#include <util/system/progname.h>
#include <FactExtract/Parser/textminerlib/processor.h>
#include "aftextminer.h"

using namespace ExceptionTrace;

int main(int argc, char* argv[])
{
    SAVE_PROGRAM_NAME;

    //---avikulin-- Init logging engine
    
    CTracer::LogInit();
    
    //---avikulin --- Output to log program entry point.
    CTracer::WriteInfo("Program started...");
      
    CProcessor processor;
    if (!processor.Init(argc, argv)) {
        processor.m_Parm.PrintParameters();
        return 1;
    }
    if (!processor.Run()) {
        return 1;
    }

    //---avikulin --- Output to log
    CTracer::WriteInfo("Program finished normally...");
    
    return 0;
}
