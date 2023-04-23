//
// Created by Artem Butko on 29.05.2020.
//

#ifndef OOP_NEW_OUTOFRANGEERROR_H
#define OOP_NEW_OUTOFRANGEERROR_H

#include <exception>
#include <string>

class OutOfRangeError : public std::exception
{
private:
    std::string error;
public:
    OutOfRangeError(std::string function, std::string error);
    OutOfRangeError(std::string function, std::string error, std::string correct);
    OutOfRangeError(std::string error, const char* correct);
    OutOfRangeError(std::string error);
    const char* what() const noexcept override;
};


#endif //OOP_NEW_OUTOFRANGEERROR_H
