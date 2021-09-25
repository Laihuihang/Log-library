#include "Log2File.h"

using namespace LOG;

CLog2File::CLog2File(const std::string exename, const std::string path, uintmax_t size)
    :m_max_size(size)
    ,m_logpath(path)
{
    //检查文件夹是否存在，如不存在则创建
    if( 0 != access( path.c_str(), F_OK ) ){
        ::mkdir( path.c_str(),  0755 );
    }
    m_cur_filename = CTimeStamp::now().toString() + "(" + std::to_string(N) + ")." + exename + ".log";
}

//输入为完整的地址, 如文件存在返回文件大小，如文件不存在返回-1
std::intmax_t CLog2File::getFileSize(const std::string filename)
{
    std::uintmax_t ret = 0;
    FILE *file = fopen( filename.c_str(), "r" );
    if( file != NULL ){
        struct stat64 buf;
        int fd = fileno(file);
        fstat64(fd, &buf);
        ret = buf.st_size;
    }else{
        ret = -1;
    }
    fclose(file);
    return ret;
}

//向文件中写入msg
void CLog2File::writeMsg(const std::string msg)
{

    //文件存在, 且写满了
    if( m_max_size < getFileSize( m_logpath + "/" + m_cur_filename ) ){
        if( m_file.is_open() ){
            m_file.close();
        }
        N++;
    }
    if( !m_file.is_open() ){
        m_file.open( m_logpath + "/" + m_cur_filename, std::ios::binary | std::ios::app | std::ios::in | std::ios::out );
    }
    m_file << msg;
}