#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;
class Exception : public exception
{
public:
    Exception()=default;
    ~Exception()=default;
    virtual const char* what() const throw() = 0;
    virtual vector<size_t> getParams() = 0;
protected:
    string error;
    vector<size_t> params;

};
class FieldException : public Exception{
public:
    FieldException();
    ~FieldException()=default;
    virtual const char* what() const noexcept override = 0;
    vector<size_t> getParams();
};
class CoordsException : public FieldException{
public:
    CoordsException(size_t xDest, size_t yDest, size_t widthField, size_t heightField);
    ~CoordsException() = default;
    const char* what() const noexcept override;
};
class CellBusyExpeption : public FieldException{
public:
    CellBusyExpeption(size_t x, size_t y);
    ~CellBusyExpeption() = default;
    const char* what() const noexcept override;
};
class SimpleFieldException final : public FieldException
{
public:
    SimpleFieldException(std::string error);
    ~SimpleFieldException() = default;
    const char* what() const noexcept override;
};
class LandExeption : public FieldException{
public:
    LandExeption(size_t x, size_t y);
    ~LandExeption() = default;
    const char* what() const noexcept override;
};



#endif // EXCEPTION_H
