//
// Created by smokfyz on 21.05.19.
//

#ifndef XGAME_EXCEPTION_H
#define XGAME_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class Exception: public std::exception
{
public:
    explicit Exception(const char* message):
            msg_(message)
    {
    }

    explicit Exception(const string& message):
            msg_(message)
    {}

    virtual ~Exception() noexcept {}

    virtual const char* what() const noexcept {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};


#endif //XGAME_EXCEPTION_H
