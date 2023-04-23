#pragma once
#include <exception>
#include <string>

struct my_exceptions : std::exception
{
    my_exceptions(std::string const& data_) : data_(data_)
    { }
    const char* what() const noexcept
    {
        return data_.c_str();
    }

private:
    std::string data_;
};

