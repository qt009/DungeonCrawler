#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H

#include "controller.h"
#include <string>
class GuardController : public Controller
{
private:
    std::string MoveStr;
    char currMove;
    size_t pos;
    size_t size;
public:
    GuardController();
    GuardController(const std::string &MoveStr);
    char move();
    void incrementMove();
};

#endif // GUARDCONTROLLER_H
