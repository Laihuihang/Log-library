#include "Logger.h"

using namespace LOG;

explicit CLogger::CLogger()
{}

CLogger* CLogger::getInstance()
{

}

bool init();

void addToBuffer(const std::string msg);

void flushToFile(const LOG::CLogBuffer logbuffer);