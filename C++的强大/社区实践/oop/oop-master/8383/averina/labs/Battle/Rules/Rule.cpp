
#include "Rule.h"
#include "../States/StateBright.h"
#include "../States/StateDark.h"
#include "../States/StateUndead.h"

void Rule::changeState()
{
    if (currentPlayer == playerOne) currentPlayer = playerTwo;
    else if (numberOfPlayers == 2) currentPlayer =  playerOne;
    else if (numberOfPlayers == 3 && currentPlayer != playerThree) currentPlayer = playerThree;
    else currentPlayer = playerOne;
}

Rule::Rule()
{
    playerOne = new StateBright();
    playerTwo = new StateDark();
    playerThree = new StateUndead();
    currentPlayer = playerOne;
}

char Rule::getState()
{
    if (currentPlayer == playerOne) return 'B';
    else if (currentPlayer == playerTwo) return 'D';
    else if (numberOfPlayers == 3 && currentPlayer == playerThree) return 'U';
}