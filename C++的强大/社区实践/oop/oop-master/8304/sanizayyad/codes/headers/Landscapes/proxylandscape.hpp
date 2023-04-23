#ifndef proxylandscape_hpp
#define proxylandscape_hpp

#include "landscape.hpp"
#include "plains.hpp"
#include "oceans.hpp"
#include "desert.hpp"


#include <stdio.h>


class ProxyLandscape : public Landscape
{
public:
    explicit ProxyLandscape();
    explicit ProxyLandscape(std::shared_ptr<Landscape> landscape);

    virtual void hurtUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual bool canMove(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<Landscape> clone() const override;

    virtual char draw() const override;

private:
    std::shared_ptr<Landscape> landscape;
};

#endif /* proxylandscape_hpp */

