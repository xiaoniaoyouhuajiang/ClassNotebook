#include "snapshotbackup.h"
#include "../Field.h"

#include "../Field.h"
#include "RAII.h"
#include "../Base.h"

#include "../extra1/unitfactory.h"

#include "../Landscape/Landscape.h"
#include "../Landscape/Ground.h"
#include "../Landscape/Mountain.h"
#include "../Landscape/Water.h"

#include "../extra2/Neutral/neutralObject.h"
#include "../extra2/Neutral/damage.h"
#include "../extra2/Neutral/restoreArmour.h"
#include "../extra2/Neutral/restoreMana.h"
#include "../extra2/Neutral/restoreHealth.h"
#include "../extra2/Neutral/none.h"
#include "../Exceptions.h"

unsigned int CRC32_function(unsigned char *buf, unsigned long len)
{
    unsigned long crc_table[256];
    unsigned long crc;
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    };
    crc = 0xFFFFFFFFUL;
    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL;
}

SnapshotBackup::SnapshotBackup(Field *field, int x, int y, int maxUnit, int curUnit, std::vector<Base*> bases):
        field(field), x(x), y(y), maxUnit(maxUnit), curUnit(curUnit), bases(bases)
{
    std::cout << "SnapshotBackup::SnapshotBackup(save)" << std::endl;
    fileWrie = new RAII("saveField.txt", "save");
}

SnapshotBackup::SnapshotBackup(Field *field)
{
    fileRead = new FileRead("saveField.txt");
    this->field = field;
    this->adapter = new Adapter;
}

SnapshotBackup::~SnapshotBackup()
{
    delete fileWrie;
    delete fileRead;
}

void SnapshotBackup::saveGame()
{
    std::cout << "saveGame" << std::endl;
    std::ostringstream str;
    this->adapter = field->getAdapter();

    //field
    str << x << " " << y << " " << maxUnit << std::endl;

    //cells
    for(int i=0;i<field->y;i++)
    {
        for(int j=0;j<field->x;j++)
        {
            Cell* c = field->cell[i][j];
            char tn = c->object->typeNeutral();
            str << c->x << " " << c->y << " " << c->landscape->typeLandscape() << " " << ((tn==' ')? '-' : tn) << std::endl;
        }
    }

    int count_base = 0;
    for(const auto& base : bases) {
        if(base)
            count_base++;
    }
    str << count_base << std::endl; // кол-во баз

    for(const auto& base : bases) {
        if(base) // когда база есть!
        {
            //base
            str << base->id <<" "<< base->x <<" "<<base->y<<" " << base->health<<" " << base->maxCountUnit << " " << base->countUnit << std::endl;

            //units
            Unit *unit;
            str << base->units.size() << std::endl;
            for (size_t i = 0; i < base->units.size(); i++){
                unit = base->getUnitById(i);
                str << unit->base_id << " " << unit->x << " " << unit->y << " " << unit->type() << " "
                    << unit->param.mana << " " << unit->param.armor << " " << unit->param.damage
                    << " " << unit->param.health << std::endl;

            }
        }
    }

    std::string data = str.str();
    unsigned int crc32 = CRC32_function((unsigned char*)data.c_str(), data.size());
    std::cout << "DATA: " << data.size() << std::endl;
    std::cout << "crc32 = " << crc32 << std::endl;

    std::ostringstream str_with_crc;
    str_with_crc<<crc32<<" ";
    str_with_crc<<str.str();

//    std::cout << str_with_crc.str() << std::endl;

    fileWrie->write(str_with_crc.str());
    adapter->gameSaved();
}

void SnapshotBackup::loadGame()
{

    std::cout << "loadGame" << std::endl;

    std::stringstream stream = fileRead->read();
    if(stream.fail()) {
        throw InputException("loadGame(): no file!");
    }

    unsigned int crc32;
    stream>>crc32;
    std::cout << "readed crc32 = " <<  crc32 << std::endl;

    // Выделение чистых данных (без CRC32, который в начале файла)
    // для вычисления CRC32
    std::string data = stream.str();
    char* p = new char[data.size()+1];
    for(int i=0; i<data.size();i++)
        p[i] = data[i];
    p[data.size()] = '\0';

    char *p2 = p;
    while(*p2!=' ') ++p2;
    p2++;

    int len=0;
    while(p2[len]) ++len;

    std::cout << "DATA: " << p << std::endl;
    unsigned int check_crc32 = CRC32_function((unsigned char*)p2, len);

    std::cout << "counted crc32 = " << check_crc32 << std::endl;

    delete [] p;
    //----------------------------------------------------

    if(crc32!=check_crc32) {
        throw InputException("loadGame(): file corrupted (wrong CRC32).");
    }

    stream >> x >> y >> maxUnit;

    if(stream.fail())
        throw InputException("int");

    if(field->x != 11 && field->x != 8)
        throw LogicException("field coordinates", x);
    if(field->y != 11 && field->y != 8)
        throw LogicException("field coordinates", y);
    if(maxUnit <= 0)
        throw LogicException("max count of filed unit", maxUnit);

    Field* field = new Field(x,y,maxUnit, new Adapter);

    // cells
    for(int i=0;i<y;i++)
    {
        for(int j=0;j<x;j++)
        {
            int x, y;
            char lt, ot;

            stream >> x >> y;
            if(stream.fail())
                throw InputException("int");

            stream >> lt >> ot;
            if(stream.fail())
                throw InputException("char");


            Landscape* l = nullptr;
            std::cout << "read: "  << x << " "<< y << " " << lt <<" " << ot << std::endl;
            switch(lt)
            {
                case '.' : l = new Ground; break;
                case '^' : l = new Mountain; break;
                case '~' : l = new Water;
            }

            NeutralObject *obj = nullptr;
            switch(ot)
            {
                case '0': obj = new restoreManaAction(new restoreManaNight); break;
                case '1': obj = new RestoreArmourAction(new RestoreArmourNight); break;
                case '2': obj = new RestoreHealthAction(new RestoreHealthDay); break;
                case '4': obj = new incDamageAction(new incDamageDay); break;
                default: obj = new NoneObj;
            }
            field->cell[i][j] = new Cell(j,i,nullptr, l, obj);
        }
    }

    int count_base;
    stream >> count_base;
    if (stream.fail())
        throw InputException("int");
    if (count_base>2)
        throw LogicException("count of base", count_base);

    for(int i=0;i<count_base;i++)
    {
        int id, baseX, baseY, maxCountUnitBase, health, countUnitBase;
        stream >> id >> baseX >> baseY >> maxCountUnitBase >> health >> countUnitBase ;

        if(baseX<0)
            throw LogicException("base coordinate", baseX);
        if(baseY < 0)
            throw LogicException("base coordinate", baseY);
        if(maxCountUnitBase <= 0)
            throw LogicException("max count unit of base", maxUnit);
        if(health < 0)
            throw LogicException("health of base", health);

        field->createBase(id, baseX, baseY, maxCountUnitBase, health);

        int unitsSize;
        stream >> unitsSize;
        if(stream.fail())
            throw InputException("int");


        std::cout << "unitsSize: " << unitsSize << std::endl;

        for(int i=0;i<unitsSize;i++)
        {
            int base_id, x, y, f, a, d, h;
            char type;


            stream >> base_id >> x >> y;
            if(stream.fail())
                throw InputException("int");

            stream >> type;
            if(stream.fail())
                throw InputException("char");

            stream >> f >> a >> d >> h;
            if(stream.fail())
                throw InputException("int");

            std::cout << base_id << " " << x<<" " << y << " " << type << " " << f <<" " << a  << " " << d << " " << h << std::endl;

            Unit *u;
            Base *base = field->getBase(base_id);
            if(base->x == x && base->y == y)
            {
                u = base->createUnit(type);
            }
            else {
                u = base->unitFactory.createUnit(type, x, y);
                base->units.addUnit(u);
                field->cell[y][x]->unit = u;
            }
            u->param.mana = f;
            u->param.armor = a;
            u->param.damage = d;
            u->param.health = h;
        }
    }

    this->field->x = field->x;
    this->field->y = field->y;
    this->field->bases = field->bases;
    this->field->adapter = field->adapter;
    this->field->cell = field->cell;

    adapter->gameLoaded();
}