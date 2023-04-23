//
// Created by Artem Butko on 29.05.2020.
//

#ifndef OOP_NEW_LOGICALERROR_H
#define OOP_NEW_LOGICALERROR_H

#include <exception>
#include <string>

class LogicalError : public std::exception
{
private:
    std::string error;
public:
    LogicalError(std::string function, std::string error);
    LogicalError(std::string function, std::string error, std::string correct);
    LogicalError(std::string error, const char* correct);
    LogicalError(std::string error);
    const char* what() const noexcept override;
};


#endif //OOP_NEW_LOGICALERROR_H
