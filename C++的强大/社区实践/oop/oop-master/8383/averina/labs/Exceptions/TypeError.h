#ifndef OOP_TYPEERROR_H
#define OOP_TYPEERROR_H

#include <exception>
#include <string>

class TypeError : public std::exception
{
private:
    std::string error;
public:
    TypeError(std::string function, std::string error);
    TypeError(std::string function, std::string error, std::string correct);
    TypeError(std::string error, const char* correct);
    TypeError(std::string error);
    const char* what() const noexcept override;
};


#endif //OOP_TYPEERROR_H
