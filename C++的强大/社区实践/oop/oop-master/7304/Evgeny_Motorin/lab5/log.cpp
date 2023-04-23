#include "log.h"

int BUFFER_SIZE = 100;

Log::~Log() {}

FileLog::FileLog(QString filename) : filename(filename){}

FileLog::~FileLog() {}

void FileLog::log_data(QString data) {
    std::ofstream f(filename.toStdString(), std::ios::binary|std::ios::app);
    f << data.toStdString();
    f.close();
}

FileLog & FileLog::get_instance() {
    static FileLog f("logs.txt");

    return f;
}

CacheLog::CacheLog(FileLog &file_log) : file_log(file_log) {}

CacheLog::~CacheLog() {
    if (!cache.isEmpty()) {
        file_log.log_data(cache);
    }
}

void CacheLog::log_data(QString data) {
    auto _data = QString::number(QDateTime::currentSecsSinceEpoch()) + " : " + data;
    session_logs += _data;
    if(cache.length() + data.length() > BUFFER_SIZE) {
        file_log.log_data(cache + _data);
        cache.clear();
    }
    else
        cache += _data;
}

CacheLog & CacheLog::get_instance() {
    static CacheLog c(FileLog::get_instance());
    return c;
}

QString CacheLog::get_session_logs() {
    return session_logs;
}
