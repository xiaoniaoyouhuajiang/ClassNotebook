#include "Game.h"

#define WINNER 1
using std::cout;
using std::endl;
using std::cin;
using std::pair;
using std::vector;
using std::rand;


Game::Game() {

    vector<Unit *> units;
    answer = '\0';
    world = nullptr;
    int h = 0;
    int w = 0;
    while (h < 10 || w < 10) {
        cout << "Write height and width: ";
        cin >> h >> w;
    }
    int maxUnitCount = h * w / 20;
    maxObjCount = h * w / 7;
    world = new World(h, w, maxObjCount, maxUnitCount);
    objectCount = maxObjCount;
    int unitCount = maxUnitCount;
    for (int i = 0; i < world->getHeight(); ++i) {
        for (int j = 0; j < world->getWidth(); ++j) {
            if (world->getCell(j, i).getIsUnit()) {
                units.push_back(world->getCell(j, i).getUnit());
            }
        }
    }
    world->setBase(units, unitCount, maxUnitCount);
    facade.setBase(world->getCell(world->getWidth() - 2, world->getHeight() - 2).getBase());
//    baseCoord.first = world->getWidth() - 2;
//    baseCoord.second = world->getHeight() - 2;
    printWorld();
    while (answer != 'n') {
        cout << "Do you want to do something else with (w)alls or (u)nits? (n) to start game." << endl;
        cin >> answer;
        if (answer == 'w') {
            cout << "(a)dd or (d)elete?" << endl;
            cin >> answer;
            if (answer == 'a') {
                addWalls();
            } else if (answer == 'd') {
                delWall();
            }
        } else if (answer == 'u') {
            cout << "(a)dd or (d)elete?" << endl;
            cin >> answer;
            if (answer == 'a') {
                facade.addUnit(*this);
            } else if (answer == 'd') {
                facade.delUnit(*this);
            }
        }
    }
}

Game::~Game() {
    delete world;
}

void Game::createPlayerSession() {
    while (playerName > '9' || playerName < '0') {
        cout << "Select the number you want to play for: ";
        cin >> playerName;
    }
    coordPlayer = {0, 0};
    while (world->getCell(coordPlayer).getIsUnit() ||
           world->getCell(coordPlayer).getIsWall()) {
        cout << "Where? ";
        cin >> coordPlayer.first >> coordPlayer.second;
    }
    world->getCell(coordPlayer).setPlayer(playerName);
    printWorld();
    mainPlay();
}


void Game::mainPlay() {
    while (answer != 'q') {
        if (!(rand() % 10)) {
            world->dropLoot();
            cout << "LOOT!" << endl;
        }
        if (world->getCell(coordPlayer).getUnit()->getHealth() <= 0) {
            cout << "Game over!" << endl;
            return;
        }
        if (playerName == WINNER) {
            cout << "You win!!!" << endl;
            return;
        }
        if (answer == 'm')
            menu();
        pair p = coordPlayer;
        goFor(coordPlayer);
        unitRandomWalk();
    }
}

void Game::goFor(pair<int, int> &coordUnit) {
    printWorld();
    answer = getchar();
    switch (answer) {
        case 'a':
            goTo(coordUnit, pair{coordUnit.first - 1, coordUnit.second});
            break;
        case 'd':
            goTo(coordUnit, pair{coordUnit.first + 1, coordUnit.second});
            break;
        case 'w':
            goTo(coordUnit, pair{coordUnit.first, coordUnit.second - 1});
            break;
        case 's':
            goTo(coordUnit, pair{coordUnit.first, coordUnit.second + 1});
            break;
        default:
            break;
    }
}

void Game::menu() {
    while (answer != 'b' && answer != 'u' && answer != 'n') {
        cout << "Do you want doing something with (b)ase or (u)nits or (n)ot?" << endl;
        cin >> answer;
    }
    if (answer == 'n') {
        return;
    }
    if (answer == 'b') {
        cout << "1. Add Unit" << endl;
        cout << "2. Delete Unit" << endl;
        cout << "3. Get information about units" << endl;
        cout << "4. Get information about base" << endl;
        do {
            cin >> answer;
        } while (answer < '1' || answer > '4');
        switch (answer) {
            case '1':
                facade.addUnit(*this);
                break;
            case '2':
                facade.delUnit(*this);
                break;
            case '3':
                facade.printInfo();
                break;
            case '4':
                facade.printBase();
            default:
                break;
        }
    } else if (answer == 'u') {
        pair<int, int> coord = getUnitCoord();
        cout << "1. Show information about this Unit." << endl;
        cout << "2. Take a step for him." << endl;
        do {
            cin >> answer;
        } while (answer < '1' || answer > '2');
        switch (answer) {
            case '1':
                facade.printInfo(world->getCell(coord).getUnit());
                break;
            case '2':
                goFor(coord);
                break;
            default:
                break;
        }
    }
}

void Game::goTo(pair<int, int> &from, pair<int, int> to) {
    if (world->getCell(to).getIsLoot())
        *(world->getCell(from).getUnit()) += world->getCell(to).getLoot();
    if (world->getCell(to).isEmpty()) {
        world->getCell(to) = world->getCell(from);
        from = to;
    } else if (world->getCell(to).getIsUnit())
        attack(world->getCell(from), world->getCell(to));
}

pair<int, int> Game::getUnitCoord() {
    pair<int, int> coord = {0, 0};
    while (!world->getCell(coord).getIsUnit() || world->getCell(coord).getIsWall()) {
        cout << "Where?" << endl;
        cin >> coord.first >> coord.second;
    }
    return coord;
}

void Game::addWalls() {
    if (objectCount >= maxObjCount) {
        cout << "So many walls." << endl;
        return;
    }
    int x, y;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
    } while (!world->getCell(x, y).isEmpty());
    world->getCell(x, y).setWall<Rock>();
    objectCount++;
    printWorld();
}

void Game::addUnits() {
    if (facade.isUnitLimit()) {
        cout << "So many units." << endl;
        return;
    }
    int x, y;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
    } while (!world->getCell(x, y).isEmpty());
    while (true) {
        cout << "What unit do you want to create?" << endl;
        cin >> answer;
        if (answer == 'C') {
            world->getCell(x, y).setUnit<Cavalry>();
            break;
        }
        if (answer == 'I') {
            world->getCell(x, y).setUnit<Infantry>();
            break;
        }
        if (answer == 'S') {
            world->getCell(x, y).setUnit<Sniper>();
            break;
        }
        if (answer == 'R') {
            world->getCell(x, y).setUnit<Rifleman>();
            break;
        }
        if (answer == 'Y') {
            world->getCell(x, y).setUnit<YellowWizard>();
            break;
        }
        if (answer == 'G') {
            world->getCell(x, y).setUnit<GreenWizard>();
            break;
        }
    }
    facade.getBase().addEnemy(world->getCell(x, y).getUnit());
    printWorld();
}

void Game::delUnit(int x, int y) {
    while (!world->getCell(x, y).getIsUnit() || world->getCell(x, y).getIsWall()) {
        cout << "Where? (x y): ";
        cin >> x >> y;
    }
    cout << "Unit " << world->getCell(x, y).getUnit()->getPict() << " with ID: "
         << world->getCell(x, y).getUnit()->getID() << " is deleted." << endl;
    facade.getBase().killEnemy(world->getCell(x, y).getUnit());
    world->getCell(x, y).delUnit();
    printWorld();
}

void Game::delWall() {
    if (objectCount <= 0)
        return;
    int x = 0;
    int y = 0;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
    } while (!world->getCell(x, y).getIsWall() || world->getCell(x, y).getIsUnit());
    world->getCell(x, y).delWall();
    objectCount--;
    printWorld();
}

void Game::printWorld() {
    for (int i = 0; i < world->getHeight(); ++i) {
        for (int j = 0; j < world->getWidth(); ++j)
            cout << world->getCell(j, i);
        cout << endl;
    }
    if (playerName >= '0' && playerName <= '9')
        cout << *(world->getCell(findUnit(0)).getUnit()) << endl;
}

void Game::attack(Cell &attacker, Cell &defender) {
    if (attacker.getUnit()->getIsEnemy() && defender.getUnit()->getIsEnemy()) {
        return;
    }
    if (attacker.getUnit()->getIsEnemy() && defender.getIsWall())
        return;
    int dam = attacker.getUnit()->giveDamage();
    int takedDam = 0;
    if (!attacker.getUnit()->getIsEnemy() && defender.getIsUnit() && defender.getIsWall()) {
        defender.getBase()->takeDamage(dam);
        if (defender.getBase()->getHealth() < 200 && defender.getBase()->getHealth() % 5 == 0) {
            world->assistBase(facade.getBase());
        }
        if (defender.getBase()->getHealth() < 0) {
            playerName = WINNER;
        }
    } else {
        takedDam = defender.getUnit()->takeDamage(dam);
        cout << "Attack from " << attacker.getUnit()->getPict() << " to " << defender.getUnit()->getPict()
             << " for "
             << takedDam << endl;
        if (defender.getUnit()->getHealth() < 0) {
            pair coord = findUnit(defender.getUnit()->getID());
            cout << defender.getUnit()->getPict() << " is dead." << endl;
            if (defender.getUnit()->getPict() == playerName) {
                playerName = 0;
                return;
            }
            delUnit(coord.first, coord.second);
            return;
        }
    }

}

void Game::unitRandomWalk() {
    for (auto u : facade.getBase().getUnits()) {
        pair<int, int> coord = findUnit(u);
        if (world->getCell(coord).getUnit()->getPict() != playerName) {
            pair<int, int> to = coord;
            if (rand() % 2)
                to.first = coord.first + rand() % 3 - 1;
            else
                to.second = coord.second + rand() % 3 - 1;
            goTo(coord, to);
        }
    }
}

pair<int, int> Game::findUnit(Unit *u) {
    for (int i = 0; i < world->getHeight(); ++i)
        for (int j = 0; j < world->getWidth(); ++j)
            if (u == world->getCell(j, i).getUnit())
                return pair(j, i);
    return pair(0, 0);
}

pair<int, int> Game::findUnit(int id) {
    for (int i = 0; i < world->getHeight(); ++i)
        for (int j = 0; j < world->getWidth(); ++j)
            if (world->getCell(j, i).getIsUnit() && id == world->getCell(j, i).getUnit()->getID())
                return pair(j, i);
    return pair(0, 0);
}

Base &MenuFacade::getBase() {
    return *(base);
}

MenuFacade &MenuFacade::addUnit(Game &g) {
    g.addUnits();
    return *this;
}

MenuFacade &MenuFacade::setBase(Base *b) {
    base = b;
    return *this;
}

bool MenuFacade::isUnitLimit() {
    return (base->isUnitLimit());
}

MenuFacade &MenuFacade::delUnit(Game &g) {
    g.delUnit();
    return *this;
}

MenuFacade &MenuFacade::printInfo(Unit *u) {
    if (u == NULL)
        base->printUnitsInfo();
    else
        base->printUnitsInfo(u);
    return *this;
}

MenuFacade &MenuFacade::printBase() {
    base->printBase();
    return *this;
}
