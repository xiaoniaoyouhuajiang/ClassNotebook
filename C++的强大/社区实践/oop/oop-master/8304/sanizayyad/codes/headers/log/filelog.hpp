#ifndef filelog_hpp
#define filelog_hpp

#include "adapter.hpp"

#include <fstream>
#include <cstdio>
#include <stdio.h>

class FileLog : public Adapter
{
public:
    explicit FileLog(const std::string& fileName);
    virtual void writeTo(const std::string& msg, TYPE type = TYPE::INFO) override;

private:
    std::string fileName;
};

#endif /* filelog_hpp */
