
#include "SkipRequest.h"

void SkipRequest::Command()
{
    int number;
    if (player == "B") number = 0;
    else if (player == "D") number = 1;
    else number = 2;

    field->basesOnField[number]->gold++;
}