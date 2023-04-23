#ifndef command_hpp
#define command_hpp

#include <stdio.h>
#include <iostream>
#include "battlefield.hpp"
#include "adapter.hpp"
#include "unitlog.hpp"
#include "base.hpp"
#include <math.h>

class Command
{
public:
    virtual void Execute() = 0;
    virtual ~Command();
};


#endif /* command_hpp */
