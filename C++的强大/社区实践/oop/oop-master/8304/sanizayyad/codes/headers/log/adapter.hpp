#ifndef log_hpp
#define log_hpp

#include <stdio.h>
#include <time.h>
#include <string>


enum class TYPE : int
{
    INFO,
    DBG,
    WARNING,
    ERR
};

class Adapter {
public:
   virtual ~Adapter() = default;

    virtual void writeTo(const std::string& msg, TYPE type = TYPE::INFO) = 0;
    
protected:
    std::string getCurrentTime() const;
    std::string getMessageType(TYPE type) const;
};


#endif /* log_hpp */
