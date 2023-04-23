//
// Created by Artem Butko on 29.05.2020.
//

#include "OutOfRangeError.h"

OutOfRangeError::OutOfRangeError(std::string function, std::string error)
{
    this->error = "<error> : out of range error with parameter " + error + " in " + function + ".\n";
}

OutOfRangeError::OutOfRangeError(std::string function, std::string error, std::string correct)
{
    this->error = "<error> : out of range error with parameter " + error + " in " + function + ", expected -- " + correct + ".\n";
}

OutOfRangeError::OutOfRangeError(std::string error, const char *correct)
{
    this->error = "<error> : out of range error with parameter " + error + ", expected -- " + correct + ".\n";
}

OutOfRangeError::OutOfRangeError(std::string error)
{
    this->error = "<error> : out of range error with parameter " + error + ".\n";
}

const char* OutOfRangeError::what() const noexcept
{
    return error.c_str();
}