#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <QString>
#include <exception>
using namespace std;

class CustomException: public exception {
public:
    CustomException(QString action_error, QString data_state);
    QString get_action_error() const;
    QString get_data_state() const ;
private:
    QString action_error;
    QString data_state;
};

#endif // CUSTOMEXCEPTION_H
