#ifndef PROXYLANDSCAPE_H
#define PROXYLANDSCAPE_H

#include "roadlandscape.h"


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

#endif // PROXYLANDSCAPE_H
