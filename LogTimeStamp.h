#ifndef LOGTIMESTAMP_H_
#define LOGTIMESTAMP_H_

#include <string>
#include <chrono>

namespace LOG{

class CTimeStamp{

public:
    CTimeStamp();
    CTimeStamp(int64_t microseconds);

    int64_t getMicroSeconds() const;
    
    static CTimeStamp now();

    static CTimeStamp addTime(CTimeStamp timestamp, double seconds);

    std::string toString() const;

    bool operator == (const CTimeStamp& rhs) const;

    bool operator > (const CTimeStamp& rhs) const;

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t m_micro_seconds;
};


}

#endif
