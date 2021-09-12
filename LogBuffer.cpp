#include "LogBuffer.h"

namespace LOG{

CLogBuffer::CLogBuffer(const uint64_t size):
     m_size(size)
    ,m_data("")
    ,m_cur_pos(0)
    ,m_remain(size)
    ,m_status(Empty)
{

}

bool CLogBuffer::empty()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_remain == m_size;
}

bool CLogBuffer::append(const std::string str)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(str.length() >= m_remain){
        setStatus(FULL);
        m_remain = 0;
        m_cur_pos = m_size;
        return false;
    }else{
        m_data.append(str);
        setStatus(NotEmpty);
        m_remain -= str.length();
        m_cur_pos += str.length();
        return true;
    }
}

Status CLogBuffer::getStatus()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_status;
}

uint64_t CLogBuffer::getSize()
{
    return m_size;
}

uint64_t CLogBuffer::getCurPos()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_cur_pos;
}

std::string CLogBuffer::getData()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_data;
}

void CLogBuffer::setStatus(const Status status)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_status = status;
}


} //LOG