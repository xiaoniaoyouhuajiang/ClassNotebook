#include "logs.h"

int SIZE = 1000;

Logs::~Logs() {}

FileLog::FileLog(QString filename) : filename(filename){}

void FileLog::log_data(QString data)
{
    std::ofstream f(filename.toStdString(), std::ios::binary|std::ios::app);
    f << data.toStdString();
    f.close();
}

CacheLog::CacheLog(FileLog &file_log) : file_log(file_log) {}

void CacheLog::log_data(QString data)
{
    if(cache.length() + data.length() < SIZE)
        file_log.log_data(cache + data);
    else
        cache += data;
}
