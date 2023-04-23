#ifndef concretememento_hpp
#define concretememento_hpp

#include <stdio.h>
#include "memento.hpp"

class ConcreteMemento : public Memento
{
private:
    std::string& fout;

public:
    ConcreteMemento( std::string& fout)
        :fout(fout)
    {}

    std::string& state()const override {
        return fout;
    }

};

#endif /* concretememento_hpp */
