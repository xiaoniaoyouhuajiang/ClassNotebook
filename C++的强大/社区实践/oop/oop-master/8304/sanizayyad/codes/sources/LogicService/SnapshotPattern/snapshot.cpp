#include "snapshot.hpp"

#include "playgame.hpp"



void Snapshot::saveGame(const PlayGame& playGame)
{
    std::ofstream file("/Users/sourcecode/Documents/LabFolder/save.txt");
    std::stringstream out;

    auto pos = playGame.playerBase->getPosition();

    out << pos.x << " ";
    out << pos.y << " ";
    out << playGame.playerBase->getHealthPoints() << " ";
    out << playGame.playerBase->getNumberOfUnits() << "\n";

    for (auto unit : *playGame.playerUnits) {
        out << unit->getUnitName() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }

    pos = playGame.enemyBase->getPosition();

    out << pos.x << " ";
    out << pos.y << " ";
    out << playGame.enemyBase->getHealthPoints() << " ";
    out << playGame.enemyBase->getNumberOfUnits() << "\n";

    for (auto unit : *playGame.enemyUnits) {
        out << unit->getUnitName() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }


    file << out.str();
    file.close();
}


void Snapshot::loadGame(PlayGame& playGame)
{
    playGame.createBattleField();

    playGame.mediator = std::make_shared<Mediator>(playGame.battleField, playGame.log);

    playGame.playerUnits->clear();
    playGame.enemyUnits->clear();

    std::ifstream file("/Users/sourcecode/Documents/LabFolder/save.txt");

    std::stringstream stream;

    if (file.is_open()) {
        stream << file.rdbuf();
        file.close();
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
                                                     playGame.enemyBase, playGame.battleField, playGame.log);
    playGame.enemyFacade = std::make_shared<Facade>(playGame.mediator, playGame.playerBase, playGame.playerUnits,
                                                    playGame.enemyBase, playGame.battleField, playGame.log);

}
