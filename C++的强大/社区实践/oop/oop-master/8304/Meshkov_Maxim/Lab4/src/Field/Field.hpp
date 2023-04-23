#pragma once

#include <memory>

#include "../TwoDimensionalArray.hpp"
#include "../Units/UnitFactory.hpp"
#include "../Terrains/TerrainFactory.hpp"
#include "FieldCell.hpp"
#include "../FieldPosition.hpp"
#include "FieldIterator.hpp"

class Field {
public:
    Field(int width, int height);
    Field(const Field &other);
    Field(Field &&other) noexcept;
    Field &operator=(const Field &other);
    Field &operator=(Field &&other) noexcept;

    FieldIterator begin() const;
    FieldIterator end() const;

    int getWidth() const;
    int getHeight() const;

    std::shared_ptr<const FieldCell> getCell(FieldPosition position) const;
    std::shared_ptr<FieldCell> getCell(FieldPosition position);

    void createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition position);
    void moveUnit(FieldPosition unitPosition, FieldPosition targetPosition);

    void removeCreature(FieldPosition position);

    void setTerrain(const std::shared_ptr<const TerrainFactory> &terrainFactory, FieldPosition position);

    void createBase(FieldPosition basePosition, int player);

private:
    TwoDimensionalArray<std::shared_ptr<FieldCell>> m_cells;
};
