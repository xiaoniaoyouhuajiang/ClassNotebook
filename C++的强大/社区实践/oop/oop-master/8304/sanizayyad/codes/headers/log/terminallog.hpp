#ifndef terminallog_hpp
#define terminallog_hpp

#include "adapter.hpp"


#include <stdio.h>
#include <iostream>


class TerminalLog: public Adapter
{
public:
    explicit TerminalLog() = default;

    virtual void writeTo(const std::string& msg, TYPE type = TYPE::INFO) override;
};

#endif /* terminallog_hpp */
