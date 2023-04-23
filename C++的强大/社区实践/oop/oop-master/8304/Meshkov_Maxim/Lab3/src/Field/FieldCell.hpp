#pragma once

#include <memory>

#include "../Units/Unit.hpp"
#include "../Terrains/Terrain.hpp"
#include "../Base.hpp"
#include "../Creature.hpp"
#include "../Things/Thing.hpp"

struct FieldCell {
    FieldCell();
    FieldCell(const FieldCell &other);
    FieldCell &operator=(const FieldCell &other);

    std::shared_ptr<Unit> getUnit() {
        return m_unit;
    }
    std::shared_ptr<const Unit> getUnit() const {
        return m_unit;
    }
    void setUnit(const std::shared_ptr<Unit> &unit) {
        m_unit = unit;
        m_base = nullptr;
    }

    std::shared_ptr<Terrain> getTerrain() {
        return m_terrain;
    }
    std::shared_ptr<const Terrain> getTerrain() const {
        return m_terrain;
    }
    void setTerrain(const std::shared_ptr<Terrain> &terrain) {
        if (terrain == nullptr) {
            throw std::invalid_argument("Error: terrain is nullptr.");
        }
        m_terrain = terrain;
    }

    std::shared_ptr<Base> getBase() {
        return m_base;
    }
    std::shared_ptr<const Base> getBase() const {
        return m_base;
    }
    void setBase(const std::shared_ptr<Base> &base) {
        m_base = base;
        m_unit = nullptr;
    }

    std::shared_ptr<const Creature> getCreature() const {
        if (m_unit != nullptr)
            return m_unit;
        return m_base;
    }
    std::shared_ptr<Creature> getCreature() {
        if (m_unit != nullptr)
            return m_unit;
        return m_base;
    }
    void removeCreature();
    bool canHoldSomething() const;

    std::shared_ptr<Thing> getThing() {
        return m_thing;
    }
    std::shared_ptr<const Thing> getThing() const {
        return m_thing;
    }
    void setThing(const std::shared_ptr<Thing> &thing) {
        m_thing = thing;
    }

private:
    std::shared_ptr<Unit> m_unit;
    std::shared_ptr<Terrain> m_terrain;
    std::shared_ptr<Base> m_base;
    std::shared_ptr<Thing> m_thing;
};
