#ifndef ADAPTER_H
#define ADAPTER_H
#pragma once
#include "target.h"
#include "proxy.h"

class Adapter : public Target
{
public:
    Proxy* write_;
    Adapter(Proxy* write) : write_(write) {}
      bool Request(std::string str) const override {
        this->write_->SpecificRequest(str);
        return true;
      }
};

#endif // ADAPTER_H
