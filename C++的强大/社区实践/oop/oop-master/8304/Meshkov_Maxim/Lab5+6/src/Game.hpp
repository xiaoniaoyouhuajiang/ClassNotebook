#pragma once

#include "GameInterface.hpp"

#include "Terrains/GroundTerrain.hpp"
#include "Terrains/StoneTerrain.hpp"
#include "Terrains/WaterTerrain.hpp"
#include "Things/MedicineThing.hpp"
#include "Things/MicroMedicineThing.hpp"
#include "Things/PowerfulMedicineThing.hpp"
#include "Things/SmallMedicineThing.hpp"
#include "Units/Archers/DistanceArcherUnit.hpp"
#include "Units/Archers/PowerfulArcherUnit.hpp"
#include "Units/Knights/HeavyKnightUnit.hpp"
#include "Units/Knights/LightweightKnightUnit.hpp"
#include "Units/Mages/FireMageUnit.hpp"
#include "Units/Mages/IceMageUnit.hpp"

#include <vector>

template <typename S, typename E> // S - game start rule, E - game end rule
class Game : public GameInterface {
private:
    Game() : m_field(new Field(0, 0)) {};
public:
    static std::shared_ptr<Game> getInstance() {
        static std::shared_ptr<Game> instance(new Game);
        return instance;
    }
    Game(const Game &) = delete;
    Game &operator=(const Game&) = delete;

    void start(int width, int height) override {
        S::startNewGame(this, m_field, width, height);
    }

    std::shared_ptr<const Field> getField() const override {
        return m_field;
    }

    FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) override {
        m_playerState->moveIsMade();
        auto base = m_field->getCell(basePosition)->getBase();
        if (base != nullptr)
            return base->createUnit(unitFactory, basePosition, *m_field);
        return {};
    }

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const override {
        auto unit = m_field->getCell(unitPosition)->getUnit();
        if (unit == nullptr)
            return {};
        return unit->findPossibleMoves(unitPosition, *m_field);
    }
    void move(FieldPosition unitPosition, FieldPosition targetPosition) override {
        auto possibleMoves = findPossibleMoves(unitPosition);
        if (possibleMoves.find(targetPosition) == possibleMoves.end())
            throw std::runtime_error("Impossible move.");
        m_field->moveUnit(unitPosition, targetPosition);
        if (auto thing = m_field->getCell(targetPosition)->getThing()) {
            auto unit = m_field->getCell(targetPosition)->getUnit();
            *unit << *thing;
            m_field->getCell(targetPosition)->setThing(nullptr);
        }
        m_playerState->moveIsMade();
    }

    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const override {
        auto unit = m_field->getCell(unitPosition)->getUnit();
        if (unit == nullptr)
            return {};
        return unit->findPossibleAttacks(unitPosition, *m_field);
    }
    void attack(FieldPosition attackerPosition, FieldPosition victimPosition) override {
        auto attacker = m_field->getCell(attackerPosition)->getUnit();
        if (attacker == nullptr)
            return;
        attacker->attack(victimPosition, *m_field);
        m_playerState->moveIsMade();
    }

    void setPlayerState(std::shared_ptr<PlayerState> playerState) override {
        m_playerState = playerState;
    }
    int getCurrentPlayer() const override {
        if (m_playerState == nullptr)
            return -1;
        return m_playerState->getPlayer();
    }

    bool gameOver(int &winner) const override {
        return E::gameOver(m_field, winner);
    }

    std::shared_ptr<GameMemento> createMemento() const override {
        auto memento = std::make_shared<GameMemento>();

        memento->currentPlayer = m_playerState->getPlayer();
        memento->fieldWidth = m_field->getWidth();
        memento->fieldHeight = m_field->getHeight();

        for (auto [cell, position] : *m_field) {
            {
                auto terrain = cell->getTerrain();
                typename GameMemento::TerrainType terrainType;
                if (dynamic_cast<const GroundTerrain *>(terrain.get()) != nullptr)
                    terrainType = GameMemento::TerrainType::GROUND;
                else if (dynamic_cast<const StoneTerrain *>(terrain.get()) != nullptr)
                    terrainType = GameMemento::TerrainType::STONE;
                else if (dynamic_cast<const WaterTerrain *>(terrain.get()) != nullptr)
                    terrainType = GameMemento::TerrainType::WATER;
                memento->terrains.push_back(terrainType);
            }


            if (auto base = cell->getBase()) {
                typename GameMemento::BaseInfo baseInfo;
                baseInfo.position = position;
                baseInfo.player = base->getPlayer().value();
                baseInfo.health = base->getHealth();
                baseInfo.creationAbility = base->getCreationAbility();
                memento->bases.push_back(baseInfo);
            }

            if (auto thing = cell->getThing()) {
                typename GameMemento::ThingType thingType;
                if (dynamic_cast<const MedicineThing*>(thing.get()) != nullptr)
                    thingType = GameMemento::ThingType::MEDICINE;
                else if (dynamic_cast<const MicroMedicineThing*>(thing.get()) != nullptr)
                    thingType = GameMemento::ThingType::MICRO;
                else if (dynamic_cast<const PowerfulMedicineThing*>(thing.get()) != nullptr)
                    thingType = GameMemento::ThingType::POWERFUL;
                else if (dynamic_cast<const SmallMedicineThing*>(thing.get()) != nullptr)
                    thingType = GameMemento::ThingType::SMALL;
                memento->things.push_back({position, thingType});
            }

            if (auto unit = cell->getUnit()) {
                typename GameMemento::UnitInfo unitInfo;

                if (dynamic_cast<const DistanceArcherUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::DISTANCE_ARCHER;
                else if (dynamic_cast<const PowerfulArcherUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::POWERFUL_ARCHER;
                else if (dynamic_cast<const HeavyKnightUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::HEAVY_KNIGHT;
                else if (dynamic_cast<const LightweightKnightUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::LIGHTWEIGHT_KNIGHT;
                else if (dynamic_cast<const FireMageUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::FIRE_MAGE;
                else if (dynamic_cast<const IceMageUnit*>(unit.get()) != nullptr)
                    unitInfo.type = GameMemento::UnitType::ICE_MAGE;

                unitInfo.position = position;
                unitInfo.player = unit->getPlayer().value();
                unitInfo.health = unit->getHealth();
                unitInfo.isIced = unit->isIced();

                memento->units.push_back(unitInfo);
            }
        }
        return memento;
    }
    void restoreFromMemento(const GameMemento &memento) override {
        m_playerState.reset(new PlayerState(memento.currentPlayer, this));
        m_field.reset(new Field(memento.fieldWidth, memento.fieldHeight));

        {
            int i = 0;
            for (auto [cell, position] : *m_field) {
                auto terrainType = memento.terrains[i];
                std::shared_ptr<TerrainFactory> terrainFactory;
                switch(terrainType) {
                    case GameMemento::TerrainType::GROUND:
                        terrainFactory.reset(new ConcreteTerrainFactory<GroundTerrain>);
                        break;
                    case GameMemento::TerrainType::STONE:
                        terrainFactory.reset(new ConcreteTerrainFactory<StoneTerrain>);
                        break;
                    case GameMemento::TerrainType::WATER:
                        terrainFactory.reset(new ConcreteTerrainFactory<WaterTerrain>);
                        break;
                }
                m_field->setTerrain(terrainFactory, position);
                i++;
            }
        }

        std::shared_ptr<Base> playersBases[2];
        for (auto baseInfo : memento.bases) {
            auto base = m_field->createBase(baseInfo.position, baseInfo.player);
            base->setHealth(baseInfo.health);
            base->setCreationAbility(baseInfo.creationAbility);
            playersBases[baseInfo.player] = base;
        }

        for (auto thingInfo : memento.things) {
            std::shared_ptr<Thing> thing;
            switch(thingInfo.type) {
                case GameMemento::ThingType::MEDICINE:
                    thing.reset(new MedicineThing);
                    break;
                case GameMemento::ThingType::MICRO:
                    thing.reset(new MicroMedicineThing);
                    break;
                case GameMemento::ThingType::POWERFUL:
                    thing.reset(new PowerfulMedicineThing);
                    break;
                case GameMemento::ThingType::SMALL:
                    thing.reset(new SmallMedicineThing);
                    break;
            }
            m_field->getCell(thingInfo.position)->setThing(thing);
        }

        for (auto unitInfo : memento.units) {
            std::shared_ptr<Unit> unit;

            switch(unitInfo.type) {
                case GameMemento::UnitType::DISTANCE_ARCHER:
                    unit.reset(new DistanceArcherUnit);
                    break;
                case GameMemento::UnitType::POWERFUL_ARCHER:
                    unit.reset(new PowerfulArcherUnit);
                    break;
                case GameMemento::UnitType::HEAVY_KNIGHT:
                    unit.reset(new HeavyKnightUnit);
                    break;
                case GameMemento::UnitType::LIGHTWEIGHT_KNIGHT:
                    unit.reset(new LightweightKnightUnit);
                    break;
                case GameMemento::UnitType::FIRE_MAGE:
                    unit.reset(new FireMageUnit);
                    break;
                case GameMemento::UnitType::ICE_MAGE:
                    unit.reset(new IceMageUnit);
                    break;
            }

            unit->setPlayer(unitInfo.player);
            unit->setHealth(unitInfo.health);
            unit->setIsIced(unitInfo.isIced);

            m_field->getCell(unitInfo.position)->setUnit(unit);

            unit->setBase(playersBases[unitInfo.player]);
        }
    }

private:
    std::shared_ptr<Field> m_field;
    std::shared_ptr<PlayerState> m_playerState;
};


