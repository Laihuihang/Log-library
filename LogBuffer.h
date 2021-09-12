#ifndef LOGBUFFER_H_
#define LOGBUFFER_H_

#include <string>
#include <mutex>
#include <sstream>

namespace LOG{

enum Status{
        Empty = 0,
        NotEmpty = 1,
        FULL = 2
};

class CLogBuffer{

public:

    CLogBuffer(const uint64_t size);

    bool empty();

    bool append(const std::string str);

    Status getStatus();

    uint64_t getSize();
    
    uint64_t getCurPos();

    std::string getData();
private:
    void setStatus(const Status status);

private:
    std::mutex             m_mutex;
    uint64_t               m_cur_pos;
    uint64_t               m_remain;
    uint64_t               m_size;
    std::string            m_data;
    Status                 m_status;
};





}
#endif
