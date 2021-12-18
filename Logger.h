#ifndef LOGGER_H_
#define LOGGER_H_

#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>
#include <assert.h>


#include "LogBuffer.h"
#include "Log2File.h"

namespace LOG{

#define MAXFILESIZE (1 << 26) //64MB
 
enum OUTPUTFORM{
    ONLYFILE = 0,
    ONLYTERMINAL,
    FIELAMDTERMINAL,
    NOOUTPUT
};

enum LEVEL{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
};

class CLogger{

public:

    static CLogger* getInstance( const std::string path, const std::string exename, const uintmax_t maxSize, const LEVEL level = DEBUG );

    bool init( const std::string path, const std::string exename, const uintmax_t maxSize = MAXFILESIZE, const LEVEL level );

    void addToBuffer(const std::string msg);

    void flushToFile(const LOG::CLogBuffer logbuffer);

    bool setLogSize(const uintmax_t size);


private:
    CLogger( const std::string path, const std::string exename, const uintmax_t maxSize );

    
private:
    //装buffer的队列
    std::list<std::shared_ptr<LOG::CLogBuffer>>                  m_log_list;
    //写入buf指针
    std::shared_ptr<LOG::CLogBuffer>                             m_current_read_buf;
    //将日志写入到file指针
    std::shared_ptr<LOG::CLogBuffer>                             m_current_write_buf;
    //文件操作类
    std::shared_ptr<LOG::CLog2File>                              m_file;
    //log路径
    std::string                                                  m_path;
    //log文件大小
    uintmax_t                                                    m_log_size;
    //条件变量
    std::condition_variable                                      m_cond;
    //锁
    std::mutex                                                   m_mutex;
    //消费者线程，刷到文件中
    std::shared_ptr<std::thread>                                 m_flush_thread;
    //生产者线程，将日志写到buf中
    std::shared_ptr<std::thread>                                 m_write_thread;
    //开启线程标志位
    bool                                                         m_thread_flag;
    //输出形式
    OUTPUTFORM                                                   m_output_form;
    //日志等级
    LEVEL                                                        m_level;
};

}

#endif
