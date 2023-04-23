//
// Created by Artem Butko on 20/05/2020.
//

#include "Chain.h"

Chain::Chain(Field *field)
{
    this->field = field;
    this->next = nullptr;
}

Chain::Chain()
{
    this->next = nullptr;
    this->field = nullptr;
}

void Chain::setNext(Chain *link)
{
    this->next = link;
}

void Chain::addNext(Chain *link)
{
    if (this->next) this->next->addNext(link);
    else this->next = link;

}

void Chain::chain(std::string command, std::string player)
{
    next->chain(command, player);
}
