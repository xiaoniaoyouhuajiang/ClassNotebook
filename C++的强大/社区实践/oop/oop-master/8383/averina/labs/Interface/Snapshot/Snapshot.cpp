
#include <sstream>
#include "Snapshot.h"


Snapshot::Snapshot(Field* field)
{
    this->field = field;
}

Snapshot::Snapshot(Field* field, int height, int width, int objectLimit, int objectCounter, int unitLimit,
                   int unitCounter)
{
    this->field = field;
    this->height = height;
    this->width = width;
    this->objectLimit = objectLimit;
    this->objectCounter = objectCounter;
    this->unitLimit = unitLimit;
    this->unitCounter = unitCounter;
}

void Snapshot::saveGame()
{
    file = new File("game_save.txt", "save");

    std::stringstream string;
    std::string str;

    /* FIELD MAIN */
    string << field->height << " " << field->width << " " << field->objLimit << std::endl;

    /* TALES */
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            auto tale = field->field[i][j];
            char landscape = '.';
            char neutral = '.';
            if (tale.landscape != nullptr) landscape = tale.landscape->getID();
            if (tale.neutral != nullptr) neutral = tale.neutral->id;
            string << tale.x << " " << tale.y << " " << landscape << " " << neutral << std::endl;
        }
    }

    /* BASE */
    if (field->base != nullptr)
    {
        string << 1 << std::endl;

        string << field->base->x << " " << field->base->y << " " << field->base->unitLimit << " " << field->base->unitCount << " " << field->base->health.get() << " " << field->base->unitDead << std::endl;
        /* UNITS ON BASE */
        string << field->base->unitsOnBase['M'] << std::endl;
        string << field->base->unitsOnBase['W'] << std::endl;
        string << field->base->unitsOnBase['A'] << std::endl;
        string << field->base->unitsOnBase['C'] << std::endl;
        string << field->base->unitsOnBase['K'] << std::endl;
        string << field->base->unitsOnBase['S'] << std::endl;
        /* UNITS ON FIELD */
        if (!field->base->unitsOnField.composite.empty())
        {
            std::cout << "DONT EMPTY" << std::endl;
            string << 1 << std::endl;
            string << field->base->unitsOnField.composite.size() << std::endl;
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                {
                    if (field->field[i][j].object != nullptr && field->field[i][j].object->id != 'B')
                    {
                        auto unit = field->field[i][j].object;
                        string << i << " " << j << " " << unit->id << " " << unit->health.get() << " " << unit->mana.get() << " " << unit->range.get()
                               << " " << unit->damage.getDamage() << " " << unit->damage.getCost() << " " << unit->damage.getRange() << std::endl;
                    }
                }

        }
        else string << 0 << std::endl;
    }
    else string << 0 << std::endl;

    str = string.str();
    file->writeString(str);
    file->~File();
}

Field* Snapshot::loadGame()
{
    file = new File("game_save.txt", "load");
    std::stringstream stream = file->readString();
    int flag;
    stream >> flag;
    if (flag == 0)
    {
        std::cout << "ERROR: file is empty or don't exist" << std::endl;
        return nullptr;
    }
    int x, y;

    /* FIELD */
    stream >> height >> width >> objectLimit;
    Field newField(height, width, 2);

    *(this->field) = newField;

    /* TALES */
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            char landscape;
            char neutral;

            stream >> x >> y >> landscape >> neutral;

            switch(neutral)
            {
                case '+':
                    field->field[i][j].neutral = field->neutralFactory.createAidKit();
                    break;
                case '*':
                    field->field[i][j].neutral = field->neutralFactory.createTrap();
                    break;
                case '$':
                    field->field[i][j].neutral = field->neutralFactory.createCurse();
                    break;
                case '&':
                    field->field[i][j].neutral = field->neutralFactory.createPotion();
                    break;
                default:
                    field->field[i][j].neutral = nullptr;
                    break;
            }

            switch(landscape)
            {
                case '$':
                    field->field[i][j].landscape = field->landscapeFactory.getForest();
                    break;
                case '~':
                    field->field[i][j].landscape = field->landscapeFactory.getWater();
                    break;
                case '^':
                    field->field[i][j].landscape = field->landscapeFactory.getMountain();
                    break;
                default:
                    field->field[i][j].landscape = nullptr;
                    break;
            }
        }
    }

    /* BASE */
    stream >> flag;
    if (flag)
    {
        int unitLim, unitCount, baseHealth, deadCount, number, id;
        stream >> x >> y >> unitLim >> unitCount >> baseHealth >> deadCount;
        field->createBase(x, y, unitLim, id, number);
        field->base->unitDead = deadCount;

        char unit;
        int count;

        stream >> count;
//        std::cout << count << std::endl;
        field->base->unitsOnBase['M'] = count;
        stream >> count;
//        std::cout << "Mage number: "  << count << std::endl;
        field->base->unitsOnBase['W'] = count;
        stream >> count;
//        std::cout << "Wizard number: "  << count << std::endl;
        field->base->unitsOnBase['A'] = count;
        stream >> count;
//        std::cout << "Archer number: "<< count << std::endl;
        field->base->unitsOnBase['C'] = count;
        stream >> count;
//        std::cout << "Crossbowman number: "<< count  << std::endl;
        field->base->unitsOnBase['K'] = count;
        stream >> count;
//        std::cout << "Knight number: " << count << std::endl;
        field->base->unitsOnBase['S'] = count;
        stream >> count;
//        std::cout << "Spearman number: " << count << std::endl;

        field->base->getInformation();
        stream >> flag;
        if (flag)
        {
            int size;
            stream >> size;

            int health, mana, range, damage, cost, drange;
            field->base->unitLimit++;
            int i, j;
            while(size != 0)
            {
                stream >> i >> j >> unit >> health >> mana >> range >> damage >> cost >> drange;
                std::cout << i << " " << j << std::endl;
                std::cout << unit << std::endl;
                field->base->createUnit(unit);
                field->addObject(field->base->getUnit(unit), i, j);
                field->field[i][j].object->damage.set(damage, drange, cost);
                field->field[i][j].object->health.set(health);
                field->field[i][j].object->range.set(range);
                field->field[i][j].object->mana.set(mana);
                --size;
            }
            field->base->unitLimit--;
        }
    }

    file->~File();
    return field;
}
