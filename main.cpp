#include "LogBuffer.h"
#include "LogTimeStamp.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace LOG;

int main()
{
    //CTimeStamp stamp(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    std::cout << CTimeStamp::now().toString() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << CTimeStamp::now().toString() << std::endl;
    
    return 0;
}