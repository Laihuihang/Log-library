#ifndef LOG2FILE_H_
#define LOG2FILE_H_

#include <string>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


#include "LogTimeStamp.h"

//将日志刷到�?�盘�?

namespace LOG{

class CLog2File{

public:
    CLog2File(const std::string exename, const std::string path, uintmax_t size);

    std::intmax_t getFileSize(const std::string filename);

    void writeMsg(const std::string msg);


private:
    std::ofstream            m_file;
    std::string              m_logpath;
    uintmax_t                m_max_size;
    std::string              m_cur_filename;
    uint32_t                 N = 0;
};



}



#endif