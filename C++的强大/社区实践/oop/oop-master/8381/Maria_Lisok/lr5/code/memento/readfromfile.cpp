#include "readfromfile.h"

ReadFromFile::ReadFromFile(string name): nameFile(name)
{
    file.open(name);
    if(!file.is_open())
        throw std::runtime_error("File doesn't open for read");
}

ReadFromFile::~ReadFromFile()
{
    if(file.is_open())
        file.close();
}

GameParam* ReadFromFile::read()
{
    string buf;
    int temp, tempUnitSize;
    unsigned width = 0;
    unsigned height = 0;
    unsigned limit = 0;
    vector<BaseParam*> bases;
    vector<NeutralParam*> neutrals;
    vector<LandscapeType> landscape;
    file >> buf;
    if(buf != "Field:"){
        throw invalid_argument("Field header wrong");
    }
    file >> width >> height >> limit;

    file >> buf;
    if (buf != "Land:")
        throw invalid_argument("Landscape header wrong");
    for(unsigned i=0; i< width*height; i++){
        if (!(file >> temp))
            throw invalid_argument("Landscape parameters wrong");
        landscape.push_back(static_cast<LandscapeType>(temp));
    }

    file >> buf;
    if (buf != "Neutrals:")
        throw invalid_argument("Neutral header wrong");
    file >> temp;
    for(unsigned i=0; i< static_cast<unsigned>(temp); i++){
        unsigned x;
        unsigned y;
        unsigned type;
        if (!(file >> x)|| !(file >> y) || !(file >> type))
            throw invalid_argument("Neutrals parameters wrong");
        neutrals.push_back(new NeutralParam(static_cast<NeutralType>(type), x, y));
    }

    file >> buf;
    if (buf != "Bases:")
        throw invalid_argument("Base header wrong");
    file >> temp;
    for(unsigned i=0; i < static_cast<unsigned>(temp); i++){
        int baseNumb;
        int unitCount;
        int maxCount;
        int health;
        int x, y;
        int unitCurr;
        vector<UnitParam*> units;
        if (!(file >> baseNumb)|| !(file >> unitCount) || !(file >> maxCount) || !(file >> health) ||
               !(file >> x)|| !(file >> y) || !(file >> unitCurr))
            throw invalid_argument("Base parameters wrong");
        file >> tempUnitSize;
        for(unsigned j=0; j < static_cast<unsigned>(tempUnitSize); j++){
            string name;
            int baseNumber;
            file >> name >> baseNumber;
            int armor;
            int attack;
            int healthUnit;
            unsigned posUnitX;
            unsigned posUnitY;
            file >> healthUnit;
            file >> armor;
            file >> attack;
            file >> posUnitX;
            file >> posUnitY;
            units.push_back(new UnitParam(name, baseNumber, new Attributes(healthUnit, armor, attack), posUnitX, posUnitY));
        }
        bases.push_back(new BaseParam(baseNumb, unitCount, maxCount, health,x, y, unitCurr, units));
    }
    return new GameParam(width, height, limit, bases, neutrals, landscape);
}
