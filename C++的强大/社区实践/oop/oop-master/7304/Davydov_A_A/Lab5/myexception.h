#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <QString>
using namespace std;

class MyException : public exception
{
public:
    MyException(QString action_error, QString data_state);
    QString get_action_error() const;
    QString get_data_state() const ;
private:
    QString action_error;
    QString data_state;
};

#endif // MYEXCEPTION_H
