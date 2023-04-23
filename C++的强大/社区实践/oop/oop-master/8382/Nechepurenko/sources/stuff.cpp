#include "../headers/stuff.hpp"
#include "../headers/game.hpp"

void SimpleMove::move(Object* ao, Move direction){
    GameController* game_controller = GameSingleton::getGameController();
    auto [height, width] = game_controller->getObjectStorage()->getCoords(ao);
    std::shared_ptr<MapCell> cell;
    switch (direction) {
        case Move::UP: {
            cell = ableMove(height-1, width);
            break;
        }
        case Move::DOWN: {
            cell = ableMove(height+1, width);
            break;
        }
        case Move::LEFT: {
            cell = ableMove(height, width-1);
            break;
        }
        case Move::RIGHT: {
            cell = ableMove(height, width+1);
            break;
        }
    }
    if (cell){
        game_controller->moveObject(ao, cell);
    } else {
        game_controller->getLogger()->appendBuffer(std::string("Unable to move there!\n"));
    }
}

std::shared_ptr<MapCell> Moveable::ableMove(uint32_t y, uint32_t x){
    auto map = GameSingleton::getGameController()->getMap();
    auto width = map->getWidth();
    auto height = map->getHeight();
    if (y < height && x < width && x >= 0 && y >= 0 && map->getMapCell(y, x)->getObject() == nullptr) {
        auto cell = map->getMapCell(y, x);
        auto ls = cell->getLandScape();
        auto type = ls->getType();
        if (type == LandType::GRASS || type == LandType::EARTH)
            return cell;
    }
    return std::shared_ptr<MapCell>(nullptr);
}

void Attackable::perform(uint32_t y, uint32_t x, uint32_t damage) {
    auto gameController = GameSingleton::getGameController();
    auto map = gameController->getMap();
    auto width = map->getWidth();
    auto height = map->getHeight();
    if (y < height && x < width && x >= 0 && y >= 0 && map->getMapCell(y, x)->getObject() != nullptr) {
        auto object = map->getMapCell(y, x)->getObject();
        if (object && dynamic_cast<Unit*>(object)){
            Unit* unit = dynamic_cast<Unit*>(object);
            if (gameController->getCurrentBase() == gameController->getObjectStorage()->getBase(unit))
                return;
            std::string msg = unit->getName() + " has been attacked, now his hp is "; 
            unit->setHealth(unit->getHealth() - damage + unit->getArmor());
            msg += std::to_string(unit->getHealth()) + "\n";
            if (unit->getHealth() <= 0) {
                auto base = gameController->getObjectStorage()->getBase(unit);
                base->deleteObject(unit);
                msg += unit->getName() + " has died!\n";
            }
            gameController->getLogger()->appendBuffer(msg);
        }
        
    }
}

void MeleeAttack::attack(uint32_t y, uint32_t x, uint32_t damage){
    perform(y+1, x, damage);
    perform(y-1, x, damage);
    perform(y, x+1, damage);
    perform(y, x-1, damage);
}

void RangeAttack::attack(uint32_t y, uint32_t x, uint32_t damage){
    perform(y-2, x+1, damage);
    perform(y+2, x-1, damage);
    perform(y-1, x+2, damage);
    perform(y+1, x-2, damage);
}