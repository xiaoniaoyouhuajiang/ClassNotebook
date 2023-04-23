#ifndef MYEXCEPT_H
#define MYEXCEPT_H

#include <exception>
#include <QString>
using namespace std;

class MyExcept : public exception
{
public:
    MyExcept(QString action_error, QString data_state);
    QString get_action_error() const;
    QString get_data_state() const ;
    virtual ~MyExcept() throw(){}
    QString action_error;
    QString data_state;
};

 #endif // MYEXCEPT_H
