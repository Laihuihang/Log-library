#include "Logger.h"

using namespace LOG;

CLogger::CLogger( const std::string path, const std::string exename, const uintmax_t maxSize )
{  
    bool ret = init( path, exename, maxSize );
    assert( ret == true );
}

CLogger* CLogger::getInstance( const std::string path, const std::string exename, const uintmax_t maxSize, const LEVEL level )
{
    static CLogger log( path, exename, maxSize );
    return &log;
}

bool CLogger::init( const std::string path, const std::string exename, const uintmax_t maxSize, const LEVEL level )
{
    m_log_list.clear();
    m_current_read_buf = std::make_shared<LOG::CLogBuffer>();
    m_current_write_buf = std::make_shared<LOG::CLogBuffer>();
    m_file = std::make_shared<LOG::CLog2File>( exename, path, maxSize );
    m_path = path;
    m_log_size = maxSize;
    m_thread_flag = true;
    m_output_form = ONLYFILE;
    m_level = level;
    return true;
}

void CLogger::addToBuffer(const std::string msg)
{
    //如果当前buffer中剩余的容量不足放下msg，则新建立一个buffer，放到新buffer中
    if( m_log_list.back()->getRemain() < msg.length() )
    {
        m_log_list.emplace_back( std::make_shared<LOG::CLogBuffer>() );
    }
    m_log_list.back()->append(msg);
}

void CLogger::flushToFile(const LOG::CLogBuffer logbuffer)
{

}


bool CLogger::setLogSize(const uintmax_t size)
{
    if( m_file.get() != NULL ){

    }
}