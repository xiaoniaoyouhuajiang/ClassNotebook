#ifndef OOP_LOGICALERROR_H
#define OOP_LOGICALERROR_H


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

#endif //OOP_LOGICALERROR_H
