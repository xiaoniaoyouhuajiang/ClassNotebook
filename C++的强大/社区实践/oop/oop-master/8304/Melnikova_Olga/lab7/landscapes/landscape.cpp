#include "landscape.h"

Landscape::Landscape() : action(nullptr)
{

}

Landscape::~Landscape() {
    delete action;
}
