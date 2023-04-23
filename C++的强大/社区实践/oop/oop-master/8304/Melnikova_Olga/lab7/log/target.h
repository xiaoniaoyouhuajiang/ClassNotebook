#ifndef TARGET_H
#define TARGET_H
#pragma once
#include "iostream"

class Target
{
public:
  virtual ~Target() = default;

    virtual bool Request(std::string str) const {
        return true;
      }
};

#endif // TARGET_H
