#pragma once

#include <memory>

#include "../Units/Unit.hpp"

class UnitInfoScreen {
public:
    explicit UnitInfoScreen(std::shared_ptr<const Unit> unit);

    void draw() const;
    void handleEvents();
    bool needToClose() const;

private:
    std::shared_ptr<const Unit> m_unit;
    bool m_needToClose = false;
};
