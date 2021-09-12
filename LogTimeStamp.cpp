#include "LogTimeStamp.h"

namespace LOG{


CTimeStamp::CTimeStamp()
    :m_micro_seconds(0)
{

}

CTimeStamp::CTimeStamp(int64_t microseconds)
    :m_micro_seconds(microseconds)
{

}

int64_t CTimeStamp::getMicroSeconds() const
{
    return m_micro_seconds;
}

CTimeStamp CTimeStamp::now()
{
    uint64_t timestamp;
    timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return CTimeStamp(timestamp);
}

CTimeStamp addTime(CTimeStamp timestamp, double seconds)
{
    int64_t delta = static_cast<int64_t>(seconds * CTimeStamp::kMicroSecondsPerSecond);
    return CTimeStamp(timestamp.getMicroSeconds() + delta);
}

std::string CTimeStamp::toString() const
{
    //获取 2021-01-12 12.31.24 格式日期
    char date[26];
    time_t sec = 0;
    time_t now_sec = m_micro_seconds / 1000000;
    if(now_sec > sec){
        sec = now_sec;
        struct tm time;
        localtime_r(&sec, &time);
        strftime(date, sizeof(date), "%Y-%m-%d %H.%M.%S", &time);
    }

    char str[28];
    auto micro = static_cast<uint32_t>(m_micro_seconds % 1000000);
    snprintf(str, sizeof(str) ,"%s.%06u", date, micro);
    return str;
}

bool CTimeStamp::operator == (const CTimeStamp& rhs) const
{

}

bool CTimeStamp::operator > (const CTimeStamp& rhs) const
{

}

}//LOG