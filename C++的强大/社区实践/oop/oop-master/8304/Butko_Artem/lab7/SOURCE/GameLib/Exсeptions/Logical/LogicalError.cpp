//
// Created by Artem Butko on 29.05.2020.
//

#include "LogicalError.h"

LogicalError::LogicalError(std::string function, std::string error)
{
    this->error = "<error> : logical error with parameter " + error + " in " + function + ".\n";
}

LogicalError::LogicalError(std::string function, std::string error, std::string correct)
{
    this->error = "<error> : logical error with parameter " + error + " in " + function + ", expected -- " + correct + ".\n";
}

LogicalError::LogicalError(std::string error, const char* correct)
{
    this->error = "<error> : logical error with parameter " + error + ", expected -- " + correct + ".\n";
}


LogicalError::LogicalError(std::string error)
{
    this->error = "<error> : logical error with parameter " + error + ".\n";
}

const char* LogicalError::what() const noexcept
{
    return error.c_str();
}



