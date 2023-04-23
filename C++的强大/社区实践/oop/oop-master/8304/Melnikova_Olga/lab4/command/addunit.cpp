#include "addunit.h"


AddUnit::AddUnit(Game *game, std::string who, bool numBase, int x, int y) 
    : game_(game), who_(who), numBase_(numBase), x_(x), y_(y) {
}
