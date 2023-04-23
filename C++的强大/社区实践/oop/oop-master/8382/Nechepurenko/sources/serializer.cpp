#include "../headers/serializer.hpp"
#include "../headers/game.hpp"
#include "../headers/neutral.hpp"
#include "../headers/exceptions.hpp"

Serializer::Serializer(std::string path) {
    file.open(path, std::ios_base::out);
    if (!file.is_open()){
        throw FileErrorException(path, 1);
    }
}

void Serializer::serialize() {
    auto gc = GameSingleton::getGameController();
    auto map = gc->getMap();
    auto objectStorage = gc->getObjectStorage();
    auto radiant = gc->getRadiantBase();
    auto dire = gc->getDireBase();
    auto logger = gc->getLogger();
    file << map->getHeight() << " " << map->getWidth() << "\n";
    for (int i = 0; i < map->getHeight(); i++) {
        for (int j = 0; j < map->getWidth(); j++){
            file << map->getMapCell(i, j)->getLandScape()->repr();
        } file << "\n";
    }
    file << radiant->getMax() << " " << radiant->getCreated() << " " << radiant->getCurrent() << " " << radiant->getDied() << "\n";
    for (auto unit : radiant->getUnits()) {
        file << unit->getType() << " " << unit->getName() << " " << unit->getHealth();
        file << " " << unit->getArmor() << " " << unit->getDamage() << " ";
        auto coords = objectStorage->getCoords(unit);
        file << coords.first << " " << coords.second << "\n";
    }
    file << dire->getMax() << " " << dire->getCreated() << " " << dire->getCurrent() << " " << dire->getDied() << "\n";
    for (auto unit : dire->getUnits()) {
        file << unit->getType() << " " << unit->getName() << " " << unit->getHealth();
        file << " " << unit->getArmor() << " " << unit->getDamage() << " ";
        auto coords = objectStorage->getCoords(unit);
        file << coords.first << " " << coords.second << "\n";
    }
    file << (int)objectStorage->getNeutral().size() - 1 << "\n";
    for (auto neutral_pair : objectStorage->getNeutral()) {
        NeutralObject* neutral = dynamic_cast<NeutralObject*>(neutral_pair.first);
        if (!neutral)
            continue;
        auto coords = neutral_pair.second->getCoords();
        file << neutral->getType() << " " << neutral->getAmount() << " " << coords.first << " " << coords.second << "\n";
        std::cout << neutral->getType() << " " << neutral->getAmount() << " " << coords.first << " " << coords.second << "\n";
    }
    if (radiant == gc->getCurrentBase())
        file << 1 << " ";
    else
        file << 0 << " ";
    auto coords = objectStorage->getCoords(radiant->getCurrentUnit());
    if (coords.first == -1){
        file << -1 << " " << -1 << " ";
    } else {
        file << coords.first << " " << coords.second << " ";
    }
    coords = objectStorage->getCoords(dire->getCurrentUnit());
    if (coords.first == -1){
        file << -1 << " " << -1 << "\n";
    } else {
        file << coords.first << " " << coords.second << " ";
    }
    logger->appendBuffer(std::string("Game saved successfully!\n"));
}

Serializer::~Serializer() {
    file.close();
}

Unserializer::Unserializer(std::string path) {
    file.open(path, std::ios_base::in);
    if (!file.is_open()){
        throw FileErrorException(path, 0);
    }
}
void Unserializer::unserialize() {
    GameSingleton::deleteGameController();
    int y = 0, x = 0;
    file >> y >> x;
    if (y <= 0 || x <= 0)
        throw UnserializerException(1);
    auto gc = GameSingleton::getGameController(y, x);
    auto map = gc->getMap();
    char land;
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++) {
            file >> land;
            if (land == '\n')
                file >> land;
            if (land == 'T')
                map->getMapCell(i,j)->setLandScape(new Tree());
            if (land == 'E')
                map->getMapCell(i,j)->setLandScape(new Earth());
            if (land == 'G')
                map->getMapCell(i,j)->setLandScape(new Grass());
        }
    }
    auto radiant = gc->getRadiantBase();
    int arg1, arg2, arg3, arg4, arg5;
    file >> arg1 >> arg2 >> arg3 >> arg4;
    radiant->setMax(arg1);
    radiant->setCurrent(arg2);
    radiant->setCreated(arg3);
    radiant->setDied(arg4);
    int ot, health, armor, damage, y_pos, x_pos;
    std::string name;
    for (int i = 0; i < arg3; i++) {
        file >> ot >> name >> health >> armor >> damage >> y_pos >> x_pos;
        ObjectType type = static_cast<ObjectType>(ot);
        Unit* u = radiant->createUnit(type, new UnitParamList(
            type, name, health, armor, damage
        ));
        gc->moveObject(u, map->getMapCell(y_pos, x_pos));
    }
    auto dire = gc->getDireBase();
    file >> arg1 >> arg2 >> arg3 >> arg4;
    dire->setMax(arg1);
    dire->setCurrent(arg2);
    dire->setCreated(arg3);
    dire->setCreated(arg4);
    for (int i = 0; i < arg3; i++) {
        file >> ot >> name >> health >> armor >> damage >> y_pos >> x_pos;
        ObjectType type = static_cast<ObjectType>(ot);
        Unit* u = dire->createUnit(type, new UnitParamList(
            type, name, health, armor, damage
        ));
        gc->moveObject(u, map->getMapCell(y_pos, x_pos));
    }
    file >> arg1;
    for (int i = 0; i < arg1; i++) {
        file >> ot >> health >> y_pos >> x_pos;
        ObjectType type = static_cast<ObjectType>(ot);
        gc->getObjectStorage()->registerNeutral(new NeutralObject(type, health), map->getMapCell(y_pos, x_pos));
    }
    file >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
    if (arg1 == 1) {
        gc->setBase(radiant);
    } else {
        gc->setBase(dire);
    }
    if (arg2 == -1 && arg3 == -1) {
        radiant->setCurrentUnit(nullptr);
    } else {
        radiant->setCurrentUnit(dynamic_cast<Unit*>(map->getMapCell(arg2, arg3)->getObject()));
    }
    if (arg4 == -1 && arg5 == -1) {
        dire->setCurrentUnit(nullptr);
    } else {
        dire->setCurrentUnit(dynamic_cast<Unit*>(map->getMapCell(arg4, arg5)->getObject()));
    }
    gc->setCurrentHero(gc->getCurrentBase()->getCurrentUnit());
    gc->getLogger()->appendBuffer(std::string("Game loaded successfully!\n"));
}

Unserializer::~Unserializer() {
    file.close();
}