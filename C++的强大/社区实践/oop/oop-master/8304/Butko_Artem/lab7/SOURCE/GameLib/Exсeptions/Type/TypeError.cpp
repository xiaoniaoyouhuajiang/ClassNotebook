//
// Created by Artem Butko on 29.05.2020.
//

#include "TypeError.h"

TypeError::TypeError(std::string function, std::string error)
{
    this->error = "<error> : type error with parameter " + error + " in " + function + ".\n";
}

TypeError::TypeError(std::string function, std::string error, std::string correct)
{
    this->error = "<error> : type error with parameter " + error + " in " + function + ", expected -- " + correct + ".\n";
}

TypeError::TypeError(std::string error, const char *correct)
{
    this->error = "<error> : type error with parameter " + error + ", expected -- " + correct + ".\n";
}

TypeError::TypeError(std::string error)
{
    this->error = "<error> : type error with parameter " + error + ".\n";
}

const char *TypeError::what() const noexcept
{
    return error.c_str();
}
