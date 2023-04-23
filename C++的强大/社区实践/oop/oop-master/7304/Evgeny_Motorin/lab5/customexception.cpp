#include "customexception.h"

CustomException::CustomException(QString action_error, QString data_state) : action_error(action_error),
    data_state(data_state) {}

QString CustomException::get_action_error() const { return action_error; }

QString CustomException::get_data_state() const { return data_state; }

