#include "fieldsnapshot.h"
#include "gamefield.h"

FieldSnapshot::FieldSnapshot(GameField* field, bool isCorrectCreated, const int x, const int y, int unitCount, const int maxCount, Point*** pointsMap,
                             Base* base1, Base* base2) : field(field), isCorrectCreated(isCorrectCreated), x(x), y(y), unitCount(unitCount), maxCount(maxCount),
                             pointsMap(pointsMap), base1(base1), base2(base2)
{

}

bool isNumber(const std::string& s)
{
    return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}

void FieldSnapshot::save()
{
    //Field saving
    File* file = new File("Game field dump.txt");
    std::ostringstream str("");
    str << x << " " << y << " " << unitCount << " " << maxCount << std::endl;
    file->write(&str.str()[0]);


    //Base1 saving
    str.str("");
    str << base1->x << " " << base1->y << " " << base1->health << " " << base1->baseNumb << " " << base1->maxCount << " "
        << base1->unitCount << std::endl;
    file->write(&str.str()[0]);


    //Base1 units saving
    for (int i = 0; i < base1->unitCount; i++){
        Unit* unit = base1->getCurrUnit();
        Point* point = field->findUnit(unit);
        str.str("");
        str << point->x << " " << point->y << " " << unit->getName() << " " << unit->getArmor() << " " << unit->getAttack() << " "
            << unit->getHealth() << std::endl;
        file->write(&str.str()[0]);
    }


    //Base2 saving
    str.str("");
    str << base2->x << " " << base2->y << " " << base2->health << " " << base2->baseNumb << " " << base2->maxCount << " "
        << base2->unitCount << std::endl;
    file->write(&str.str()[0]);


    //Base2 units saving
    for (int i = 0; i < base2->unitCount; i++){
        Unit* unit = base2->getCurrUnit();
        Point* point = field->findUnit(unit);
        str.str("");
        str << point->x << " " << point->y << " " << unit->getName() << " " << unit->getArmor() << " " << unit->getAttack() << " "
            << unit->getHealth() << std::endl;
        file->write(&str.str()[0]);
    }
    file->~File();
}

bool FieldSnapshot::isFileCorrect()
{
    //Checking field info
    FileIn* file = new FileIn("Game field dump.txt");
    std::stringstream str("");
    str << file->read();

    std::string xx, yy, uunitCount, mmaxCount;
    str >> xx >> yy >> uunitCount >> mmaxCount;

    if(xx == "" || yy == "" || uunitCount == "" || mmaxCount == "")
        return false;

    try
    {
        stoi(xx); stoi(yy); stoi(uunitCount); stoi(mmaxCount);
    }
    catch(std::out_of_range)
    {
        return false;
    }

    if(isNumber(xx) && isNumber(yy) && isNumber(uunitCount) && isNumber(mmaxCount)){
        if (stoi(xx) <= 1 || stoi(yy) <= 1 || stoi(mmaxCount) <= 1 || stoi(uunitCount) < 0 || stoi(uunitCount) > stoi(mmaxCount))
            return false;
    }
    else{
        return false;
    }

    GameField possibleField(stoi(xx), stoi(yy), stoi(mmaxCount), true);


    //Checking base1 info
    str.str("");
    str << file->read();

    std::string baseNumb, unitCountB, maxCountB, health, xb, yb;
    str >> xb >> yb >> health >> baseNumb >> maxCountB >> unitCountB;

    if(xb == "" || yb == "" || health == "" || baseNumb == "" || maxCountB == "" || unitCountB == "")
        return false;

    try
    {
        stoi(xb); stoi(yb); stoi(baseNumb); stoi(health); stoi(maxCountB); stoi(unitCountB);
    }
    catch(std::out_of_range)
    {
        return false;
    }

    if(isNumber(xb) && isNumber(yb) && isNumber(health) && isNumber(baseNumb) && isNumber(maxCountB) && isNumber(unitCountB)){
        if (stoi(xb) < 0 || stoi(xb) >= stoi(xx) || stoi(yb) < 0 || stoi(yb) >= stoi(xx) || stoi(health) <= 0 || stoi(baseNumb) != 1 ||
                stoi(maxCountB) <= 0 || stoi(unitCountB) < 0 || stoi(unitCountB) > stoi(uunitCount) || stoi(unitCountB) > stoi(maxCountB))
            return false;
    }
    else{
        return false;
    }
    possibleField.setBase(stoi(maxCountB), stoi(health), stoi(xb), stoi(yb));


    //Checking base1 units info
    std::string xu, yu, armor, attack, healthu, name;
    std::vector<std::vector<bool>> map;
    map.resize(stoi(yy));
    for(int i = 0; i < stoi(yy); i++){
        map[i].resize(stoi(xx));
        for(int j = 0; j < stoi(xx); j++)
            map[i][j] = false;
    }
    map[stoi(yb)][stoi(xb)] = true;

    for (int i = 0; i < stoi(unitCountB); i++){
        str.str("");
        str << file->read();
        str >> xu >> yu >> name >> armor >> attack >> healthu;
        if(xu == "" || yu == "" || name == "" || armor == "" || attack == "" || healthu == "")
            return false;

        try
        {
            stoi(xu); stoi(yu); stoi(armor); stoi(healthu); stoi(attack);
        }
        catch(std::out_of_range)
        {
            return false;
        }

        const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};

        if(isNumber(xu) && isNumber(yu) && isNumber(armor) && isNumber(attack) && isNumber(healthu) && (name == unitsNames[0] ||
                 name == unitsNames[1] || name == unitsNames[2] || name == unitsNames[3] || name == unitsNames[4] || name == unitsNames[5])){
            if (stoi(xu) < 0 || stoi(xu) >= stoi(xx) || stoi(yu) < 0 || stoi(yu) >= stoi(yy) || stoi(healthu) <= 0 || stoi(armor) <= 0 ||
                    stoi(attack) < 0)
                return false;
            else{
                if (!possibleField.canStand(name, stoi(xu), stoi(yu)) || (map[stoi(yu)][stoi(xu)])) //if unit can't stand cause of landscape or unit or base
                    return false;
                else
                    map[stoi(yu)][stoi(xu)] = true;
            }
        }
        else{
            return false;
        }
    }


    //Base2 checking info
    str.str("");
    str << file->read();

    std::string unitCountB2;
    str >> xb >> yb >> health >> baseNumb >> maxCountB >> unitCountB2;

    if(xb == "" || yb == "" || health == "" || baseNumb == "" || maxCountB == "" || unitCountB2 == "")
        return false;

    try
    {
        stoi(xb); stoi(yb); stoi(baseNumb); stoi(health); stoi(maxCountB); stoi(unitCountB2);
    }
    catch(std::out_of_range)
    {
        return false;
    }

    if(isNumber(xb) && isNumber(yb) && isNumber(health) && isNumber(baseNumb) && isNumber(maxCountB) && isNumber(unitCountB2)){
        if (stoi(xb) < 0 || stoi(xb) >= stoi(xx) || stoi(yb) < 0 || stoi(yb) >= stoi(yy) || stoi(health) <= 0 || stoi(baseNumb) != 2 ||
                stoi(maxCountB) <= 0 || stoi(unitCountB2) < 0 || stoi(unitCountB2) > stoi(uunitCount) || stoi(unitCountB2) > stoi(maxCountB) ||
                map[stoi(yb)][stoi(xb)] || (stoi(unitCountB) + stoi(unitCountB2) != stoi(uunitCount)))
            return false;
    }
    else{
        return false;
    }
    possibleField.setBase(stoi(maxCountB), stoi(health), stoi(xb), stoi(yb));
    map[stoi(yb)][stoi(xb)] = true;

    //Checking base2 units info
    for (int i = 0; i < stoi(unitCountB2); i++){
        str.str("");
        str << file->read();
        str >> xu >> yu >> name >> armor >> attack >> healthu;
        if(xu == "" || yu == "" || name == "" || armor == "" || attack == "" || healthu == "")
            return false;

        try
        {
            stoi(xu); stoi(yu); stoi(armor); stoi(healthu); stoi(attack);
        }
        catch(std::out_of_range)
        {
            return false;
        }

        const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};

        if(isNumber(xu) && isNumber(yu) && isNumber(armor) && isNumber(attack) && isNumber(healthu) && (name == unitsNames[0] ||
                 name == unitsNames[1] || name == unitsNames[2] || name == unitsNames[3] || name == unitsNames[4] || name == unitsNames[5])){
            if (stoi(xu) < 0 || stoi(xu) >= stoi(xx) || stoi(yu) < 0 || stoi(yu) >= stoi(xx) || stoi(healthu) <= 0 || stoi(armor) <= 0 ||
                    stoi(attack) < 0)
                return false;
            else{
                if (!possibleField.canStand(name, stoi(xu), stoi(yu)) || (map[stoi(yu)][stoi(xu)])) //if unit can't stand cause of landscape or unit or base
                    return false;
                else
                    map[stoi(yu)][stoi(xu)] = true;
            }
        }
        else{
            return false;
        }
    }
    possibleField.~GameField();

    file->~FileIn();
    return true;
}

void FieldSnapshot::load(Mediator* mediator)
{
    if (isFileCorrect()){
        //Field loading
        FileIn* file = new FileIn("Game field dump.txt");
        std::stringstream str;
        str << file->read();
        str >> x >> y >> unitCount >> maxCount;

        GameField loadField(x, y, maxCount, true);
        *(this->field) = loadField;


        //Base1 loading
        str.str("");
        str << file->read();

        int baseNumb;
        int unitCountB;
        int maxCountB;
        int health;
        int xx, yy;

        str >> xx >> yy >> health >> baseNumb >> maxCountB >> unitCountB;
        field->setBase(maxCountB, health, xx, yy);


        //Base1 units loading
        int xu, yu, armor, attack, healthu;
        std::string name;

        for (int i = 0; i < unitCountB; i++){
            str.str("");
            str << file->read();
            str >> xu >> yu >> name >> armor >> attack >> healthu;
            Unit* unit = field->createUnit(xu, yu, name, 1, mediator);
            unit->setAttributes(armor, healthu, attack);
        }


        //Base2 loading
        str.str("");
        str << file->read();

        str >> xx >> yy >> health >> baseNumb >> maxCountB >> unitCountB;
        field->setBase(maxCountB, health, xx, yy);


        //Base2 units loading
        for (int i = 0; i < unitCountB; i++){
            str.str("");
            str << file->read();
            str >> xu >> yu >> name >> armor >> attack >> healthu;
            Unit* unit = field->createUnit(xu, yu, name, 2, mediator);
            unit->setAttributes(armor, healthu, attack);
        }
        file->~FileIn();
    }
    else{
        std::cout << "Load file is critically damaged\n";
        field->isCorrectCreated = false;
    }
}
