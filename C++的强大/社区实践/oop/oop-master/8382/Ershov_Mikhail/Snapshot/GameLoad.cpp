#include "GameLoad.h"

GameLoad::GameLoad(string name) : fileName(name) {
    file.open(name);
    if (!file.is_open())
        throw std::runtime_error("Файл для загрузки не открывается");
}

GameLoad::~GameLoad() {
    if (file.is_open())
        file.close();
}

SnapshotGame* GameLoad::load() {
    string buf;
    unsigned sizeOfField = 0;
    unsigned whoseTurn = 0;
    vector<SnapshotBase*> bases;

    file >> buf;
    if (buf != "Field:") {
        throw invalid_argument("Field header wrong");
    }
    file >> sizeOfField >> whoseTurn;

    Cell** c;
    c = new Cell * [sizeOfField];
    for (unsigned i = 0; i < sizeOfField; i++) {
        c[i] = new Cell[sizeOfField];
    }

    file >> buf;
    if (buf != "Units:")
        throw invalid_argument("Units header wrong");
    for (unsigned i = 0; i < sizeOfField; i++) {
        string name;
        int health;
        int armor;
        int damage;
        for (unsigned j = 0; j < sizeOfField; j++) {
            Warrior w;
            if (!(file >> name))
                throw invalid_argument("Unit parameters wrong");
            else w.SetValue(name);
            if (!(file >> health))
                throw invalid_argument("Unit parameters wrong");
            else w.SetHealth(health);
            if (!(file >> armor))
                throw invalid_argument("Unit parameters wrong");
            else w.SetArmor(armor);
            if (!(file >> damage))
                throw invalid_argument("Unit parameters wrong");
            else w.SetDamage(damage);
            w.SetPlaceX(i);
            w.SetPlaceY(j);
            c[i][j].setUnit(w);
        } 
    }

    file >> buf;
    if (buf != "Landscape:")
        throw invalid_argument("Landscape header wrong");
    for (unsigned i = 0; i < sizeOfField; i++) {
        string landType;
        for (unsigned j = 0; j < sizeOfField; j++) {
            Landscape* l = nullptr;
            if (!(file >> landType))
                throw invalid_argument("Landscape parameters wrong");
            else {
                if (landType == "forest")
                    c[i][j].setLandscape(l->create(Forest_ID));
                else if (landType == "burningE")
                    c[i][j].setLandscape(l->create(BurningEarth_ID));
                else if (landType == "UnknownL")
                    c[i][j].setLandscape(l->create(UnknownLand_ID));
                else 
                    throw invalid_argument("Landscape parameters wrong");
            }
        }
    }

    file >> buf;
    if (buf != "NeutObjects:")
        throw invalid_argument("Neutral Object header wrong");
    for (unsigned i = 0; i < sizeOfField; i++) {
        string NOType;
        for (unsigned j = 0; j < sizeOfField; j++) {
            NeutralObject* NO = nullptr;
            if (!(file >> NOType))
                throw invalid_argument("NeutObject parameters wrong");
            else {
                if (NOType == "Killer")
                    c[i][j].setNeutral(NO->create(Killer_ID));
                else if (NOType == "ArmorR")
                    c[i][j].setNeutral(NO->create(Armor_ID));
                else if (NOType == "HealthR")
                    c[i][j].setNeutral(NO->create(Health_ID));
                else if (NOType == "Freezer")
                    c[i][j].setNeutral(NO->create(Freezer_ID));
                else if (NOType == "0") 
                    c[i][j].setNeutral(NO->create(NO_ID));
                else 
                    throw invalid_argument("NeutObject parameters wrong");
            }
        }
    }

    int numOfBases = -1;
    file >> buf;
    if (buf != "Bases:")
        throw invalid_argument("Base header wrong");
    if (!(file >> numOfBases))
        throw invalid_argument("Base parameters wrong");
    for (unsigned i = 0; i < static_cast<unsigned>(numOfBases); i++) {
        char typeOfB;
        int currentOrcsNum;
        int currentMEnum;
        int health;
        vector <Warrior> orcsUnits;
        vector <Warrior> MEUnits;
        int numOfUnitsInBase = 0;
        vector<SnapshotUnit*> unitsSnap;
        if (!(file >> typeOfB) || !(file >> health) || !(file >> currentOrcsNum) || !(file >> currentMEnum))
            throw invalid_argument("Base parameters wrong");
        file >> numOfUnitsInBase;
        for (unsigned j = 0; j < static_cast<unsigned>(numOfUnitsInBase); j++) {
            string name;
            int unitHealth;
            int armor;
            int damage;
            int posUnitX;
            int posUnitY;
            if (!(file >> name) || !(file >> unitHealth) || !(file >> armor) || !(file >> damage) || !(file >> posUnitX) || !(file >> posUnitY))
                throw invalid_argument("Units in base parameters wrong");

            unitsSnap.push_back(new SnapshotUnit(name, damage, unitHealth, armor, posUnitX, posUnitY));
        }
        bases.push_back(new SnapshotBase(typeOfB, health, currentOrcsNum, currentMEnum, unitsSnap));
    }

    SnapshotField* fieldSnap = new SnapshotField(sizeOfField, c, whoseTurn);
    return new SnapshotGame(sizeOfField, bases, fieldSnap);
}
