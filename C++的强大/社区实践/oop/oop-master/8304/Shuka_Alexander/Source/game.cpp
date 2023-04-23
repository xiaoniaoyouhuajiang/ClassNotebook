#include "game.h"

using namespace unit;


Game::Game()
{
    factory = std::make_shared<RandomObjectFactory>();
    playerUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    enemyUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    logger = std::make_shared<FileLogger>("log.txt");
}


void Game::run()
{
    init();

    isRun = true;
    while (isRun) {
        auto command = input();
        auto flag = logic(command);

        if (!flag) {
            break;
        }

        enemyLogic();

        if (playerBase->getHealthPoints() <= 0) {
            logger->writeToLog("GAME OVER. ENEMY WON!");
            std::cout << "ENEMY WON!\n";
            return;
        }
        else if (enemyBase->getHealthPoints() <= 0) {
            logger->writeToLog("GAME OVER. PLAYER WON!");
            std::cout << "YOU WON!\n";
            return;
        }

        std::set<std::shared_ptr<Unit>> tmp;
        for (auto i : *playerUnits) {
            if (i->getHealthPoints() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            logger->writeToLog(UnitLogMsg::dieMessage(i));

            playerUnits->erase(i);
            i->notify();
            field->deleteUnit(i);
        }

        tmp.clear();
        for (auto i : *enemyUnits) {
            if (i->getHealthPoints() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            logger->writeToLog(UnitLogMsg::dieMessage(i));

            enemyUnits->erase(i);
            i->notify();
            field->deleteUnit(i);
        }

        draw();
        Sleep(200);
    }
}


void Game::init()
{
    logger->writeToLog("START GAME");

    std::cout << "RULES:\na - armor\n. - road\n+ - heal\n* - fog\nx - spikes\n"
                 "- - bomb\n^ - tower\nB- base\n";
    Sleep(3000);

    playerUnits->clear();
    enemyUnits->clear();

    this->enemyGold = 0;
    this->playerGold = 0;
    isPlayerAttack = false;

    createField();
    mediator = std::make_shared<Mediator>(field, logger);

    playerBase = std::make_shared<Base>(Point2D(1, field->getHeight()/2),
                                        mediator, PLAYER::ONE);

    enemyBase = std::make_shared<Base>(Point2D(field->getWidth() - 2,
                                               field->getHeight()/2),
                                       mediator, PLAYER::TWO);

    field->addUnit(playerBase);
    field->addUnit(enemyBase);

    logger->writeToLog(UnitLogMsg::createMessage(playerBase));
    logger->writeToLog(UnitLogMsg::createMessage(enemyBase));
    logger->writeToLog(PlayerLogMsg::attack(PLAYER::TWO));
    logger->writeToLog(PlayerLogMsg::deffend(PLAYER::ONE));

    playerFacade = std::make_shared<Facade>(mediator, playerBase, playerUnits,
                                            enemyBase, field, logger);
    enemyFacade = std::make_shared<Facade>(mediator, enemyBase, enemyUnits,
                                           playerBase, field, logger);
}


void Game::createField()
{
    field = std::make_shared<GameField>(19, 31);

    auto spikes = std::make_shared<SpikesLandscape>();
    auto fog = std::make_shared<FogLandscape>();
    auto proxy = std::make_shared<ProxyLandscape>(spikes);

    field->getCell(Point2D(0, 0))->setLandscape(spikes);

    for (size_t i = 0; i < field->getHeight(); ++i) {
        field->getCell(Point2D(0, i))->setLandscape(proxy);
        field->getCell(Point2D(field->getWidth() - 1, i))->setLandscape(proxy);
    }

    for (size_t i = 0; i < field->getWidth(); ++i) {
        field->getCell(Point2D(i, 0))->setLandscape(proxy);
        field->getCell(Point2D(i, field->getHeight() - 1))->setLandscape(proxy);
    }

    proxy = std::make_shared<ProxyLandscape>(fog);

    for (size_t i = 0; i < field->getHeight(); ++i) {
        if (abs(static_cast<long long>(i) -
                static_cast<long long>(field->getHeight() / 4)) >= 2 &&
                abs(static_cast<long long>(i) -
                    static_cast<long long>(3 * field->getHeight() / 4)) >= 2) {
            field->getCell(Point2D(field->getWidth()/2, i))->setLandscape(proxy);
        }
    }
}


void Game::draw() const
{
    std::string res;
    for (size_t i = 0; i < field->getHeight(); ++i) {
        for (size_t  j = 0; j < field->getWidth(); ++j) {
            auto cell = field->getCell(Point2D(j, i));

            if (cell->isEmpty()) {
                auto& object = *cell->getNeutralObject();
                auto landscape = cell->getLandscape();
                if (typeid (object) != typeid(NoObject)) {
                    res += object.draw();
                }
                else {
                    res += landscape->draw();
                }
            }
            else {
                res += cell->getUnit()->draw();
            }
            res += ' ';
        }
        res += '\n';
    }

    res += "\nGold: " + std::to_string(playerGold) + "\n";
    res += "Base HP: " + std::to_string(playerBase->getHealthPoints()) + "\n";
    res += "enemy Base HP: " + std::to_string(enemyBase->getHealthPoints()) + "\n";

    res += "q - quit, 1 - standing, 2 - ground, 3 - flying\n"
           "a - attack, d - defense\n9 - save\n0 - load\n";
    system("cls");
    std::cout << res;
}


void Game::farmEnemy()
{
    enemyGold += enemyBase->farm();
    for (auto i : *enemyUnits) {
        enemyGold += i->farm();
    }
}


void Game::farmPlayer()
{
    playerGold += playerBase->farm();
    for (auto i : *playerUnits) {
        playerGold += i->farm();
    }
}


bool Game::logic(COMMAND command)
{
    farmPlayer();

    switch (command) {
    case COMMAND::SAVE:
        Snapshot::save(*this);
        break;
    case COMMAND::LOAD:
        std::cout << "LOADED!\n";
        Sleep(1000);
        Snapshot::load(*this);
        break;
    case COMMAND::ATTACK:
        logger->writeToLog(PlayerLogMsg::attack(PLAYER::ONE));
        isPlayerAttack = true;
        break;
    case COMMAND::DEFFEND:
        logger->writeToLog(PlayerLogMsg::deffend(PLAYER::ONE));
        isPlayerAttack = false;
        break;
    case COMMAND::CRT_FLYING:
        if (playerGold > 220) {
            auto isCreate = playerFacade->createFlyingUnit();
            if (isCreate) {
                playerGold -= 220;
                logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::ONE));
                break;
            }
        }
        logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::ONE), LVL::WARNING);
        break;
    case COMMAND::CRT_GROUND:
        if (playerGold > 150) {
            auto isCreate = playerFacade->createGroundUnit();
            if (isCreate) {
                playerGold -= 150;
                logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::ONE));
                break;
            }
        }
        logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::ONE), LVL::WARNING);
        break;
    case COMMAND::CRT_STANDING:
        if (playerGold > 200) {
            auto isCreate = playerFacade->createStandingUnit();
            if (isCreate) {
                playerGold -= 200;
                logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::ONE));
                break;
            }
        }
        logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::ONE), LVL::WARNING);
        break;
    case COMMAND::EXIT:
        logger->writeToLog("GAME OVER");
        isRun = false;
        return false;
    default:
        break;
    }

    if (isPlayerAttack) {
        playerFacade->charge();
    }
    else {
        playerFacade->deffend();
    }

    return true;
}


void Game::enemyLogic()
{
    farmEnemy();
    enemyFacade->charge();

    srand(time(0));
    auto choose = rand() % 2;

    if (choose == 1 && enemyGold > 150) {
        choose = rand() % 3;
        switch (choose) {
        case 0:
            if (enemyGold > 200) {
                auto isCreate = enemyFacade->createStandingUnit();
                if (isCreate) {
                    enemyGold -= 200;
                    logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::TWO));
                    break;
                }
            }
            logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::TWO), LVL::WARNING);
            break;
        case 1:
            if (enemyGold > 150) {
                auto isCreate = enemyFacade->createGroundUnit();
                if (isCreate) {
                    enemyGold -= 150;
                    logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::TWO));
                    break;
                }
            }
            logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::TWO), LVL::WARNING);
            break;
        case 2:
            if (enemyGold > 220) {
                auto isCreate = enemyFacade->createFlyingUnit();
                if (isCreate) {
                    enemyGold -= 220;
                    logger->writeToLog(PlayerLogMsg::createUnit(true, PLAYER::TWO));
                    break;
                }
            }
            logger->writeToLog(PlayerLogMsg::createUnit(false, PLAYER::TWO), LVL::WARNING);
            break;
        }
    }
}


COMMAND Game::input()
{
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            return COMMAND::ATTACK;
        case 'd':
            return COMMAND::DEFFEND;
        case '1':
            return COMMAND::CRT_STANDING;
        case '2':
            return COMMAND::CRT_GROUND;
        case '3':
            return COMMAND::CRT_FLYING;
        case 'q':
            return COMMAND::EXIT;
        case '9':
            return COMMAND::SAVE;
        case '0':
            return  COMMAND::LOAD;
        }
    }
    return COMMAND::NO_COMMAND;
}
