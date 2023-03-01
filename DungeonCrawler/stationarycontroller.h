#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "controller.h"
class StationaryController : public Controller
{
public:
    StationaryController();
    char move();
};

#endif // STATIONARYCONTROLLER_H
