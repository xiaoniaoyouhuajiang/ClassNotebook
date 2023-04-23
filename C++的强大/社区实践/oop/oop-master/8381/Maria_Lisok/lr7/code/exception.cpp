#include "exception.h"

FieldException::FieldException()
{
    error = "Field error:";
}

vector<size_t> FieldException::getParams()
{
    return params;
}

CoordsException::CoordsException(size_t xDest, size_t yDest, size_t widthField, size_t heightField)
{
    params.push_back(xDest);
    params.push_back(yDest);
    params.push_back(widthField);
    params.push_back(heightField);
    error += " coords (" + to_string(params[0]) + ";" + to_string(params[1]) + ") not part of the field " + to_string(params[2]) + "*" + to_string(params[3]);
}

const char *CoordsException::what() const throw()
{
    return error.c_str();
}

CellBusyExpeption::CellBusyExpeption(size_t x, size_t y)
{
    params.push_back(x);
    params.push_back(y);
    error += " on cell (" + std::to_string(x) + ";" + std::to_string(y) + ") already is object";
}

const char *CellBusyExpeption::what() const throw()
{
    return error.c_str();
}

SimpleFieldException::SimpleFieldException(string err)
{
    error += " " + err;
}

const char *SimpleFieldException::what() const throw()
{
    return error.c_str();
}

LandExeption::LandExeption(size_t x, size_t y)
{
    params.push_back(x);
    params.push_back(y);
    error += " on cell (" + std::to_string(x) + ";" + std::to_string(y) + ") not movable landscape";
}

const char *LandExeption::what() const throw()
{
    return error.c_str();
}
