#include "Game.hpp"

#include "Terrains/GroundTerrain.hpp"
#include "Terrains/StoneTerrain.hpp"
#include "Terrains/WaterTerrain.hpp"
#include "Terrains/ConcreteTerrainFactory.hpp"
#include "Base.hpp"
#include "Things/MedicineThing.hpp"
#include "Things/MicroMedicineThing.hpp"
#include "Things/SmallMedicineThing.hpp"
#include "Things/PowerfulMedicineThing.hpp"

constexpr float waterProbability = 0.1f;
constexpr float stoneProbability = 0.1f;
constexpr float thingProbability = 0.025f;

Game::Game()
    : m_field(new Field(0, 0))
{}

void Game::start(int width, int height) {
    m_field.reset(new Field(width, height));
    srand(time(0));
    for (auto [cell, position] : *m_field) {
        auto randomNumber = (float)rand() / RAND_MAX;
        if (randomNumber <= waterProbability) {
            m_field->setTerrain(std::make_shared<ConcreteTerrainFactory<WaterTerrain>>(), position);
        }
        else if (randomNumber <= waterProbability + stoneProbability) {
            m_field->setTerrain(std::make_shared<ConcreteTerrainFactory<StoneTerrain>>(), position);
        }
        else if (randomNumber <= waterProbability + stoneProbability + 1 * thingProbability) {
            m_field->getCell(position)->setThing(std::make_shared<MedicineThing>());
        }
        else if (randomNumber <= waterProbability + stoneProbability + 2 * thingProbability) {
            m_field->getCell(position)->setThing(std::make_shared<MicroMedicineThing>());
        }
        else if (randomNumber <= waterProbability + stoneProbability + 3 * thingProbability) {
            m_field->getCell(position)->setThing(std::make_shared<PowerfulMedicineThing>());
        }
        else if (randomNumber <= waterProbability + stoneProbability + 4 * thingProbability) {
            m_field->getCell(position)->setThing(std::make_shared<SmallMedicineThing>());
        }

    }

    int baseRow = height / 2;
    int baseColOffset = 5;
    m_field->createBase({baseRow, baseColOffset}, 0);
    m_field->createBase({baseRow, (width - 1) - baseColOffset}, 1);
}

std::shared_ptr<const Field> Game::getField() const {
    return m_field;
}

FieldPosition Game::createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) {
    auto base = m_field->getCell(basePosition)->getBase();
    if (base != nullptr)
        return base->createUnit(unitFactory, basePosition, *m_field);
    return {};
}

std::set<FieldPosition> Game::findPossibleMoves(FieldPosition unitPosition) const {
    auto unit = m_field->getCell(unitPosition)->getUnit();
    if (unit == nullptr)
        return {};
    return unit->findPossibleMoves(unitPosition, *m_field);
}

void Game::move(FieldPosition unitPosition, FieldPosition targetPosition) {
    auto possibleMoves = findPossibleMoves(unitPosition);
    if (possibleMoves.find(targetPosition) == possibleMoves.end())
        throw std::runtime_error("Impossible move.");
    m_field->moveUnit(unitPosition, targetPosition);
    if (auto thing = m_field->getCell(targetPosition)->getThing()) {
        auto unit = m_field->getCell(targetPosition)->getUnit();
        *unit << *thing;
        m_field->getCell(targetPosition)->setThing(nullptr);
    }
}

std::set<FieldPosition> Game::findPossibleAttacks(FieldPosition unitPosition) const {
    auto unit = m_field->getCell(unitPosition)->getUnit();
    if (unit == nullptr)
        return {};
    return unit->findPossibleAttacks(unitPosition, *m_field);
}

void Game::attack(FieldPosition attackerPosition, FieldPosition victimPosition) {
    auto attacker = m_field->getCell(attackerPosition)->getUnit();
    if (attacker == nullptr)
        return;
    attacker->attack(victimPosition, *m_field);
}
