#ifndef memento_hpp
#define memento_hpp

#include <iostream>

class Memento {
 public:
    virtual std::string& state() const = 0;
};
#endif /* memento_hpp */
