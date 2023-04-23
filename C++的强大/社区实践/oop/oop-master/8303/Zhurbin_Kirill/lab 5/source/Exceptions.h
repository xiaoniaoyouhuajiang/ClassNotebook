#ifndef OOP1_EXCEPTIONS_H
#define OOP1_EXCEPTIONS_H
#include <exception>
#include <string>

class LogicException: public std::exception{
private:
    std::string error;

public:
    LogicException(std::string place, int param){
        error = "Error: logic exception in " + place + " with incorrect param " + std::to_string(param);
    }

    LogicException(std::string place, std::string param){
        error = "Error: logic exception in " + place + " with incorrect param " + param;
    }

    const char* what() const noexcept override {
        return error.c_str();
    }
};

class TypeInputException: public std::exception{
private:
    std::string error;

public:
    TypeInputException(std::string type){
        error = "Error: expected data type " + type + " but another was received";
    }

    const char* what() const noexcept override {
        return error.c_str();
    }
};

#endif //OOP1_EXCEPTIONS_H
