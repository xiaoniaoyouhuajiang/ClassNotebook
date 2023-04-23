#ifndef caretaker_hpp
#define caretaker_hpp

#include <stdio.h>
#include "originator.hpp"

class PlayGame;

class Caretaker {
 private:
    std::shared_ptr<Memento> memento;
    std::shared_ptr<Originator> originator;

 public:
  Caretaker(std::shared_ptr<Originator> originator_) : originator(originator_) {
  }

  void Backup(const PlayGame& playGame) {
    memento = this->originator->Save(playGame);
  }
  void Undo(PlayGame& playGame) {
    this->originator->Restore(playGame);
  }
};
#endif /* caretaker_hpp */
