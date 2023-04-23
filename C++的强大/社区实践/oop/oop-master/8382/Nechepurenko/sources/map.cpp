#include "../headers/map.hpp"
#include "../headers/game.hpp"
#include "../headers/exceptions.hpp"


Map::Map(uint16_t c_width, uint16_t c_height) noexcept {
    this->width = c_width;
    this->height = c_height;
    this->matrix = new std::shared_ptr<MapCell>*[height];
    for (size_t i = 0; i < height; i++){
        this->matrix[i] = new std::shared_ptr<MapCell>[width];
        for (size_t j = 0; j < width; j++){
            this->matrix[i][j] = std::shared_ptr<MapCell>(new MapCell(i,j));
        }
    }
}

void Map::draw() {
    Unit* currentHero = nullptr;
    std::pair<uint32_t, uint32_t> position = std::make_pair(-1, -1);
    try {
        currentHero = GameSingleton::getGameController()->getCurrentHero();
        position = GameSingleton::getGameController()->getObjectStorage()->getCoords(currentHero);
    } catch (NoCurrentPlayerException& e) {
        currentHero = nullptr;
    }
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            if (matrix[i][j]->getObject()){
                if (i == position.first && j == position.second)
                    std::cout << "\033[1;31m" << matrix[i][j]->getObject()->repr() << "\033[0m" << " ";
                else
                    std::cout << matrix[i][j]->getObject()->repr() << " ";
            } else {
                if (matrix[i][j]->getLandScape())
                    std::cout << matrix[i][j]->getLandScape()->repr() << " ";
                else
                    std::cout << "0" << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}

Map::~Map() {
    delete this->matrix;
}


MapCell::MapCell(MapCell const & mc){
    auto object_storage = GameSingleton::getGameController()->getObjectStorage();
    auto map = GameSingleton::getGameController()->getMap();
    if (this->objectAtPosition != nullptr) {
        object_storage->deleteObject(this->objectAtPosition);
        this->objectAtPosition = nullptr;
    }
    if (mc.objectAtPosition != nullptr) {
        //auto new_object = new Object(*mc.objectAtPosition);
        //object_storage->setObject(new_object, map->getMapCell(this->y, this->x));
    }

}
MapCell& MapCell::operator=(MapCell const & mc){
    if (this == &mc)
        return *this;
        
    auto object_storage = GameSingleton::getGameController()->getObjectStorage();
    auto map = GameSingleton::getGameController()->getMap();
    if (this->objectAtPosition != nullptr) {
        object_storage->deleteObject(this->objectAtPosition);
        this->objectAtPosition = nullptr;
    }
    if (mc.objectAtPosition != nullptr) {
        //auto new_object = new Object(*mc.objectAtPosition);
        
        //object_storage->setObject(new_object, map->getMapCell(this->y, this->x));
    }

    return *this;
}

std::shared_ptr<MapCell> Map::getMapCell(size_t y, size_t x){
    if (y < height && y >= 0 && x < width && x >= 0)
        return this->matrix[y][x];
    else
        return std::shared_ptr<MapCell>(nullptr);
}

void MapCell::setObject(Object* ao){
    this->objectAtPosition = ao;
}

std::shared_ptr<MapCell>** Map::getMatrix(){
    return this->matrix;
}

Object* MapCell::getObject(){
    return this->objectAtPosition;
}

std::pair<uint32_t, uint32_t> MapCell::getCoords(){
    return std::make_pair(this->y, this->x);
}

uint16_t Map::getWidth(){
    return this->width;
}

uint16_t Map::getHeight(){
    return this->height;
}

void MapCell::deleteObject(){
    if (this->objectAtPosition)
        delete this->objectAtPosition;
    this->objectAtPosition = nullptr;
}

void MapCell::setLandScape(LandScape* ls) {
    delete this->ls;
    this->ls = ls;
}

LandScape* MapCell::getLandScape() {
    return this->ls;
}

void Rock::draw(){
    std::cout << "now I'm looking like a rock!" << std::endl;
}

void Tree::draw(){
    std::cout << "now I'm looking like a tree!" << std::endl;
}

void Earth::draw(){
    std::cout << "now I'm looking like a earth!" << std::endl;
}

void Grass::draw(){
    std::cout << "now I'm looking like a grass!" << std::endl;
}