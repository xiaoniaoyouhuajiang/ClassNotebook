#include "game.h"



Game::Game(unsigned x, unsigned y, unsigned limit)
{
    field = new PlayingField(x, y, limit);
    units = new AttackMediator(field);
}

void Game::createBase(int maxUnitsCount, int health, int xx, int yy, int baseNumb)
{
    Base* base =  new Base(maxUnitsCount, health, xx, yy, baseNumb);
    gameMediator = new GameMediator(this, base);
    base->setGameMediator(gameMediator);
    bases.push_back(base);
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
    throw std::invalid_argument("Error! No such base in the game!!!");
}

void Game::deleteUnit(Unit *unit, Base *base)
{
    for(Base* b : bases){
        if(b == base){
            units->deleteUnit(unit);
            return;
        }
    }
    throw std::invalid_argument("Error! No such base in the game!!!");
}

Base *Game::getBaseByNum(int num)
{
    for(Base* b : bases){
        if(b->getBaseNumb() == num){
            return b;
        }
    }
    throw invalid_argument("there is not such base number");
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
