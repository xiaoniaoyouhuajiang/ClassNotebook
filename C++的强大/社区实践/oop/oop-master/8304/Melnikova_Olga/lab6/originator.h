#include "concretememento.h"
#include "fstream"
#include "typeinfo"
#include "rule1.h"
#include "rule2.h"

class Originator
{
private:
    std::string fout;
    std::ofstream out;
    std::ifstream fin;


 public:
  Originator(std::string fout, bool isSave) :fout(fout) {
      if(isSave){
          out.open(fout,  std::ios_base::out | std::ios_base::trunc);
      }else{
          fin.open(fout);
      }
  }
  ~Originator(){
      out.close();
      fin.close();
  }

  void doSomething(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Object* selectedUnit, int& currNumBase){
      out<<game->field->H<< " " <<game->field->W<<std::endl;
      for (int i = 1; i <= game->field->H; i++){
          for (int j = 1; j <= game->field->W; j++){
              if(game->field->cells(i,j).innerObject){
                  out<<"Glade"<<std::endl;
              }else{
                  if(game->field->cells(i, j).landscape->isCliff){
                      out<<"Cliff"<<std::endl;
                  }
                  else if(game->field->cells(i, j).landscape->isSwamp){
                      out<<"Swamp"<<std::endl;
                  }else if(game->field->cells(i, j).landscape->isGlade){
                      out<<"Glade"<<std::endl;
                  }
              }
          }
      }
      out<<game->base1->units.size()<<std::endl;
      for (Unit* n : game->base1->units){ // не все созданны
          if(n->isArcher){
              out<<"Archer"<< std::endl;
          }else if(n->isCrossBowMan){
              out<<"CrossBowMan"<< std::endl;
          }else if(n->isKnight){
              out<<"Knight"<< std::endl;
          }else if(n->isSpearMan){
              out<<"Spearman"<< std::endl;
          }else if(n->isHeavyRider){
              out<<"HeavyRider"<< std::endl;
          }else if(n->isLightRider){
              out<<"LightRider"<< std::endl;
          }
          out<<n->health<<std::endl;
          out<<n->x<<std::endl;
          out<<n->y<<std::endl;
          out<<n->numBase<<std::endl;
          out<<n->isUnit<<std::endl;
          out<<n->isBase<<std::endl;
          out<<n->isNeutral<<std::endl;
          out<<n->damage<<std::endl;
          out<<n->movementRadius<<std::endl;
          out<<n->attackRadius<<std::endl;
          out<<n->shieldUsed<<std::endl;
          out<<n->shieldEnabled<<std::endl;
          out<<n->MoveRadiusBetter<<std::endl;
          out<<n->AttackRadiusBetter<<std::endl;
          out<<n->isArcher<<std::endl;
          out<<n->isCrossBowMan<<std::endl;
          out<<n->isKnight<<std::endl;
          out<<n->isSpearMan<<std::endl;
          out<<n->isHeavyRider<<std::endl;
          out<<n->isLightRider<<std::endl;
      }
      out<<game->base1->health<<std::endl;

      out<<game->base2->units.size()<<std::endl;
      for (Unit* n : game->base2->units){ // не все созданны
          if(n->isArcher){
              out<<"Archer "<< std::endl;
          }else if(n->isCrossBowMan){
              out<<"CrossBowMan " << std::endl;
          }else if(n->isKnight){
              out<<"Knight " << std::endl;
          }else if(n->isSpearMan){
              out<<"Spearman " << std::endl;
          }else if(n->isHeavyRider){
              out<<"HeavyRider "<< std::endl;
          }else if(n->isLightRider){
              out<<"LightRider " << std::endl;
          }
          out<<n->health<<std::endl;
          out<<n->x<<std::endl;
          out<<n->y<<std::endl;
          out<<n->numBase<<std::endl;
          out<<n->isUnit<<std::endl;
          out<<n->isBase<<std::endl;
          out<<n->isNeutral<<std::endl;
          out<<n->damage<<std::endl;
          out<<n->movementRadius<<std::endl;
          out<<n->attackRadius<<std::endl;
          out<<n->shieldUsed<<std::endl;
          out<<n->shieldEnabled<<std::endl;
          out<<n->MoveRadiusBetter<<std::endl;
          out<<n->AttackRadiusBetter<<std::endl;
          out<<n->isArcher<<std::endl;
          out<<n->isCrossBowMan<<std::endl;
          out<<n->isKnight<<std::endl;
          out<<n->isSpearMan<<std::endl;
          out<<n->isHeavyRider<<std::endl;
          out<<n->isLightRider<<std::endl;
      }
      out<<game->base2->health<< std::endl;


      for (int i = 1; i <= game->field->H; i++){
          for (int j = 1; j <= game->field->W; j++){
              if(game->field->cells(i,j).innerObject == nullptr){
                  out<<"None"<<std::endl;
              }else{
                  if(game->field->cells(i,j).innerObject->isNeutral){
                      if(((NeutralObject*)game->field->cells(i, j).innerObject)->isHorse){
                          out<<"Horse"<<std::endl;
                      }
                      else if(((NeutralObject*)game->field->cells(i, j).innerObject)->isMedicine){
                          out<<"MedicineChest"<<std::endl;
                      }else if(((NeutralObject*)game->field->cells(i, j).innerObject)->isPower){
                          out<<"PowerUp"<<std::endl;
                      }else if(((NeutralObject*)game->field->cells(i, j).innerObject)->isShield){
                          out<<"Shield"<<std::endl;
                      }
                  }
                  else{
                      out<<"None"<<std::endl;
                  }
              }
          }
      }

      out<<game->isActionDone<< " " << game->isAttackDone << std::endl;
      out<<isUnitSelected << std::endl;
      out<<logToFile << std::endl;
      out<<logToTerminal << std::endl;
      out<<withoutLog << std::endl;

      if(isUnitSelected){
          out<<((Unit*)selectedUnit)->numBase<<std::endl;

          if(((Unit*)selectedUnit)->isArcher){
          out<<"Archer "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }else if(((Unit*)selectedUnit)->isCrossBowMan){
              out<<"CrossBowMan "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }else if(((Unit*)selectedUnit)->isKnight){
              out<<"Knight "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }else if(((Unit*)selectedUnit)->isSpearMan){
              out<<"Spearman "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }else if(((Unit*)selectedUnit)->isHeavyRider){
              out<<"HeavyRider "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }else if(((Unit*)selectedUnit)->isLightRider){
              out<<"LightRider "<<((Unit*)selectedUnit)->x<<" "<<((Unit*)selectedUnit)->y << std::endl;
          }
      }else{
          out<<"None"<< std::endl;;
      }

      out<<currNumBase << std::endl;


  }

  Memento *Save(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Object* selectedUnit, int& currNumBase) {
    doSomething(game,isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
    return new ConcreteMemento(fout);
  }

  void Restore(Game<Rules>** game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Object** selectedUnit, int& currNumBase)
  {
      //this->fout = memento->state();

      int h, w;
      fin>>h>>w;
      Rule2* rule = new Rule2();
      Game<Rules> _game(h,w, *rule);


      for (int i = 1; i <= h; i++){
          for (int j = 1; j <= w; j++){
              if(_game.field->cells(i,j).innerObject){
                  _game.field->deleteObject(i,j);
              }
          }
      }
      _game.base1->units.clear();
      _game.base2->units.clear();

      LandscapeFabric landFabric;
      Landscape* cliff = landFabric.cliff();
      Landscape* glade = landFabric.glade();
      Landscape* swamp = landFabric.swamp();

      std::string name;
      for (int i = 1; i <= h; i++){
          for (int j = 1; j <= w; j++){
              fin>>name;
              if(name=="Glade"){
                  _game.field->cells(i, j).landscape = glade;
              }else if(name=="Cliff"){
                      _game.field->cells(i, j).landscape = cliff;
              }else{
                      _game.field->cells(i, j).landscape = swamp;
              }
          }
      }

      objectFabric fabric;
      _game.base1 = fabric.createBase(1,1,0);
      _game.base2 = fabric.createBase(h,w,1); //numbase 0 ??????
      _game.field->addObject(_game.base1, _game.base1->baseCell->x, _game.base1->baseCell->y);
      _game.field->addObject(_game.base2, _game.base2->baseCell->x, _game.base2->baseCell->y);

      int size;
      fin>>size;
      while(size){
          fin>>name;
          if (name == "EndBase1") break;
          Unit* unit;
          if(name=="Archer"){
              unit = _game.base1->createUnit("Archer");
          }else if("CrossBowMan"){
              unit = _game.base1->createUnit("CrossBowMan");
          }else if("Knight"){
              unit = _game.base1->createUnit("Knight");
          }else if("Spearman"){
              unit = _game.base1->createUnit("Spearman");
          }else if("HeavyRider"){
              unit = _game.base1->createUnit("HeavyRider");
          }else if("LightRider"){
              unit = _game.base1->createUnit("LightRider");
          }

          fin>>unit->health;
          fin>>unit->x;
          fin>>unit->y;
          fin>>unit->numBase;
          fin>>unit->isUnit;
          fin>>unit->isBase;
          fin>>unit->isNeutral;
          fin>>unit->damage;
          fin>>unit->movementRadius;
          fin>>unit->attackRadius;
          fin>>unit->shieldUsed;
          fin>>unit->shieldEnabled;
          fin>>unit->MoveRadiusBetter;
          fin>>unit->AttackRadiusBetter;
          fin>>unit->isArcher;
          fin>>unit->isCrossBowMan;
          fin>>unit->isKnight;
          fin>>unit->isSpearMan;
          fin>>unit->isHeavyRider;
          fin>>unit->isLightRider;

          _game.field->addObject(unit,unit->x,unit->y);
          size--;
      }
      fin>>_game.base1->health;

      fin>>size;

      while(size){
          fin>>name;
          Unit* unit;
          if(name=="Archer"){
              unit = _game.base2->createUnit("Archer");
          }else if("CrossBowMan"){
              unit = _game.base2->createUnit("CrossBowMan");
          }else if("Knight"){
              unit = _game.base2->createUnit("Knight");
          }else if("Spearman"){
              unit = _game.base2->createUnit("Spearman");
          }else if("HeavyRider"){
              unit = _game.base2->createUnit("HeavyRider");
          }else if("LightRider"){
              unit = _game.base2->createUnit("LightRider");
          }

          fin>>unit->health;
          fin>>unit->x;
          fin>>unit->y;
          fin>>unit->numBase;
          fin>>unit->isUnit;
          fin>>unit->isBase;
          fin>>unit->isNeutral;
          fin>>unit->damage;
          fin>>unit->movementRadius;
          fin>>unit->attackRadius;
          fin>>unit->shieldUsed;
          fin>>unit->shieldEnabled;
          fin>>unit->MoveRadiusBetter;
          fin>>unit->AttackRadiusBetter;
          fin>>unit->isArcher;
          fin>>unit->isCrossBowMan;
          fin>>unit->isKnight;
          fin>>unit->isSpearMan;
          fin>>unit->isHeavyRider;
          fin>>unit->isLightRider;

          _game.field->addObject(unit,unit->x,unit->y);
          size--;
      }
      fin>>_game.base2->health;


      for (int i = 1; i <= _game.field->H; i++){
          for (int j = 1; j <= _game.field->W; j++){
              fin>>name;
              if(name=="Horse"){
                  _game.field->addObject(fabric.createHorse(), i, j);
              }else if(name=="MedicineChest"){
                  _game.field->addObject(fabric.createMedicineChest(), i, j);
              }else if(name=="PowerUp"){
                  _game.field->addObject(fabric.createPowerUp(), i, j);
              }else if(name=="Shield"){
                  _game.field->addObject(fabric.createShield(), i, j);
              }
          }
      }
      fin>>_game.isActionDone>> _game.isAttackDone;
      fin>>isUnitSelected;
      fin>>logToFile;
      fin>>logToTerminal;
      fin>>withoutLog;
      selectedUnit = nullptr;
      if(isUnitSelected){
          int num;
          fin>>num;
          if(num == 1){
              if(name=="Archer"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isArcher){
                          *selectedUnit = n;
                      }
                  }
              }else if("CrossBowMan"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isCrossBowMan){
                         *selectedUnit = n;
                      }
                  }
              }else if("Knight"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isKnight){
                          *selectedUnit = n;
                      }
                  }
              }else if("Spearman"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isSpearMan){
                          *selectedUnit = n;
                      }
                  }
              }else if("HeavyRider"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isHeavyRider){
                          *selectedUnit = n;
                      }
                  }
              }else if("LightRider"){
                  for (Unit* n : _game.base2->units){ // не все созданны
                      if(n->isLightRider){
                          *selectedUnit = n;
                      }
                  }
              }
          }else{
              if(name=="Archer"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isArcher){
                          *selectedUnit = n;
                      }
                  }
              }else if("CrossBowMan"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isCrossBowMan){
                          *selectedUnit = n;
                      }
                  }
              }else if("Knight"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isKnight){
                          *selectedUnit = n;
                      }
                  }
              }else if("Spearman"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isSpearMan){
                          *selectedUnit = n;
                      }
                  }
              }else if("HeavyRider"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isHeavyRider){
                          *selectedUnit = n;
                      }
                  }
              }else if("LightRider"){
                  for (Unit* n : _game.base1->units){ // не все созданны
                      if(n->isLightRider){
                          *selectedUnit = n;
                      }
                  }
              }
          }
      }
      fin>>currNumBase;
      *game = &_game;
  }

};
