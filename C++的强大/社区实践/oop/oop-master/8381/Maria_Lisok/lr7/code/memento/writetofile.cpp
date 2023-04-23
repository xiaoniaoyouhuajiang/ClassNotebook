#include "writetofile.h"

#include <exception.h>


WriteToFile::WriteToFile(string name): nameFile(name)
{
    file.open(name);
    if(!file.is_open())
        throw SimpleFieldException("File doesn't open");
}


WriteToFile::~WriteToFile()
{
    if(file.is_open())
        file.close();
}
void WriteToFile::write(GameParam* params)
{
    file << "Field:\n";
    file << params->getWidth() << " " << params->getHeight() << " " << params->getLimit();
    file << "\nLand:\n";
    for(unsigned i=0; i < params->getHeight()*params->getWidth(); i++){
        file << params->getLandscape()[i] << " ";
    }
    file << "\nNeutrals:\n";
    file << params->getNeutrals().size() << "\n";
    for(NeutralParam* neutr : params->getNeutrals()){
        file << neutr->getX()<< " " << neutr->getY() <<" " << neutr->getType() << "\n";
    }
    file << "Bases:\n";
    file << params->getBases().size() << "\n";
    for(BaseParam* base : params->getBases()){
        file << base->getBaseNumb() << " " << base->getUnitCount()<<" " <<
                base->getMaxCount()<<" " << base->getHealth()<<" " <<
                base->getX()<<" " << base->getY()<<" " << base->getUnitCurr()<<"\n";
        file << base->getUnits().size() << "\n";
        for(UnitParam* unit : base->getUnits()){
            file << unit->getName() << " " << unit->getBaseNumber() << " ";
            file << unit->getAttributes()->getHealth()<<" " << unit->getAttributes()->getArmor()<<" " <<unit->getAttributes()->getAttack() <<" "<<
                unit->getX()<<" " << unit->getY()<<" " << "\n";
        }
    }
}
