#include "World.h"

using std::endl;
using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::rand;

World::World(int h, int w, int maxObj, int maxUnit) : height{h}, width{w} {
    if (height < 10 || width < 10)
        height = width = 10;
    std::srand(std::time(0));
    cells = new Cell *[height];
    for (int i = 0; i < height; ++i)
        cells[i] = new Cell[width];
    // frame
    for (int i = 0; i < height; ++i) {
        cells[i][0].setWall<Wall>();
        cells[i][width - 1].setWall<Wall>();
    }
    for (int i = 0; i < width; ++i) {
        cells[0][i].setWall<Wall>();
        cells[height - 1][i].setWall<Wall>();
    }
    // create landscape
    for (int i = 0; i < maxObj; ++i) {
        int randi = rand() % height;
        int randj = rand() % width;
        //если нет стены, ставим стену
        if (cells[randi][randj].isEmpty()) {
            if (rand() % 2)
                cells[randi][randj].setWall<Tree>();
            else
                cells[randi][randj].setWall<Rock>();
        } else { --i; }
    }

    // create units
    for (int i = 0; i < maxUnit; ++i) {
        int randi = rand() % height;
        int randj = rand() % width;
        if (cells[randi][randj].isEmpty()) {
            switchUnit(randj, randi, []() { return rand() % 6; });
        } else { --i; }
    }
}

void World::switchUnit(int x, int y, int choose()) {
    switch (choose()) {
        case 0:
            cells[y][x].setUnit<Cavalry>();
            break;
        case 1:
            cells[y][x].setUnit<Infantry>();
            break;
        case 2:
            cells[y][x].setUnit<Sniper>();
            break;
        case 3:
            cells[y][x].setUnit<Rifleman>();
            break;
        case 4:
            cells[y][x].setUnit<YellowWizard>();
            break;
        case 5:
            cells[y][x].setUnit<GreenWizard>();
            break;
        default:
            break;
    }
}

World::~World() {
    for (int i = 0; i < height; ++i) {
        delete cells[i];
    }
    delete cells;
}

World::World(std::ifstream &file, int h, int w) : height(h), width(w) {
    cout << height << " " << width << endl;
    std::vector<Unit *> units;
    cells = new Cell *[height];
    for (int i = 0; i < height; ++i)
        cells[i] = new Cell[width];
    char c = 0;
    int r_id, r_hp, r_dam, r_arm;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> c;
            switch (c) {
                case '#':
                    cells[i][j].setWall<Wall>();
                    break;
                case '*':
                    cells[i][j].setWall<Rock>();
                    break;
                case '^':
                    cells[i][j].setWall<Tree>();
                    break;
                case 'C':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<Cavalry>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                    break;
                case 'I':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<Infantry>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                        break;
                case 'S':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<Sniper>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                    break;
                case 'R':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<Rifleman>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                    break;
                case 'Y':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<YellowWizard>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                    break;
                case 'G':
                    if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                        cells[i][j].setUnit<GreenWizard>(r_id, r_hp, r_dam, r_arm);
                        units.push_back(cells[i][j].getUnit());
                    }
                    break;
                case '$':
                    file >> r_hp;
                    if (r_hp < 1 || r_hp > 555)
                        r_hp = 555;
                    setBase(units, h * w / 20, r_hp);
                    break;
                default:
                    if (c > '0' && c < '9') {
                        if (readUnitParam(file, r_id, r_hp, r_dam, r_arm)) {
                            cells[i][j].setPlayer(c, r_id, r_hp, r_dam, r_arm);
                        }
                    }
                    break;
            }
        }
    }
}

bool World::readUnitParam(std::ifstream &file, int &id, int &hp, int &dam, int &arm) {
    file >> id >> hp >> dam >> arm;
    if (id < 0)
        return false;
    if (hp < 1 || hp > 200)
        return false;
    if (dam < 0 || dam > 11)
        return false;
    if (arm < 0 || arm > 11)
        return false;
    return true;
}

Cell &World::getCell(pair<int, int> coord) {
    return getCell(coord.first, coord.second);
}

Cell &World::getCell(int x, int y) {
    if (y >= 0 && y < height && x >= 0 && x < width)
        return cells[y][x];
    else
        return cells[0][0];
}

int World::getHeight() const {
    return height;
}

int World::getWidth() const {
    return width;
}

World::World(const World &w) : height{w.height}, width{w.width} {
    cells = new Cell *[height];
    for (int i = 0; i < height; ++i)
        cells[i] = new Cell[width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i][j] = w.cells[i][j];
        }
    }
}

World &World::operator=(const World &w) {
    if (this == &w) {
        return *this;
    }
    height = w.height;
    width = w.width;
    cells = new Cell *[height];
    for (int i = 0; i < height; ++i)
        cells[i] = new Cell[width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i][j] = w.cells[i][j];
        }
    }
    return *this;
}

void World::setBase(vector<Unit *> units, int maxUnit, int hp) {
    cells[height - 2][width - 2].delUnit().delWall().setBase(std::move(units), maxUnit, hp);
    cells[height - 3][width - 2].delUnit().delWall();
    cells[height - 2][width - 3].delUnit().delWall();
    cells[height - 3][width - 3].delUnit().delWall();
}

void World::dropLoot() {
    while (true) {
        int x = rand() % width;
        int y = rand() % height;
        if (cells[y][x].isEmpty()) {
            if (rand() % 50 == 0) {
                cells[y][x].setNeutral<RareBox>();
                return;
            }
            switch (rand() % 3) {
                case 0:
                    cells[y][x].setNeutral<HealthBox>();
                    break;
                case 1:
                    cells[y][x].setNeutral<ArmorBox>();
                    break;
                case 2:
                    cells[y][x].setNeutral<RandomBox>();
                    break;
            }
            break;
        }
    }
}

void World::assistBase(Base &b) {
    cells[height - 3][width - 2].setUnit<Cavalry>();
    if (cells[height - 3][width - 2].getUnit()->getID() != 0)
        b.addEnemy(cells[height - 3][width - 2].getUnit());
    cells[height - 2][width - 3].setUnit<Cavalry>();
    if (cells[height - 2][width - 3].getUnit()->getID() != 0)
        b.addEnemy(cells[height - 2][width - 3].getUnit());
    cells[height - 3][width - 3].setUnit<Cavalry>();
    if (cells[height - 3][width - 3].getUnit()->getID() != 0)
        b.addEnemy(cells[height - 3][width - 3].getUnit());
}


Cell::Cell(bool isUnit, bool isWall) : isUnit(isUnit), isWall(isWall), object(new Road) {}

template<class ClosedCellsClass>
Cell &Cell::setWall() {
    if (isEmpty()) {
        delete object;
        isWall = true;
        object = new ClosedCellsClass;
    }
    return *this;
}

bool Cell::getIsWall() const {
    return isWall;
}

Cell &Cell::setPlayer(char playerName, int t_id, int t_health, int t_damage, int t_armor) {
    if (isEmpty()) {
        isUnit = true;
        if (t_id != -1)
            object = new Player(playerName, t_id, t_health, t_damage, t_armor);
        else
            object = new Player(playerName);
    }
    return *this;
}

template<class UnitClass>
Cell &Cell::setUnit(int id, int health, int damage, int armor) {
    if (isEmpty()) {
        delete object;
        isWall = isLoot = false;
        isUnit = true;
        if (id != -1)
            object = new UnitClass(id, health, damage, armor);
        else
            object = new UnitClass;
    }
    return *this;
}

bool Cell::getIsUnit() const {
    return isUnit;
}

Unit *Cell::getUnit() const {
    return getIsUnit() ? static_cast<Unit *>(object) : nullptr;
}

Tree::Tree() : ClosedCells('^') {}

Rock::Rock() : ClosedCells('*') {}

Wall::Wall() : ClosedCells('#') {}

std::ostream &operator<<(std::ostream &out, const Cell &cc) {
    out << cc.object->getPict();
    return out;
}

Cell &Cell::delWall() {
    if (isWall && !isUnit) {

        delete object;
        isWall = isUnit = false;
        object = new Road;
    }
    return *this;
}

Cell &Cell::delUnit() {
    if (isUnit && !isWall) {
        delete object;
        isUnit = isWall = isLoot = false;
        object = new Road;
    }
    return *this;
}

bool Cell::isEmpty() const {
    return !(isWall || isUnit || isLoot);
}

Cell &Cell::operator=(Cell &from) {
    isUnit = true;
    object = from.object;
    from.isUnit = false;
    from.object = new Road();
    return *this;
}

Cell &Cell::setBase(vector<Unit *> units, int maxUnit, int hp) {
    isUnit = isWall = true;
    object = new Base(units, maxUnit, hp);
    return *this;
}


ClosedCells::ClosedCells(char pict) : AbstractObject(pict) {}

Road::Road(char pict) : AbstractObject(pict) {}

Base *Cell::getBase() {
    if (isUnit && isWall)
        return static_cast<Base *>(object);
    return NULL;
}

template<class NeutralClass>
Cell &Cell::setNeutral() {
    if (isEmpty()) {
        isUnit = isWall = false;
        isLoot = true;
        object = new NeutralClass;
    }
    return *this;;
}

bool Cell::getIsLoot() const {
    return isLoot;
}

char Cell::getLoot() {
    char pic = object->getPict();
    if (isLoot) {
        delete object;
        isLoot = false;
        object = new Road;
    }
    return pic;
}

Cell &Cell::operator<<(Cell &dest) {
    this->isLoot = dest.isLoot;
    this->isUnit = dest.isUnit;
    this->isWall = dest.isWall;
    this->object = dest.object;
    return *this;
}
