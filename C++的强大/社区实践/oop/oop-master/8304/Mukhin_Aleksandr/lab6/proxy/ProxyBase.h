#ifndef LAB2_PROXYBASE_H
#define LAB2_PROXYBASE_H

#include "Base.h"

class ProxyBase : public AbstractionBase {
private:
    Base* base = nullptr;
public:
    ProxyBase() = default;
    explicit ProxyBase(Base* b) : base(b) {}
    void add_unit(std::shared_ptr<Unit>&) override;
    void get_base() override;
};


#endif
