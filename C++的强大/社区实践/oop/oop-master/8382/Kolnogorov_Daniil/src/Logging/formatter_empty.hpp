#pragma once

#include "formatter.hpp"
#include <string>

class FormatterEmpty : public LogFormatter {
public:
    string format(string str) override { return str; }
};
