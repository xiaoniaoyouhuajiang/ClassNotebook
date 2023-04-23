#include "originator.hpp"

#include "playgame.hpp"

using namespace unit;

Originator::Originator(std::string filePath) :filePath(filePath){
}


void Originator::doSomething(const PlayGame& playGame){
    std::ofstream out(filePath);
    std::stringstream ouputStream;

    auto pos = playGame.playerBase->getPosition();

    ouputStream << pos.x << " ";
    ouputStream << pos.y << " ";
    ouputStream << playGame.playerBase->getHealthPoints() << " ";
    ouputStream << playGame.playerBase->getNumberOfUnits() << "\n";

    for (auto unit : *playGame.playerUnits) {
        ouputStream << unit->getUnitName() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }

    pos = playGame.enemyBase->getPosition();

    ouputStream << pos.x << " ";
    ouputStream << pos.y << " ";
    ouputStream << playGame.enemyBase->getHealthPoints() << " ";
    ouputStream << playGame.enemyBase->getNumberOfUnits() << "\n";

    for (auto unit : *playGame.enemyUnits) {
        ouputStream << unit->getUnitName() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }


    out << ouputStream.str();
    out.close();
}
void Originator::Restore(PlayGame& playGame)
{
    playGame.createBattleField();

    playGame.mediator = std::make_shared<Mediator>(playGame.battleField, playGame.proxyLog);

    playGame.playerUnits->clear();
    playGame.enemyUnits->clear();

    std::ifstream fin(filePath);
    std::stringstream stream;

    if (fin.is_open()) {
        stream << fin.rdbuf();
        fin.close();
    }

    Position2D pos;
    double healthPoints = 0;
    size_t numberOfUnits = 0;

    stream >> pos.x;
    stream >> pos.y;
    stream >> healthPoints;
    stream >> numberOfUnits;

    playGame.playerBase = std::make_shared<Base>(pos, playGame.mediator,
                                             PLAYER::ONE, healthPoints);
    playGame.battleField->addUnit(playGame.playerBase);

    std::string unitName;
    for (size_t i = 0; i < numberOfUnits; ++i) {
        stream >> unitName;
        stream >> healthPoints;
        stream >> pos.x;
        stream >> pos.y;
        UnitStateSnap unitStateSnap;
        unitStateSnap.position = pos;
        unitStateSnap.unitName = unitName;
        unitStateSnap.healthPoints = healthPoints;

        auto unit = playGame.playerBase->createUnitFromSnaphot(unitStateSnap);
        playGame.playerUnits->insert(unit);
        playGame.battleField->addUnit(unit);
    }

    stream >> pos.x;
    stream >> pos.y;
    stream >> healthPoints;
    stream >> numberOfUnits;

    playGame.enemyBase = std::make_shared<Base>(pos, playGame.mediator,
                                            PLAYER::TWO, healthPoints);
    playGame.battleField->addUnit(playGame.enemyBase);

    for (size_t i = 0; i < numberOfUnits; ++i) {
        stream >> unitName;
        stream >> healthPoints;
        stream >> pos.x;
        stream >> pos.y;

        UnitStateSnap unitStateSnap;
        unitStateSnap.position = pos;
        unitStateSnap.unitName = unitName;
        unitStateSnap.healthPoints = healthPoints;

        auto unit = playGame.enemyBase->createUnitFromSnaphot(unitStateSnap);
        playGame.enemyUnits->insert(unit);
        playGame.battleField->addUnit(unit);
    }

    playGame.playerFacade = std::make_shared<Facade>(playGame.mediator, playGame.playerBase, playGame.playerUnits,
                                                     playGame.enemyBase, playGame.battleField, playGame.proxyLog);
    playGame.enemyFacade = std::make_shared<Facade>(playGame.mediator, playGame.playerBase, playGame.playerUnits,
                                                    playGame.enemyBase, playGame.battleField, playGame.proxyLog);

}
