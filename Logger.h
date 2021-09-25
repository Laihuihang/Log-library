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
    //װbuffer�Ķ���
    std::list<std::shared_ptr<LOG::CLogBuffer>>                  m_log_list;
    //д�뵽bufferָ��
    std::shared_ptr<LOG::CLogBuffer>                             m_current_read_buf;
    //����־д�뵽fileָ��
    std::shared_ptr<LOG::CLogBuffer>                             m_current_write_buf;
    //�ļ�������
    std::shared_ptr<LOG::CLog2File>                              m_file;
    //log·��
    std::string                                                  m_path;
    //log�ļ���С
    uintmax_t                                                    m_log_size;
    //��������
    std::condition_variable                                      m_cond;
    //��
    std::mutex                                                   m_mutex;
    //����־ˢ�������ϵ��̣߳��������߳�
    std::shared_ptr<std::thread>                                 m_flush_thread;
    //����־д��LogBuffer�е��̣߳��������߳�
    std::shared_ptr<std::thread>                                 m_write_thread;
    //�����̱߳�־λ
    bool                                                         m_flag;
};

#endif
