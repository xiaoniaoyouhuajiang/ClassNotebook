//
// Created by Artem Butko on 08/05/2020.
//

#include "Mana.h"

void Mana::set(int mana)
{
    this->mana_ = mana;
    this->maxMana_ = mana;
}

void Mana::actRecovered(int recover)
{
    this->mana_ += recover;
    if (this->mana_ > this->maxMana_)
        this->mana_ = this->maxMana_;
}

void Mana::actReduced(int decrease)
{
    this->mana_ -= decrease;
    if (this->mana_ < 0)
        this->mana_ = 0;
}
