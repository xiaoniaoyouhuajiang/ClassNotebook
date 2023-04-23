#ifndef CONCRETEMEMENTO_H
#define CONCRETEMEMENTO_H
#include "memento.h"

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

#endif // CONCRETEMEMENTO_H
