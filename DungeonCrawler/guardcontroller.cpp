#include "guardcontroller.h"
#include <iostream>
GuardController::GuardController()
{

}

char GuardController::move()
{
    currMove = MoveStr[pos];
    pos++;
    if (pos == size) pos = 0;
    return currMove;
}

void GuardController::incrementMove()
{
    currMove++;
}

GuardController::GuardController(const std::string &MoveStr) : MoveStr(MoveStr)
{
    size = MoveStr.size();
    pos = 0;
    currMove = MoveStr[pos];
}
