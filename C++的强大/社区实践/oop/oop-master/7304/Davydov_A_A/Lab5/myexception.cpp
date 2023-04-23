#include "myexception.h"

MyException::MyException(QString action_error, QString data_state) : action_error(action_error),
    data_state(data_state) {}

QString MyException::get_action_error() const { return action_error; }

QString MyException::get_data_state() const { return data_state; }
