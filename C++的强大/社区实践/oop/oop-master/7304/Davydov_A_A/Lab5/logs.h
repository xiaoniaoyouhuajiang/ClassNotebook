#ifndef LOGS_H
#define LOGS_H

#include <QString>
#include <fstream>

extern int SIZE;

class Logs
{
public:
    virtual ~Logs();
    //interface
    virtual void log_data(QString data) = 0;
};

class FileLog : public Logs
{
public:
    FileLog(QString filename);
    void log_data(QString data) override;
private:
    QString filename;
};

class CacheLog : public Logs
{
public:
    CacheLog(FileLog &file_log);
    void log_data(QString data) override;
private:
    FileLog &file_log;
    QString cache;
};

#endif // LOGS_H
