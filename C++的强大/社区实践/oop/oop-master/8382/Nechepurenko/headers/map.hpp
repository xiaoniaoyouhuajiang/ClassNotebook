#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "object.hpp"
#include <memory>

enum Move {UP, DOWN, LEFT, RIGHT};
enum LandType {ROCK, TREE, EARTH, GRASS};

class DrawLandScape {
    public:
        virtual void draw() = 0;
};

class LandScape : public Object{
    public:
        LandType getType() {
            return type;
        }
    protected:
        LandScape(LandType type) : type(type) {}
        LandType type;
};

class Rock : public LandScape, public DrawLandScape {
    public:
        Rock() : LandScape(LandType::ROCK) {}
        void draw();
};

class Tree : public LandScape, public DrawLandScape {
    public:
        Tree() : LandScape(LandType::TREE) {}
        void draw();
        std::string repr(){
            return std::string("T");
        }
};

class Grass : public LandScape, public DrawLandScape {
    public:
        Grass() : LandScape(LandType::GRASS) {}
        void draw();
        std::string repr(){
            return std::string("G");
        }
};

class Earth : public LandScape, public DrawLandScape {
    public:
        Earth() : LandScape(LandType::EARTH) {}
        void draw();
        std::string repr(){
            return std::string("E");
        }
};

class MapSample {
    public:
        MapSample(std::string path = "map_samples/default.s");
        std::vector<std::vector<uint8_t> > ms;
        uint16_t width = 0;
        uint16_t height = 0;
};

class MapCell {
    public:
        MapCell(uint32_t y, uint32_t x, LandScape* ls = nullptr) : y(y), x(x), ls(ls) {
            if (!ls)
                this->ls = new Earth();
        };
        MapCell(MapCell const & mc);
        MapCell& operator=(MapCell const & mc);
        void setObject(Object* ao);
        void deleteObject();
        Object* getObject();
        void setLandScape(LandScape* ls);
        LandScape* getLandScape();
        std::pair<uint32_t, uint32_t> getCoords();
    private:
        Object* objectAtPosition = nullptr;
        uint32_t y;
        uint32_t x;
        LandScape* ls = new Earth();
};

class Map {
    public:
        Map(uint16_t c_width = 20, uint16_t c_height = 20) noexcept;
        Map(MapSample const & ms);
        std::shared_ptr<MapCell> getMapCell(size_t y, size_t x);
        std::shared_ptr<MapCell>** getMatrix();
        uint16_t getWidth();
        uint16_t getHeight();
        void draw();
        ~Map();
    private:
        std::shared_ptr<MapCell>** matrix;
        uint16_t width;
        uint16_t height;
};