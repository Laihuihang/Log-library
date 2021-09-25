#ifndef LOGGER_H_
#define LOGGER_H_

#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>


#include "LogBuffer.h"
#include "Log2File.h"

class CLogger{

public:
    explicit CLogger();

    static CLogger* getInstance();

    static bool init();

    static void addToBuffer(const std::string msg);

    static void flushToFile(const LOG::CLogBuffer logbuffer);
    
private:
    //装buffer的队列
    std::list<std::shared_ptr<LOG::CLogBuffer>>                  m_log_list;
    //写入到buffer指针
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
    //将日志刷到磁盘上的线程，消费者线程
    std::shared_ptr<std::thread>                                 m_flush_thread;
    //将日志写到LogBuffer中的线程，生产者线程
    std::shared_ptr<std::thread>                                 m_write_thread;
    //开启线程标志位
    bool                                                         m_flag;
};

#endif
