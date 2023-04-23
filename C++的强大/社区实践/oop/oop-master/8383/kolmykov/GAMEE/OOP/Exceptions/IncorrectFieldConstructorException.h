#ifndef INCORRECTFIELDCONSTRUCTOREXCEPTION_H
#define INCORRECTFIELDCONSTRUCTOREXCEPTION_H


#include <ostream>


class IncorrectFieldConstructorException
{
private:
    int w;
    int h;
public:
    IncorrectFieldConstructorException(int w, int h);
    friend std::ostream& operator<< (std::ostream &out, const IncorrectFieldConstructorException exeption);
};

#endif // INCORRECTFIELDCONSTRUCTOREXCEPTION_H
