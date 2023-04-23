#include "originator.h"


class Caretaker {
 private:
  Memento* memento = nullptr;
  Originator *originator_;

 public:
  Caretaker(Originator *originator) : originator_(originator) {
    this->originator_ = originator;
  }

  void Backup(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Object* selectedUnit, int& currNumBase) {
    memento = this->originator_->Save(game,isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
  }
  void Undo(Game<Rules>** game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Object** selectedUnit, int& currNumBase) {
    this->originator_->Restore(game,isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
  }
};
