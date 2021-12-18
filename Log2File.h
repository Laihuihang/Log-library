#ifndef LOG2FILE_H_
#define LOG2FILE_H_

#include <string>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


#include "LogTimeStamp.h"

//日志刷到磁盘


namespace LOG{

#define MAXFILENUM 32

class CLog2File{

public:
    CLog2File(const std::string exename, const std::string path, uintmax_t maxSize);

    std::intmax_t getFileSize(const std::string filename);

    //刷缓存
    void fflush(const std::string msg);
    //返回目前文件的个数
    uint32_t getFileNum();

private:
    std::ofstream            m_file;
    std::string              m_logpath;
    uintmax_t                m_max_size;
    std::string              m_cur_filename;
    std::string              m_exename;
    //文件个数
    uint32_t                 N = 1;
};



}



#endif