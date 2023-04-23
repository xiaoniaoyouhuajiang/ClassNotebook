#ifndef LAB2_TYPEERROR_H
#define LAB2_TYPEERROR_H
#include <exception>
#include <string>

class TypeError : public std::exception {
private:
    std::string message_error;
public:
    TypeError(std::string, std::string);
    [[nodiscard]] const char* what() const noexcept override;
};


#endif
