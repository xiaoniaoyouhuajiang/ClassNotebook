#include "game.h"

#include <exception.h>



Game::Game(unsigned x, unsigned y, unsigned limit)
{
    field = new PlayingField(x, y, limit);
    units = new AttackMediator(field);
}

void Game::createBase(int maxUnitsCount, int health, int xx, int yy, int baseNumb)
{
    Base* base =  new Base(maxUnitsCount, health, xx, yy, baseNumb);
    try {

        field->addBase(base);
        gameMediator = new GameMediator(this, base);
        base->setGameMediator(gameMediator);
        bases.push_back(base);
    }catch (CoordsException& e) {
        throw e;
    }catch (CellBusyExpeption& e) {
        throw e;
    }catch (SimpleFieldException& e) {
        throw e;
    }catch (LandExeption& e) {
        throw e;
    }
}

void Game::createNeutral(NeutralType net, unsigned x, unsigned y)
{
    NeutralObj* obj=nullptr;
    switch(net){
    case  HELMET:
        obj = new GetArmor(new Helmet());
        break;
    case MITTENS:
        obj = new GetArmor(new Mittens());
        break;
    case SABATON:
        obj = new GetArmor(new Sabaton());
        break;
    case   BANDAGE:
        obj = new GetMedicine(new Bandage());
        break;
    case   POWERPOTION:
        obj = new GetMedicine(new PowerPotion());
        break;
    case   COVID19:
        obj = new DrinkPoison(new Covid19());
        break;
    case CODID37:
        obj = new DrinkPoison(new Covid37());
        break;
    case SWORD:
        obj = new GetWeapon(new Sword());
        break;
    case HATCHET:
        obj = new GetWeapon(new Hatchet());
        break;

    }
    field->addNeutral(obj, x, y);
}

void Game::addUnit(Unit *unit, Base *base)
{
    for(Base* b : bases){
        if(b == base){
            units->addUnit(unit);
            return;
        }
    }
    throw SimpleFieldException("Error! No such base in the game!!!");
}

void Game::deleteUnit(Unit *unit, Base *base)
{
    for(Base* b : bases){
        if(b == base){
            units->deleteUnit(unit);
            return;
        }
    }
    throw SimpleFieldException("Error! No such base in the game!!!");
}

Base *Game::getBaseByNum(int num)
{
    for(Base* b : bases){
        if(b->getBaseNumb() == num){
            return b;
        }
    }
    throw SimpleFieldException("there is not such base number");
}

std::vector<Base *> Game::getBases() const
{
    return bases;
}

std::vector<Unit *> Game::getUnits() const
{
    return units->getUnits();
}

PlayingField *Game::getField() const
{
    return field;
}

void Game::restoreMemento(Memento *memento)
{
    GameParam* params = memento->loadFromFile();
    delete field;
    for(Base* base : bases){
        delete base;
    }
    bases.clear();
    delete units;
    field = new PlayingField(params->getWidth(), params->getHeight(),params->getLimit());
    units = new AttackMediator(field);
    unsigned land=0;
    for(unsigned i=0; i<field->getWidth(); i++){
        for(unsigned j=0; j<field->getHeight(); j++){
            field->addLandscape(new Proxy(params->getLandscape()[land++]), i, j);
        }
    }
    for(NeutralParam* obj : params->getNeutrals()){
        field->createNeutral(obj->getType(), obj->getX(), obj->getY());
    }
    for(BaseParam* b: params->getBases()){
        createBase(b->getMaxCount(), b->getHealth(), b->getX(), b->getY(), b->getBaseNumb());
        Base* base = nullptr;
        try{
            base = getBaseByNum(b->getBaseNumb());
        }catch (CoordsException& e) {
            throw e;
        }catch (CellBusyExpeption& e) {
            throw e;
        }catch (SimpleFieldException& e) {
            throw e;
        }catch (LandExeption& e) {
            throw e;
        }
        for(UnitParam* u : b->getUnits()){
            try{
                CreateMediator* createMed = new CreateMediator(field, base);
                base->setCreateMediator(createMed);
                field->setCreateMediator(createMed);
                Attributes* attributes = u->getAttributes();
                Unit* unit = base->createUnit(u->getName(), u->getX(), u->getY());
                unit->setAttributesArmor(attributes->getArmor());
                unit->setAttributesAttack(attributes->getAttack());
                unit->setAttributesHealth(attributes->getHealth());
                unit->setX(u->getX());
                unit->setY(u->getY());
            }catch (CoordsException& e) {
                throw e;
            }catch (CellBusyExpeption& e) {
                throw e;
            }catch (SimpleFieldException& e) {
                throw e;
            }catch (LandExeption& e) {
                throw e;
            }

        }
    }
}

GameMemento *Game::readMemento(string name)
{
    vector<LandscapeType> land;
    for(unsigned i=0; i<field->getWidth(); i++){
        for(unsigned j=0; j<field->getHeight();j++){
            land.push_back(field->getCell(i,j)->getLandscape()->getLandscapeTypeEnum());
        }
    }
    vector<NeutralParam*> neutrals;
    for(unsigned i=0; i<field->getWidth(); i++){
        for(unsigned j=0; j<field->getHeight();j++){
            if(field->getCell(i,j)->getNeutral()){
                NeutralParam* net =  new NeutralParam(field->getCell(i,j)->getNeutral()->getTypeEnum(),i,j);
                neutrals.push_back(net);
            }
        }
    }
    vector<BaseParam*> paramBases;
    for(Base* base : bases){
        int baseNumb = base->getBaseNumb();
        int unitCount = base->getUnitCount();
        const int maxCount = base->getMaxCount();
        int health = base->getHealth();
        int x = base->getX();
        int y = base->getY();
        int unitCurr = base->getUnitCurr();
        CompositeUnit* units = base->getUnits();
        vector<UnitParam*> paramUnits;
        for(Unit* u : units->getUnits()){
            string name = u->getName();
            int num = baseNumb;
            Attributes* attributes = u->getAttributes();
            UnitParam* paramUnit = new UnitParam(name, num, attributes, u->getX(), u->getY());
            paramUnits.push_back(paramUnit);
        }
        BaseParam* paramBase = new BaseParam(baseNumb, unitCount, maxCount, health, x, y, unitCurr, paramUnits);
        paramBases.push_back(paramBase);
    }
    GameParam* gameParam = new GameParam(field->getWidth(), field->getHeight(), field->getMaxItems(), paramBases, neutrals, land);
    return new GameMemento(name, gameParam);
}
