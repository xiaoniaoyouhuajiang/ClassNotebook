#include <iostream>
#include "GameField.h"
#include "Base.h"
#include "Armor/IronArmor.h"
#include "Armor/BaseArmor.h"
#include "Texture/SwampTexture.h"
#include "Texture/RockTexture.h"
#include "Texture/GrassTexture.h"
#include "NeutralObject/WildAnimalsArea.h"
#include "NeutralObject/House.h"
#include "NeutralObject/HolyGrail.h"
#include "Unit/Archer/Sniper.h"
#include "Unit/Archer/CrossBowMan.h"
#include "Unit/Wizard/FireMage.h"
#include "Unit/Viking/SwordMan.h"
#include "GameUI/GameAPI.h"
#include "Logging/Formats/TimeFormat.h"
#include "Logging/Formats/TagFormat.h"
#include "Logging/Formats/NoFormat.h"
#include "Logging/Loggers/TerminalLogger.h"
#include "Logging/Loggers/FileLogger.h"
#include "Logging/Loggers/NoLogger.h"
#include "GameUI/Rules/TinyGame.h"
#include "GameUI/Rules/HugeGame.h"

void example1() {
  GameField gameField(3, 3);

  Base *base = new Base(100, *ArmorFlyWeight::getFlyWeight<IronArmor>());
  gameField.addBase(base, 0, 0);
  FireMage *fireMage1 = base->createUnit<FireMage>(Point(0, 1));
  FireMage *fireMage2 = base->createUnit<FireMage>(Point(0, 2));
  Sniper *sniper1 = base->createUnit<Sniper>(Point(2, 0));

  std::cout << "FireMage1 Health: " << fireMage1->getUnitHealth() << std::endl;
  std::cout << "FireMage2 Health: " << fireMage2->getUnitHealth() << std::endl;

  fireMage1->attack(*fireMage2);

  std::cout << "FireMage1 Health: " << fireMage1->getUnitHealth() << std::endl;
  std::cout << "FireMage2 Health: " << fireMage2->getUnitHealth() << std::endl;

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  gameField.getCell(Point(1, 0))->canSetTexture(new GrassTexture());
  fireMage1->move(Point(1, 0));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "FireMage1 Health: " << fireMage1->getUnitHealth() << std::endl;
  std::cout << "FireMage2 Health: " << fireMage2->getUnitHealth() << std::endl;

  fireMage1->attack(*fireMage2);

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "FireMage1 Health: " << fireMage1->getUnitHealth() << std::endl;
}

void example2() {
  GameField gameField(3, 3);

  Base *base = new Base(100, *ArmorFlyWeight::getFlyWeight<IronArmor>());
  gameField.addBase(base, 0, 0);

  House *house = new House();
  gameField.addObject(house, 1, 0);

  Sniper *archer = base->createUnit<Sniper>(Point(0, 1));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "Sniper Health: " << archer->getUnitHealth() << std::endl;

  archer->move(Point(1, 0));
  std::cout << "Sniper Health: " << archer->getUnitHealth() << std::endl;

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
}

void example3() {
  GameField gameField(3, 3);

  Base *base = new Base(100, *ArmorFlyWeight::getFlyWeight<IronArmor>());
  gameField.addBase(base, 0, 0);

  auto *fireMage = base->createUnit<FireMage>(Point(1, 0));

  gameField.getCell(Point(0, 1))->canSetTexture(new SwampTexture());
  fireMage->move(Point(0, 1));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  auto *house = new House();
  gameField.getCell(Point(1, 1))->canSetObject(house);

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  fireMage->move(Point(1, 1));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
}

void example4() {
  GameField gameField(5, 5);

  Base *base = new Base(100, *ArmorFlyWeight::getFlyWeight<BaseArmor>());
  gameField.addBase(base, 2, 1);

  auto grail = new HolyGrail();
  gameField.getCell(Point(3, 3))->canSetObject(grail);

  auto *fireMage = base->createUnit<FireMage>(Point(0, 0));
  auto *swordMan = base->createUnit<SwordMan>(Point(1, 0));
  auto *sniper = base->createUnit<Sniper>(Point(2, 2));

  auto animals = new WildAnimalsArea();
  gameField.getCell(Point(0, 2))->canSetObject(animals);
  gameField.getCell(Point(1, 1))->canSetTexture(new SwampTexture());
  gameField.getCell(Point(1, 2))->canSetTexture(new GrassTexture());

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "Sniper Health: " << sniper->getUnitHealth() << std::endl;
  sniper->move(Point(0, 2));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "Sniper Health: " << sniper->getUnitHealth() << std::endl;
  std::cout << "Firemage Health: " << fireMage->getUnitHealth() << std::endl;

  swordMan->attack(*fireMage);

  std::cout << "Firemage Health: " << fireMage->getUnitHealth() << std::endl;

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  fireMage->move(Point(1, 1));
  std::cout << "Firemage Health: " << fireMage->getUnitHealth() << std::endl;

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  swordMan->attack(*fireMage);

  std::cout << "Firemage Health: " << fireMage->getUnitHealth() << std::endl;

  fireMage->attack(*swordMan);

  std::cout << "swordman Health: " << swordMan->getUnitHealth() << std::endl;

  fireMage->attack(*swordMan);

  std::cout << "swordman Health: " << swordMan->getUnitHealth() << std::endl;

  fireMage->attack(*swordMan);

  std::cout << "swordman Health: " << swordMan->getUnitHealth() << std::endl;

  swordMan->attack(*fireMage);

  std::cout << "Firemage Health: " << fireMage->getUnitHealth() << std::endl;

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  swordMan->move(Point(3, 3));

  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;

  std::cout << "Swordman Health: " << swordMan->getUnitHealth() << std::endl;
}

void example5() {
  GameField gameField(5, 5);

  Base *base = new Base(100, *ArmorFlyWeight::getFlyWeight<BaseArmor>());
  gameField.addBase(base, 0, 0);

  auto *u1 = base->createUnit<FireMage>(Point(0, 1));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u2 = base->createUnit<FireMage>(Point(0, 2));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u3 = base->createUnit<FireMage>(Point(0, 3));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u4 = base->createUnit<FireMage>(Point(1, 1));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u5 = base->createUnit<FireMage>(Point(1, 2));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u6 = base->createUnit<FireMage>(Point(1, 3));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
  auto *u7 = base->createUnit<FireMage>(Point(2, 1));
  std::cout << std::endl;
  std::cout << gameField;
  std::cout << std::endl;
}

void example_lab3() {
//  auto unit = new FireMage;
//
//  GameAPI game(2, 6, 6);
//
//  while (!game.isGameOver()){
//    std::cout << game;
//    game.nextTurn();
//  }
}

void example_lab4() {
//  game::log.setLogger(new FileLogger("log.txt"));
//  game::log.setLogFormat(new TimeFormat());
//
//  GameAPI game(2, 3, 3);
//
//  while (!game.isGameOver()){
//    std::cout << game;
//    game.nextTurn();
//  }
}


int main() {
  game::log.setLogger(new TerminalLogger());
  game::log.setLogFormat(new TimeFormat());

  auto game = GameAPI<TinyGame, 3>::instance();

  while (!game.isGameOver()){
    std::cout << game;
    game.nextTurn();
  }
  return 0;
}