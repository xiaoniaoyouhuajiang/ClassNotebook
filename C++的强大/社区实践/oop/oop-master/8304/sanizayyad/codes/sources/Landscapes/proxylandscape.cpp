#include "proxylandscape.hpp"

using namespace unit;

 ProxyLandscape::ProxyLandscape()
 {
     this->landscape = std::make_shared<PlainsLandscape>();
 }


 ProxyLandscape::ProxyLandscape(std::shared_ptr<Landscape> landscape)
 {
     this->landscape = landscape;
 }


 void ProxyLandscape::hurtUnit(std::shared_ptr<unit::Unit> unit) const
 {
     if (unit) {
         this->landscape->hurtUnit(unit);
     }
 }


 bool ProxyLandscape::canMove(std::shared_ptr<unit::Unit> unit) const
 {
     if (unit) {
         return this->landscape->canMove(unit);
     }

     return true;
 }


 std::shared_ptr<Landscape> ProxyLandscape::clone() const
 {
     return std::make_shared<ProxyLandscape>(this->landscape->clone());
 }


 char ProxyLandscape::draw() const
 {
     return landscape->draw();
 }
