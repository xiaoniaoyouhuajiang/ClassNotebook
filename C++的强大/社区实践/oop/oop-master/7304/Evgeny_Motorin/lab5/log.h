#ifndef LOG_H
#define LOG_H



#include <QString>
#include <fstream>
#include <QDateTime>

extern int BUFFER_SIZE;

//interface
class Log {
public:
    virtual ~Log();
    virtual void log_data(QString data) = 0;
};

class FileLog : public Log {
public:
    void log_data(QString data) override;
    static FileLog & get_instance();
private:
    FileLog(QString filename);
    ~FileLog() override;
    FileLog(FileLog const &);
    FileLog const & operator = (FileLog const &);
    QString filename;
};

class CacheLog : public Log {
public:
    void log_data(QString data) override;
    static CacheLog & get_instance();
    QString get_session_logs();
private:
    QString session_logs;
    CacheLog(FileLog &file_log);
    ~CacheLog() override;
    CacheLog(CacheLog const &);
    CacheLog const & operator = (CacheLog const &);
    FileLog &file_log;
    QString cache;
};

#endif // LOG_H
