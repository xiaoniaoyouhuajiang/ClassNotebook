#include "LogicalError.h"



LogicalError::LogicalError(std::string error, const char* correct)
{
    this->error = "<error> : logical error with parameter " + error + ", expected -- " + correct + ".\n";
}


LogicalError::LogicalError(std::string error)
{
    this->error = "<error> : logical error with parameter " + error + ".\n";
}



LogicalError::LogicalError(std::string function, std::string error)
{
    this->error = "<error> : logical error with parameter " + error + " in " + function + ".\n";
}