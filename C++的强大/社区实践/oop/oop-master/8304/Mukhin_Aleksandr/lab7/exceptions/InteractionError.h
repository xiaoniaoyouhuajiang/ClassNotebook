#ifndef LAB2_INTERACTIONERROR_H
#define LAB2_INTERACTIONERROR_H


#include <exception>
#include <string>

class InteractionError : public std::exception {
private:
    std::string message_error;
public:
    InteractionError(std::string, int, int, int, int);
    InteractionError(std::string, int, int);
    [[nodiscard]] const char* what() const noexcept override;
};


#endif
