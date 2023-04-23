#include "Game.h"

#define WINNER 1
#define  DEAD 0
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
    while (answer != 'C' && answer != 'L') {
        cout << "(C)reate or (L)oad?" << endl;
        cin >> answer;
    }
    if (answer == 'C') {
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
        log.str("");
        log << "Main: World create with size " << h << " " << w << ".";
        logger << log.str();
        world->setBase(units, maxUnitCount);
        facade.setBase(world->getCell(world->getWidth() - 2, world->getHeight() - 2).getBase());
        logger << "Main: Base setted.";

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
        createPlayerSession();
    } else if (answer == 'L') {
        while (!facade.load(*this));
        facade.setBase(world->getCell(world->getWidth() - 2, world->getHeight() - 2).getBase());
        mainPlay();
    }
}

Game::~Game() {
    logger << "Main: Game ends.";
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
    log.str("");
    log << "Main: Player " << playerName << " created at " << coordPlayer.first << " " << coordPlayer.second;
    logger << log.str();
    log.str("");
    mainPlay();
}


void Game::mainPlay() {
    while (answer != 'q') {
        if (!(rand() % 10)) {
            world->dropLoot();
            logger << "Main: LOOT!";
        }
        if (world->getCell(findUnit(0)).getUnit()->getHealth() <= 0) {
            cout << "Game over!" << endl;
            logger << "Main: Player is dead";
            return;
        }
        if (playerName == WINNER) {
            cout << "You win!!!" << endl;
            logger << "Main: Base is dead";
            return;
        }
        if (answer == 'm') {
            menu();
        }
        goFor(coordPlayer);
        unitRandomWalk();
    }
}

void Game::goFor(pair<int, int> &coordUnit) {
    printWorld();
    cin >> answer;
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
    while (answer != 'b' && answer != 'u' && answer != 'n' && answer != 's' && answer != 'l') {
        cout << "Do you want doing something with (b)ase, (u)nits, (s)ave, (l)oad or (n)ot?" << endl;
        cin >> answer;
    }
    switch (answer) {
        case 'l': {
            facade.load(*this);
            facade.setBase(world->getCell(world->getWidth() - 2, world->getHeight() - 2).getBase());
            break;
        }
        case 's': {
            facade.save(*this);
            break;
        }
        case 'n':
            return;
        case 'b':
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
                    break;
                default:
                    break;
            }
            break;
        case 'u':
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
            break;
    }
}

void Game::goTo(pair<int, int> &from, pair<int, int> to) {
    Unit *u = world->getCell(from).getUnit();
    if (world->getCell(to).getIsLoot()) {
        log.str("");
        log << "Main: Unit " << u->getPict() << " with ID: " << u->getID() << " take loot at " << to.first << " "
            << to.second << ".";
        logger << log.str();
        log.str("");
        *u += world->getCell(to).getLoot();
        if (u->getHealth() < 0) {
            pair coord = findUnit(u->getID());
            log.str("");
            log << "Main: " << u->getPict() << " is dead.";
            logger << log.str();
            if (u->getPict() == playerName) {
                playerName = DEAD;
                return;
            }
            delUnit(coord.first, coord.second);
            return;
        }
    }
    if (world->getCell(to).isEmpty()) {
        log.str("");
        log << "Main: Unit " << u->getPict() << " with ID: " << u->getID() << " go to " << to.first << " " << to.second
            << ".";
        logger << log.str();
        log.str("");
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
        logger << "Main: Fail try add wall, limit.";
        cout << "So many walls." << endl;
        return;
    }
    int x, y;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
        log.str("");
        log << "Main: Fail try add wall, not empty cell. (" << x << " " << y << ")";
        logger << log.str();
    } while (!world->getCell(x, y).isEmpty());
    log.str("");
    log << "Main: Create wall in " << x << " " << y;
    logger << log.str();
    world->getCell(x, y).setWall<Rock>();
    objectCount++;
    printWorld();
}

void Game::addUnits() {
    if (facade.isUnitLimit()) {
        logger << "Main: Fail try add unit, limit.";
        cout << "So many units." << endl;
        return;
    }
    int x, y;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
        log.str("");
        log << "Main: Fail try add unit, not empty cell. (" << x << " " << y << ")";
        logger << log.str();
    } while (!world->getCell(x, y).isEmpty());
    while (true) {
        cout << "What unit do you want to create?" << endl;
        cin >> answer;
        log.str("");
        log << "Main: Add unit ";
        if (answer == 'C') {
            world->getCell(x, y).setUnit<Cavalry>();
            log << "Cavalry ";
            break;
        }
        if (answer == 'I') {
            world->getCell(x, y).setUnit<Infantry>();
            log << "Infantry ";
            break;
        }
        if (answer == 'S') {
            world->getCell(x, y).setUnit<Sniper>();
            log << "Sniper ";
            break;
        }
        if (answer == 'R') {
            world->getCell(x, y).setUnit<Rifleman>();
            log << "Rifleman ";
            break;
        }
        if (answer == 'Y') {
            world->getCell(x, y).setUnit<YellowWizard>();
            log << "YellowWizard ";
            break;
        }
        if (answer == 'G') {
            world->getCell(x, y).setUnit<GreenWizard>();
            log << "GreenWizard ";
            break;
        }
    }
    facade.getBase().addEnemy(world->getCell(x, y).getUnit());
    log << "on " << x << " " << y << ".";
    logger << log.str();
    printWorld();
}

void Game::delUnit(int x, int y) {
    if (facade.getBase().getUnits().empty()) {
        logger << "Main: Fail try delete unit, no units.";
        return;
    }
    while (!world->getCell(x, y).getIsUnit() || world->getCell(x, y).getIsWall()) {
        cout << "Where? (x y): ";
        cin >> x >> y;
        log.str("");
        log << "Main: " << "Fail try delete unit, cell without unit. (" << x << " " << y << ")";
        logger << log.str();
    }
    log.str("");
    log << "Main: " << "Delete unit " << world->getCell(x, y).getUnit()->getPict() << " with ID: "
        << world->getCell(x, y).getUnit()->getID() << " in " << x << " " << y << ".";
    logger << log.str();
    facade.getBase().killEnemy(world->getCell(x, y).getUnit());
    world->getCell(x, y).delUnit();
    printWorld();
}

void Game::delWall() {
    if (objectCount <= 0) {
        logger << "Main: Fail try delete wall, no walls.";
        return;
    }
    int x = 0;
    int y = 0;
    do {
        cout << "Where? (x y): ";
        cin >> x >> y;
        log.str("");
        log << "Main: Fail try delete wall, cell without wall. (" << x << " " << y << ")";
        logger << log.str();
    } while (!world->getCell(x, y).getIsWall() || world->getCell(x, y).getIsUnit());
    world->getCell(x, y).delWall();
    log.str("");
    log << "Main: Delete wall in " << x << " " << y << ".";
    logger << log.str();
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
    log << "Main: Attack from " << attacker.getUnit()->getIsEnemy() << " to " << defender.getUnit()->getIsEnemy();
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
            logger << "Main: Base take help.";
            world->assistBase(facade.getBase());
        }
        if (defender.getBase()->getHealth() < 0) {
            playerName = WINNER;
        }
    } else {
        takedDam = defender.getUnit()->takeDamage(dam);
        log.str("");
        log << "Main: Attack from " << attacker.getUnit()->getPict() << " to " << defender.getUnit()->getPict()
            << " for " << takedDam << ".";
        logger << log.str();
        log.str("");
        if (defender.getUnit()->getHealth() < 0) {
            pair coord = findUnit(defender.getUnit()->getID());
            log.str("");
            log << "Main: " << defender.getUnit()->getPict() << " is dead.";
            logger << log.str();
            if (defender.getUnit()->getPict() == playerName) {
                playerName = DEAD;
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

MenuFacade &MenuFacade::save(Game &g) {
    std::string fname;
    cout << "Enter save name: ";
    cin >> fname;
    std::string path = fname + ".save";
    std::ofstream file;
    file.open(path);
    if (!file.is_open()) {
        g.logger << "ERROR: Game not saved";
        return *this;
    }
    file << g.world->getHeight() << " " << g.world->getWidth() << " " << g.playerName << endl;
    for (int i = 0; i < g.world->getHeight(); ++i) {
        for (int j = 0; j < g.world->getWidth(); ++j) {
            file << g.world->getCell(j, i);
            if (g.world->getCell(j, i).getIsUnit()) {
                if (g.world->getCell(j, i).getIsWall())
                    file << " " << g.world->getCell(j, i).getBase()->getHealth();
                else
                    file << " " << g.world->getCell(j, i).getUnit()->getID() <<
                         " " << g.world->getCell(j, i).getUnit()->getHealth() <<
                         " " << g.world->getCell(j, i).getUnit()->getDamage() <<
                         " " << g.world->getCell(j, i).getUnit()->getArmor() << " ";
            }
        }
        file << endl;
    }
    file.close();
    return *this;
}

bool MenuFacade::load(Game &g) {
    std::string fname;
    std::ifstream file;
    cout << "Enter load name: ";
    cin >> fname;
    std::string path = fname + ".save";
    file.open(path);
    if (!file.is_open()) {
        g.logger << "ERROR: File is not exist!";
        return false;
    }
    delete g.world;
    int h, w;
    char r_char;
    file >> h;
    if (h < 10)
        return false;
    file >> w;
    if (w < 10)
        return false;
    file >> r_char;
    if (r_char > '9' || r_char < '0')
        return false;
    g.playerName = r_char;
    g.world = new World(file, h, w);
    g.coordPlayer = g.findUnit(0);
    file.close();
    return true;
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
