#include <exception>
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

struct HandlerStructureException : public std::exception {
   const char * what () const throw () {
      return "Error: the 2 handlers has different structure (different number of inp/out)";
   }
};

struct TypeException : public std::exception {
   const char * what () const throw () {
      return "Error: Type mismatch";
   }
};

struct InputFormatException : public std::exception {
   const char * what () const throw () {
      return "Error: Invalid input format ";
   }
};

struct HandlerNotFoundException : public std::exception {
   const char * what () const throw () {
      return "Error: Cannot find handler with this id";
   }
};
#endif // MYEXCEPTION_H
