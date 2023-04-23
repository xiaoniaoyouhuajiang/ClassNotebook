#include "NeutralPlayer.h"
#include "Neutrals/NeutralContext.h"

NeutralPlayer::~NeutralPlayer() {
    for (auto neutral = neutralSet.begin(); neutral != neutralSet.end(); neutral = neutralSet.begin()) {
        delete *neutral;
        //auto temp = *neutral;
        //neutralSet.erase(neutral);
        //delete temp;
    }
}

void NeutralPlayer::addNeutralObject(NeutralContext* neutralObject) {
    neutralSet.insert(neutralObject) ;
}

void NeutralPlayer::removeNeutralObject(NeutralContext* neutralObject) {
    neutralSet.erase(neutralObject);
}

std::set <NeutralContext*>* NeutralPlayer::getNeutralObjectSet() {
    return &neutralSet;
}
