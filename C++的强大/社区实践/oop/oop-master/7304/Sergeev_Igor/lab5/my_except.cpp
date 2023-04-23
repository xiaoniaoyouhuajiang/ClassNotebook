#include "my_except.h"


 MyExcept::MyExcept(QString action_error, QString data_state) : action_error(action_error), data_state(data_state) {}

 QString MyExcept::get_action_error() const { return action_error; }

 QString MyExcept::get_data_state() const { return data_state; }

